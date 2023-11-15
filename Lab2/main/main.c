

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"

#define UNCLICK 0
#define CLICK 1

void Task_printid(void *pvParameters)
{
    while (1)
    {
        printf("2012863\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
// void vTaskDelete(xTaskHandle pxTask);
int button_state = 0;
void Task_printESP32(void *pvParameters)
{

    while (1)
    {
        switch (button_state)
        {
        case UNCLICK:
            printf("ABC\n");
            if (gpio_get_level(GPIO_NUM_17) == 1){
                button_state = 1;
                printf("ESP32\n");
            }
                
            break;
        case CLICK:
            if (gpio_get_level(GPIO_NUM_17) == 0)
                button_state = 0;
            break;
        default:
            break;
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void gpio_init()
{
    gpio_config_t gpioConfig;
    gpioConfig.pin_bit_mask = (1ULL << GPIO_NUM_17);
    gpioConfig.mode = GPIO_MODE_INPUT;
    gpioConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpioConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpioConfig.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpioConfig);
}

void app_main(void)
{
    // this is the entry point of the program
    // your code goes here
    gpio_init();
    xTaskCreate(&Task_printid, "Demo Task", 4096, NULL, 5, NULL); // lần lượt là task func,name of task,stack size, priority of task
    xTaskCreate(&Task_printESP32, "Demo Task2", 4096, NULL, 10, NULL);
}
