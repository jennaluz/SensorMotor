/*
 * SensorMotor/source/error.c
 */


#include <FreeRTOS.h>
#include <queue.h>

#include "display.h"
#include "system_code.h"


/*
 * Send error code to display_queue.
 */
void error(system_code error)
{
    xQueueSendToFront(display_queue, &error, 0);
}
