/*
 * Created by Nhom 6
*/

#include <stdio.h>
#include <inttypes.h>
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "FreeRTOSConfig.h"
#include "freertos/queue.h"


#include "data_types.h"

QueueHandle_t queue=NULL;

void Reception_task(void *pvParameter)
{
    Task* taskreceive = (Task*)pvParameter;
    //classify
    
     for(int i=0;i<sizeof(taskreceive)/sizeof(taskreceive[0]);i++){
        taskreceive[i].dataType =taskreceive[i].ID%3;
    }

    
    // push to queue
    for(int i=0;i<sizeof(taskreceive)/sizeof(taskreceive[0]);i++){
        if (xQueueSend(queue, taskreceive[i], QUEUE_SEND_WAITS) != pdTRUE)
        {
            printf("Failed to send %d to queue ! \n", taskreceive[i].ID);
        }
        else printf("gg");
    }

    while(1){
        vTaskDelay(pdMS_TO_TICKS(QUEUE_SEND_DELAY));
    }
}
void Functional_task(void *pvParameter){
    Task receive_task;
    char* function_task = (char*)pvParameter;
    while(1){
        if(xQueueReceive(queue, receive_task, pdMS_TO_TICKS(QUEUE_WAITS))== pdTRUE)
            {
                    if (function_task="task1" && receive_task.dataType == 0  )
                    {
                        printf("Received from task1 ID= %d\n", receive_task.ID);
                    }
                    else if (function_task="task2" && receive_task.dataType == 1  )
                    {
                        printf("Received from task2 ID= %d\n", receive_task.ID);
                    }
                    else if (receive_task.dataType == 2)
                    {
                        printf("Invalid data\n");
                    }
                    else xQueueSendToFront(queue, receive_task, QUEUE_SEND_WAITS);
            }
        }
        
    }



void app_main(void) 
{   
    Task all_task[5]={{1,0},{2,0},{3,0},{4,0},{5,0}};
    queue=xQueueCreate(QUEUE_SIZE, sizeof(all_task[0]));
    if (queue == 0)
    {
        printf("Failed to create queue= %p\n", queue);
    }
    xTaskCreate(Reception_task, "Reception_task", 4096, all_task, 10, NULL);
    xTaskCreate(Functional_task, "task1", 4096, NULL, 5, NULL);
    xTaskCreate(Functional_task, "task2", 4096, NULL, 5, NULL);

    vTaskStartScheduler();
}