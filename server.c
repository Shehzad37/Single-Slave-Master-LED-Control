
#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "net/nullnet/nullnet.h"
#include "net/netstack.h"

/**

Desc :  Deceleration of process name

**/


PROCESS(server_node_process, "Server Node Process");

/**

Desc : This indicates that process will auto start right after the execution

**/

AUTOSTART_PROCESSES(&server_node_process);

/**

Method : PROCESS_THREAD

Desc : This includes the actual function of process

**/


PROCESS_THREAD(server_node_process, ev, data) {

  int   i =  rand()%3; // getting random number in range of 3
  nullnet_buf = (uint8_t *)&i; // type caste i into uint8_t and setting it to nullnet buffer
  nullnet_len = 2; // setting nullnet length

  static struct etimer timer; // timer for process cycle

  PROCESS_BEGIN(); // process start point

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 1);

    // getting process into non ending cycle

    while(1) {

        memcpy(nullnet_buf, &i, sizeof(i));  // copying value of i and size to nullnet buffer
        nullnet_len = sizeof(i); // setting nullnet buffer size

        NETSTACK_NETWORK.output(NULL); // broadcasting value of i

    /**

       Switching LEDS with random values

    **/

    switch (i) {
        case 0:
            leds_off(LEDS_GREEN);
            leds_off(LEDS_YELLOW);
            leds_on(LEDS_RED);
            break;
        case 1:
            leds_off(LEDS_RED);
            leds_off(LEDS_YELLOW);
            leds_on(LEDS_GREEN);
            break;
        case 2:
            leds_off(LEDS_RED);
            leds_off(LEDS_GREEN);
            leds_on(LEDS_YELLOW);
            break;

        }

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        etimer_reset(&timer);
    }

      PROCESS_END(); // process end point


}