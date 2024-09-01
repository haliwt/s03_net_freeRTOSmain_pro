#ifndef __BSP_WIFI_H
#define __BSP_WIFI_H
#include "main.h"



extern uint8_t (*wifi_link_net_state)(void);





void wifi_init(void);


void wifi_link_net_handler(uint8_t (wifi_link_net_state_handler)(void));

void Wifi_Link_Tencent_Net_State(void);

void link_wifi_net_handler(void);


#endif 

