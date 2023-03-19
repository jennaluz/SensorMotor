/*
 * SensorMotor/source/motor.c
 *
 * Controls the Stepper Motor status based on motor_queue values.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <stdio.h>

#include "motor.h"
#include "motor_driver.h"
#include "sensor.h"
#include "system_code.h"
#include "system_error.h"


QueueHandle_t motor_queue = NULL;


/*
 * Reads in information from motor_queue to control the status of the queue.
 * The status of the queue is defined by the enumeratored eStatus varaible.
 */
void motor_handler()
{
    system_code motor_code = MOTOR_CLOCKWISE;
    system_code motor_status = motor_code;
    int old_tmp = 70;
    int new_tmp = 0;
    int old_hmd = 45;
    int new_hmd = 0;

    while (true) {
        xQueuePeek(motor_queue, &motor_code, 0);

        switch (motor_code) {
            case MOTOR_CLOCKWISE:
                motor_clockwise();
                break;
            case MOTOR_COUNTERCLOCKWISE:
                motor_counterclockwise();
                break;
            case MOTOR_ALTERNATE:
                motor_alternate();
                break;
            case MOTOR_TEMPERATURE:
                xQueuePeek(temperature_queue, &new_tmp, 0);

                if (new_tmp == old_tmp) {
                    motor_halt();
                } else {
                    if (new_tmp > old_tmp) {
                        motor_increment();
                    } else {
                        motor_decrement();
                    }
                }

                old_tmp = new_tmp;
                break;
            case MOTOR_HUMIDITY:
                xQueuePeek(humidity_queue, &new_hmd, 0);

                if (new_hmd == old_hmd) {
                    motor_halt();
                } else {
                    if (new_hmd > old_hmd) {
                        motor_increment();
                    } else {
                        motor_decrement();
                    }
                }

                old_hmd = new_hmd;
                break;
            case MOTOR_HALT:
                motor_halt();
                break;
            case MOTOR_STATUS:
                break;
            default:
                system_error(ERROR_UNKNOWN_INPUT);
        }

        taskYIELD();
    }
}
