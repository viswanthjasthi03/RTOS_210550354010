#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t msgmq;


void temperature_task(void *data)
{
while(1)
{
printf("temperature task started\n");
//--------
printf("temperature task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void pressure_task(void *data)
{
while(1)
{
printf("pressure task started\n");
//--------
printf("pressure task ended\n");
vTaskDelay(2000 / portTICK_PERIOD_MS);
}
}

void uart_task(void *data)
{
while(1)
{
printf("uart task started\n");
//--------
printf("uart task ended\n");
vTaskDelay(5000 / portTICK_PERIOD_MS);
}
}

void mqtt_task(void *data)
{
int msg=0;
while(1)
{
printf("mqtt task started\n");
msg++;
xQueueSend(msgmq,&msg,0);
printf("mqtt task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void ethernet_task(void *data)
{
int buff;
while(1)
{
printf("ethernet task started\n");
xQueueReceive(msgmq,&buff,0);
printf("mqtt Buff=%d\n",buff);
printf("ethernet task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void app_main(void)
{
    int i = 0;
    msgmq = xQueueCreate(5, sizeof(int));
    xTaskCreate(temperature_task, "temp_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(pressure_task, "press_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(uart_task, "uart_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(mqtt_task, "mqtt_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(ethernet_task, "ether_tsk", 2048, NULL, 3, NULL);
    while (1) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
