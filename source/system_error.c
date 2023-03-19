/*
 * SensorMotor/source/error.c
 */


#include <FreeRTOS.h>
#include <queue.h>

#include "display.h"
#include "system_code.h"
#include "system_error.h"


/*
 * Send error code to display_queue.
 */
void system_error(system_code eError)
{
    xQueueSendToFront(display_queue, &eError, 0);
}
