#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"

#define WIFI_SSID "Petersson"
#define WIFI_PASS "HU88085TAO"
#define MQTT_BROKER_IP "192.168.15.4"
#define MQTT_BROKER_PORT 1884

static mqtt_client_t* client;

void mqtt_pub_callback(void *arg, err_t err) {
    if (err == ERR_OK) {
        printf("Mensagem publicada com sucesso.\n");
    } else {
        printf("Erro ao publicar a mensagem. Código: %d\n", err);
    }
}

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    printf("Callback de conexão MQTT. Status: %d\n", status);
    switch (status) {
        case MQTT_CONNECT_ACCEPTED:
            printf("Conectado ao broker com sucesso!\n");
            break;
        case MQTT_CONNECT_REFUSED_PROTOCOL_VERSION:
            printf("Erro: versão do protocolo não suportada.\n");
            break;
        case MQTT_CONNECT_REFUSED_IDENTIFIER:
            printf("Erro: identificador rejeitado.\n");
            break;
        case MQTT_CONNECT_REFUSED_SERVER:
            printf("Erro: broker indisponível.\n");
            break;
        case MQTT_CONNECT_REFUSED_USERNAME_PASS:
            printf("Erro: autenticação falhou.\n");
            break;
        case MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_:
            printf("Erro: não autorizado.\n");
            break;
        default:
            printf("Erro desconhecido de conexão: %d\n", status);
            break;
    }
}

void connect_and_publish() 
{
    ip_addr_t broker_addr;

    printf("Convertendo endereço IP do broker...\n");
    if (!ip4addr_aton(MQTT_BROKER_IP, &broker_addr)) 
    {
        printf("Erro: IP do broker inválido\n");
        return;
    }

    printf("Criando cliente MQTT...\n");
    client = mqtt_client_new();

    if (client == NULL) 
    {
        printf("Erro: falha ao criar cliente MQTT\n");
        return;
    }

    struct mqtt_connect_client_info_t ci = {
        .client_id = "pc",
        .client_user = NULL,
        .client_pass = NULL,
        .keep_alive = 60,
        .will_topic = NULL,
        .will_msg = NULL,
        .will_qos = 0,
        .will_retain = 0,
    };

    printf("Conectando ao broker MQTT (%s:%d)...\n", MQTT_BROKER_IP, MQTT_BROKER_PORT);
    mqtt_client_connect(client, &broker_addr, MQTT_BROKER_PORT, mqtt_connection_cb, NULL, &ci);

    for (int i = 0; i < 10; ++i) {
        cyw43_arch_poll();
        sleep_ms(10);
        if (client->conn_state == 3) 
        {
            printf("Conexão MQTT estabelecida com sucesso.\n");
            break;
        }
        printf("Aguardando conexão MQTT... (%d/10)\n", i + 1);
        sleep_ms(500);
    }

    if (client->conn_state != 3) 
    {
        printf("Erro: conexão MQTT falhou ou expirou.\n");
        return;
    }
}

int main() 
{
    stdio_init_all();
    
    sleep_ms(1000);
    
    if (cyw43_arch_init()) 
    {
        printf("Erro ao iniciar Wi-Fi\n");
    }

    cyw43_arch_enable_sta_mode();

    if(cyw43_arch_wifi_connect_timeout_ms( WIFI_SSID , WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) 
    {
        printf("Erro ao conectar\n");
    } else {        
        printf("Conectado ao Wi-Fi\n");
        printf("Endereço IP do Pico: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));
    }

    printf("Wi-Fi connected.\n");

    connect_and_publish();

    while (true) 
    {
        cyw43_arch_poll();
        sleep_ms(10);
        
        const char *topic = "pico/test";
        const char *message = "Hello from Pico W!";

        printf("Publicando mensagem no tópico '%s': %s\n", topic, message);

        err_t err = mqtt_publish(client, topic, message, strlen(message), 0, 0, mqtt_pub_callback, NULL);

        if (err != ERR_OK)
        {
            printf("Erro ao publicar: %d\n", err);
        }
        else
        {
            printf("Publicação enviada com sucesso!\n");
        }
    }

    return 0;
}