#include "lwip/apps/mqtt.h"
#include "mqtt_comm.h"
#include "lwipopts.h"
#include <string.h>

static mqtt_client_t *client;

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) 
{
    printf("Status %d\n",status);
    if (status == MQTT_CONNECT_ACCEPTED) 
    {
        printf("Conectado ao broker MQTT com sucesso!\n");
    } else {
        printf("Falha ao conectar ao broker, código: %d\n", status);
    }
}

void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass) 
{
    ip_addr_t broker_addr;
    
    if (!ip4addr_aton(broker_ip, &broker_addr)) 
    {
        printf("Erro no IP\n");
        return;
    }

    client = mqtt_client_new();
    if (client == NULL) 
    {
        printf("Falha ao criar o cliente MQTT\n");
        return;
    }

    struct mqtt_connect_client_info_t ci = {
        .client_id = client_id,
        .client_user = user,
        .client_pass = pass
    };

    int result;
    result = mqtt_client_connect(client, &broker_addr, 1884, mqtt_connection_cb, NULL, &ci);
    printf("Resultado %d\n",result);
}

static void mqtt_pub_request_cb(void *arg, err_t result) 
{
    if (result == ERR_OK) 
    {
        printf("Publicação MQTT enviada com sucesso!\n");
    } 
    else 
    {
        printf("Erro ao publicar via MQTT: %d\n", result);
    }
}

void mqtt_comm_publish() 
{
    err_t status = mqtt_publish(client, "escola/sala1/temperatura", "26.5", strlen("26.5"), 0, 0, NULL, NULL);

    if (status != ERR_OK) 
    {
        printf("mqtt_publish falhou ao ser enviada: %d\n", status);
    }
}