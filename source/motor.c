/*
 * SensorMotor/source/motor.c
 *
 * Controls the Stepper Motor status based on xMotorQueue values.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <stdio.h>

#include "motor.h"
#include "motor_driver.h"


QueueHandle_t xMotorQueue = NULL;


/*
 * Reads in information from xMotorQueue to control the status of the queue.
 * The status of the queue is defined by the enumeratored eStatus varaible.
 */
void vMotorHandler()
{
    motor_status_e eStatus = MOTOR_CLOCKWISE;

    while (true) {
        xQueueReceive(xMotorQueue, &eStatus, 0);

        switch (eStatus) {
            case MOTOR_CLOCKWISE:
                vMotorClockwise();
                break;
            case MOTOR_COUNTERCLOCKWISE:
                vMotorCounterclockwise();
                break;
            case MOTOR_ALTERNATE:
                vMotorAlternate();
                break;
            default:
                printf("Error");
        }
    }
}
