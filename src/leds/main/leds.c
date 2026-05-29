/**
 * @file     leds.c
 * @brief    Asynchronous multi-LED blinking (3:1 ratio) using FreeRTOS on ESP-IDF v6.0.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/* Configuración de pines */
#define LED_A_PIN    (26U)   /* LED rápido (3 parpadeos por segundo) */
#define LED_B_PIN    (27U)   /* LED lento (1 parpadeo por segundo) */

/* Tiempos de estado (Semiperíodos) */
#define LED_A_TOGGLE_MS   (166U)  /* 333ms ciclo total / 2 */
#define LED_B_TOGGLE_MS   (500U)  /* 1000ms ciclo total / 2 */

/**
 * @brief Tarea para el LED A: 3 parpadeos por segundo
 */
static void BlinkTaskA(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(LED_A_TOGGLE_MS);

    (void)pvParameters;

    gpio_reset_pin(LED_A_PIN);
    gpio_set_direction(LED_A_PIN, GPIO_MODE_OUTPUT);

    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        gpio_set_level(LED_A_PIN, 1);
        printf("[LED A - Pin 26] (*) ENCENDIDO (Rápido)\n");
        xTaskDelayUntil(&xLastWakeTime, xFrequency);

        gpio_set_level(LED_A_PIN, 0);
        printf("[LED A - Pin 26] ( ) APAGADO   (Rápido)\n");
        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

/**
 * @brief Tarea para el LED B: 1 parpadeo por segundo
 */
static void BlinkTaskB(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(LED_B_TOGGLE_MS);

    (void)pvParameters;

    gpio_reset_pin(LED_B_PIN);
    gpio_set_direction(LED_B_PIN, GPIO_MODE_OUTPUT);

    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        gpio_set_level(LED_B_PIN, 1);
        printf("               [LED B - Pin 27] (***) ENCENDIDO (Lento)\n");
        xTaskDelayUntil(&xLastWakeTime, xFrequency);

        gpio_set_level(LED_B_PIN, 0);
        printf("               [LED B - Pin 27] (   ) APAGADO   (Lento)\n");
        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

/**
 * @brief Punto de entrada de la aplicación
 */
void app_main(void)
{
    printf("=====================================\n");
    printf("    Blinker Asíncrono Ratio 3:1\n");
    printf("=====================================\n");

    /* Ambas tareas corren de forma independiente con prioridad 5 */
    xTaskCreate(BlinkTaskA, "Blink_Fast", 2048U, NULL, 5U, NULL);
    xTaskCreate(BlinkTaskB, "Blink_Slow", 2048U, NULL, 5U, NULL);
}