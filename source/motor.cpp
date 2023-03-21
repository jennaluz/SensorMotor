/*
 * SensorMotor/source/motor.cpp
 *
 * Controls the Stepper Motor status based on motor_queue values.
 * Sends the current direction of the Stepper Motor to motor_direction_queue.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>

#include "motor.h"
#include "motor_driver.h"
#include "sensor.h"
#include "system_code.h"
#include "system_error.h"


QueueHandle_t motor_queue = NULL;
QueueHandle_t motor_direction_queue = NULL;

const uint REV_STEPS = 275;


/*
 * Reads in information from motor_queue to control the status of the queue.
 * The status of the queue is defined by the enumeratored eStatus varaible.
 */
void motor_handler(void *parameters)
{
    system_code motor_code = MOTOR_CLOCKWISE;
    system_code motor_status = motor_code;
    system_code motor_dir = MOTOR_CLOCKWISE;

    int old_tmp = 70;
    int new_tmp = 0;
    int old_hmd = 45;
    int new_hmd = 0;

    while (true) {
        xQueueReceive(motor_queue, &motor_code, 0);

        // changes functionality based on motor_code
        switch (motor_code) {
            case MOTOR_RESET:
                motor_code = motor_status;
                break;
            case MOTOR_CLOCKWISE:
                motor_dir = MOTOR_CLOCKWISE;
                xQueueOverwrite(motor_direction_queue, &motor_dir);

                motor_clockwise();
                motor_status = motor_code;
                break;
            case MOTOR_COUNTERCLOCKWISE:
                motor_dir = MOTOR_COUNTERCLOCKWISE;
                xQueueOverwrite(motor_direction_queue, &motor_dir);

                motor_counterclockwise();
                motor_status = motor_code;
                break;
            case MOTOR_ALTERNATE:
                motor_dir = MOTOR_CLOCKWISE;
                xQueueOverwrite(motor_direction_queue, &motor_dir);

                for (int i = 0; i < REV_STEPS; i++) {
                    motor_clockwise();
                }

                motor_dir = MOTOR_COUNTERCLOCKWISE;
                xQueueOverwrite(motor_direction_queue, &motor_dir);

                for (int i = 0; i < REV_STEPS; i++) {
                    motor_counterclockwise();
                }

                motor_status = motor_code;
                break;
            case MOTOR_TEMPERATURE:
                xQueuePeek(temperature_queue, &new_tmp, 0);

                if (new_tmp == old_tmp) {
                    motor_dir = MOTOR_HALT;
                    xQueueOverwrite(motor_direction_queue, &motor_dir);
                    motor_halt();
                } else {
                    if (new_tmp > old_tmp) {
                        motor_dir = MOTOR_CLOCKWISE;
                        xQueueOverwrite(motor_direction_queue, &motor_dir);
                        motor_increment();
                    } else {
                        motor_dir = MOTOR_COUNTERCLOCKWISE;
                        xQueueOverwrite(motor_direction_queue, &motor_dir);
                        motor_decrement();
                    }
                }

                old_tmp = new_tmp;
                motor_status = motor_code;
                break;
            case MOTOR_HUMIDITY:
                xQueuePeek(humidity_queue, &new_hmd, 0);

                if (new_hmd == old_hmd) {
                    motor_dir = MOTOR_HALT;
                    xQueueOverwrite(motor_direction_queue, &motor_dir);
                    motor_halt();
                } else {
                    if (new_hmd > old_hmd) {
                        motor_dir = MOTOR_CLOCKWISE;
                        xQueueOverwrite(motor_direction_queue, &motor_dir);
                        motor_increment();
                    } else {
                        motor_dir = MOTOR_COUNTERCLOCKWISE;
                        xQueueOverwrite(motor_direction_queue, &motor_dir);
                        motor_decrement();
                    }
                }

                old_hmd = new_hmd;
                motor_status = motor_code;
                break;
            case MOTOR_HALT:
                motor_dir = MOTOR_HALT;
                xQueueOverwrite(motor_direction_queue, &motor_dir);
                motor_halt();
                break;
            default:
                system_error(ERROR_UNKNOWN_INPUT);
        }

        vTaskDelay(1);
    }
}
