/*
 * SensorMotor/source/main.c
 */


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/time.h>

#include <stdio.h>

#include "button.h"
#include "display.h"
#include "display_driver.h"
#include "motor.h"
#include "motor_driver.h"
#include "sensor.h"
#include "sensor_driver.h"
#include "system_code.h"


int main()
{
    stdio_init_all();

    // initialize stepper motor gpio pins
    vDisplayInit();
    motor_init();
    sensor_init();
    button_irq_init();

    // create semaphores
    button1_semaphore = xSemaphoreCreateBinary();
    button2_semaphore = xSemaphoreCreateBinary();
    button3_semaphore = xSemaphoreCreateBinary();
    xDisplaySemaphore = xSemaphoreCreateBinary();

    // create queues
    xDisplayQueue = xQueueCreate(10, sizeof(system_code_e));
    xLeftDisplayQueue = xQueueCreate(1, sizeof(uint8_t));
    xRightDisplayQueue = xQueueCreate(1, sizeof(uint8_t));
    motor_queue = xQueueCreate(1, sizeof(system_code_e));
    sensor_base_queue = xQueueCreate(1, sizeof(sensor_base_e));
    temperature_queue = xQueueCreate(1, sizeof(int));
    humidity_queue = xQueueCreate(1, sizeof(int));

    // create tasks
    xTaskCreate(button1_handler, "Button 1", 256, NULL, 4, NULL);
    xTaskCreate(button2_handler, "Button 2", 256, NULL, 4, NULL);
    xTaskCreate(button3_handler, "Button 3", 256, NULL, 4, NULL);
    xTaskCreate(vDisplayHandler, "Display", 256, NULL, 3, NULL);
    xTaskCreate(vLeftDisplayHandler, "Left Display", 256, NULL, 3, NULL);
    xTaskCreate(vRightDisplayHandler, "Right Display", 256, NULL, 3, NULL);
    xTaskCreate(motor_handler, "Stepper Motor Handler", 256, NULL, 3, NULL);
    xTaskCreate(sensor_handler, "HDC1080 Handler", 256, NULL, 3, NULL);

    // give display semaphore
    xSemaphoreGive(xDisplaySemaphore);

    vTaskStartScheduler();

    while (true) {};
}
