#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    while (true) {
        printf("SuperMiniEnviroSense boot ok\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}