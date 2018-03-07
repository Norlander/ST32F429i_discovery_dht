/*
 * dht_example.c
 *
 *  Created on: 23 Feb 2018
 *      Author: matte
 */


#include "dht22.h"

#include <stm32f4xx.h>
#include <tim_old.h>

static dht22_data data;

int dht_test()
{
  /*
    ....
  */

  DTIM_Initialize();
  DHT22_Init();

  while (1)
  {
     /* Temporarily disable all interrupts to ensure accurate timing */
    __disable_irq ();

    if ( DHT22_Read (&data) == true )
    {
      /* Use data.temperature and data.humidity */
    } else {
      /*
        Error - check response code in data.rcv_response, for more info
        attach debugger and examine impulse times in data.bits[40] (dht22.c)
      */
    }

    __enable_irq ();

    Delay_ms(4000);

  }

}
