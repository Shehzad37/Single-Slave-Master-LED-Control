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

PROCESS(client_node_process, "Client Node Process");

/**

Desc : This indicates that process will auto start right after the execution

**/

AUTOSTART_PROCESSES(&client_node_process);

/**
Method : input_callback
Desc :  This method is callback for receiving data from server node

**/

void input_callback(const void *data, uint16_t len,
  const linkaddr_t *src, const linkaddr_t *dest){
    int i;
    memcpy(&i, data, sizeof(i));
    switch (i){
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


}

/**

Method : PROCESS_THREAD

Desc : This includes the actual function of process

**/

PROCESS_THREAD(client_node_process, ev, data) {

  static struct etimer timer; // timer for process cycle

  PROCESS_BEGIN(); // process start point

  etimer_set(&timer, CLOCK_SECOND * 1); // setting time to 1 clock second
  
  nullnet_set_input_callback(input_callback); // fetching data from server node by setting input callback

  // getting process into non ending cycle
  while(1) {

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    etimer_reset(&timer);
  }

  PROCESS_END(); // process end point


}