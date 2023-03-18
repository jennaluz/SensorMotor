/*
 * SensorMotor/source/motor.c
 *
 * Controls the Stepper Motor status based on motor_queue values.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <stdio.h>

#include "error.h"
#include "motor.h"
#include "motor_driver.h"
#include "sensor.h"
#include "system_code.h"


QueueHandle_t motor_queue = NULL;


/*
 * Reads in information from motor_queue to control the status of the queue.
 * The status of the queue is defined by the enumeratored eStatus varaible.
 */
void vMotorHandler()
{
    system_code_e eMotorCode = MOTOR_CLOCKWISE;
    system_code_e eStatus = eMotorCode;
    int iOldTmp = 70;
    int iNewTmp = 0;
    int iOldHmd = 45;
    int iNewHmd = 0;

    int i = 0;
    for (i = 0; i < 100; i++) {
        printf("%d\n", eMotorCode);
    }

    while (true) {
        xQueuePeek(motor_queue, &eMotorCode, 0);

        switch (eMotorCode) {
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
                xQueuePeek(xTemperatureQueue, &iNewTmp, 0);

                if (iNewTmp == iOldTmp) {
                    vMotorHalt();
                } else {
                    if (iNewTmp > iOldTmp) {
                        vMotorIncrement();
                    } else {
                        vMotorDecrement();
                    }
                }

                iOldTmp = iNewTmp;
                break;
            case MOTOR_HUMIDITY:
                xQueuePeek(xHumidityQueue, &iNewHmd, 0);

                if (iNewHmd == iOldHmd) {
                    vMotorHalt();
                } else {
                    if (iNewHmd > iOldHmd) {
                        vMotorIncrement();
                    } else {
                        vMotorDecrement();
                    }
                }

                iOldHmd = iNewHmd;
                break;
            case MOTOR_HALT:
                vMotorHalt();
                break;
            case MOTOR_STATUS:
                break;
            default:
                vError(ERROR_UNKNOWN_INPUT);
        }

        //vTaskDelay(100);
    }
}
