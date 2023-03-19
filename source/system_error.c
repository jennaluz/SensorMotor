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
void system_error(system_code error)
{
    if (error == ERROR_OVERFLOW) {
        xQueueReset(display_queue);
    }
    xQueueSendToFront(display_queue, &error, 0);
}
