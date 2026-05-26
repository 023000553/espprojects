/**
 * @file   hello-world.c
 * @brief  Basic FreeRTOS Hello World example for ESP32.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @brief Task function.
 */
static void HelloTask(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        printf("Hello World I'm Manolo!\n");

        /* Delay task execution for 1000 ms */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Application entry point.
 */
void app_main(void)
{
    // Es mejor validar si la tarea realmente se creó
    BaseType_t result = xTaskCreate(
        HelloTask,
        "HelloTask",
        2048,
        NULL,
        1,
        NULL
    );

    if (result != pdPASS) {
        printf("Error: No se pudo crear la tarea HelloTask\n");
    }
} // <--- ¡Aquí faltaba esta llave!