/*
 * SensorMotor/source/error.c
 */


#include <FreeRTOS.h>
#include <queue.h>

#include "display.h"
#include "system_code.h"


/*
 * Send error code to xDisplayQueue.
 */
void vError(system_code_e eError)
{
    xQueueSendToFront(xDisplayQueue, &eError, 0);
}
