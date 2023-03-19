/*
 * SensorMotor/source/main.c
 */


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

#include <pico/stdlib.h>

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
    display_init();
    motor_init();
    sensor_init();
    button_irq_init();

    // create semaphores
    button1_semaphore = xSemaphoreCreateBinary();
    button2_semaphore = xSemaphoreCreateBinary();
    button3_semaphore = xSemaphoreCreateBinary();
    display_semaphore = xSemaphoreCreateBinary();

    // create queues
    display_queue = xQueueCreate(10, sizeof(system_code));
    left_display_queue = xQueueCreate(1, sizeof(int));
    right_display_queue = xQueueCreate(1, sizeof(int));
    motor_queue = xQueueCreate(1, sizeof(system_code));
    motor_direction_queue = xQueueCreate(1, sizeof(system_code));
    sensor_base_queue = xQueueCreate(1, sizeof(display_setting));
    temperature_queue = xQueueCreate(1, sizeof(int));
    humidity_queue = xQueueCreate(1, sizeof(int));

    // create tasks
    xTaskCreate(button1_handler, "Button 1", 256, NULL, 4, NULL);
    xTaskCreate(button2_handler, "Button 2", 256, NULL, 4, NULL);
    xTaskCreate(button3_handler, "Button 3", 256, NULL, 4, NULL);
    xTaskCreate(display_handler, "Display", 256, NULL, 3, NULL);
    xTaskCreate(left_display_handler, "Left Display", 256, NULL, 3, NULL);
    xTaskCreate(right_display_handler, "Right Display", 256, NULL, 3, NULL);
    xTaskCreate(motor_handler, "Stepper Motor Handler", 256, NULL, 3, NULL);
    xTaskCreate(sensor_handler, "HDC1080 Handler", 256, NULL, 3, NULL);

    // give display semaphore
    xSemaphoreGive(display_semaphore);

    vTaskStartScheduler();

    while (true) {};
}
