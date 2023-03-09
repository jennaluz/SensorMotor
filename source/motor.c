/*
 * SensorMotor/source/motor.c
 *
 * Controls the Stepper Motor status based on xMotorQueue values.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <stdio.h>

#include "error.h"
#include "motor.h"
#include "motor_driver.h"


QueueHandle_t xMotorQueue = NULL;


/*
 * Reads in information from xMotorQueue to control the status of the queue.
 * The status of the queue is defined by the enumeratored eStatus varaible.
 */
void vMotorHandler()
{
    motor_code_e eCode = MOTOR_CLOCKWISE;
    motor_code_e eStatus = eCode;

    while (true) {
        xQueueReceive(xMotorQueue, &eCode, 0);

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
            case MOTOR_TEMPERATURE:
            case MOTOR_HUMIDITY:
                break;
            case MOTOR_HALT:
                break;
            case MOTOR_STATUS:
                break;
            default:
                vError(ERROR_UNKNOWN_INPUT);
        }
    }
}
