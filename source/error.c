/*
 * SensorMotor/source/error.c
 */


#include <FreeRTOS.h>
#include <queue.h>


#include "display.h"
#include "error.h"


/*
 * Send error code to xDisplayQueue.
 */
void vError(error_code_e eError)
{
    xQueueSendToFront(xDisplayQueue, &eError, 0);
}
