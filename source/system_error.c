/*
 * SensorMotor/source/system_error.c
 *
 * Receives error codes to send to display_queue.
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
    // ERROR_OVERFLOW must clear the display_queue
    if (error == ERROR_OVERFLOW) {
        xQueueReset(display_queue);
    }

    xQueueSendToFront(display_queue, &error, 0);
}
