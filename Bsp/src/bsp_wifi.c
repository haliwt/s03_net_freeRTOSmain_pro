#include "bsp.h"


uint8_t (*wifi_link_net_state)(void);

static uint8_t wifi_link_net_fun(void);


void wifi_init(void)
{

    wifi_link_net_handler(wifi_link_net_fun);


}



void wifi_link_net_handler(uint8_t (wifi_link_net_state_handler)(void))
{

   wifi_link_net_state = wifi_link_net_state_handler;

}

static uint8_t wifi_link_net_fun(void)
{
     if(net_t.wifi_link_net_success ==1) return 1;
     else 
        return 0;


}


void Wifi_Link_Tencent_Net_State(void)
{

   HAL_UART_Transmit(&huart2, "AT+TCMQTTSTATE?\r\n", strlen("AT+TCMQTTSTATE?\r\n"), 5000);

   //AT+CWRECONNCFG?
 //  HAL_UART_Transmit(&huart2, "AT+CWRECONNCFG?\r\n", strlen("AT+CWRECONNCFG?\r\n"), 5000);
 
  
}

/*****************************************************************************
    *
    *Function Name: static void AutoReconnect_Wifi_Neware_Function(void)
    *Function: 
    *Input Ref: NO
    *Return Ref:NO
    *
*****************************************************************************/	 	
void link_wifi_net_handler(void)
{

  
   

        switch( gpro_t.link_net_step){

            case 0: //one step

                WIFI_IC_DISABLE();
        		HAL_Delay(1000);
        		//HAL_Delay(1000);
        		//HAL_Delay(1000);
        		WIFI_IC_ENABLE();
        		//at_send_data("AT+RESTORE\r\n", strlen("AT+RESTORE\r\n"));
        		at_send_data("AT+RST\r\n", strlen("AT+RST\r\n"));
        		HAL_Delay(1000);

                 gpro_t.link_net_step = 1;

            break;

            case 1:
                    WIFI_IC_ENABLE();
                 	HAL_UART_Transmit(&huart2, "AT+CWMODE=3\r\n", strlen("AT+CWMODE=3\r\n"), 5000);
                	
                   
        		
        			
        			gctl_t.randomName[0]=HAL_GetUIDw0();
                    gpro_t.gTimer_link_net_timer_time = 0;
                    
		            gpro_t.link_net_step = 2;

            break;

            case 2:
                 if(gpro_t.gTimer_link_net_timer_time  > 3){
                     gpro_t.gTimer_link_net_timer_time = 0;

                         WIFI_IC_ENABLE();
            			
                        sprintf((char *)device_massage, "AT+TCPRDINFOSET=1,\"%s\",\"%s\",\"UYIJIA01-%d\"\r\n", PRODUCT_ID, DEVICE_SECRET,gctl_t.randomName[0]);
            			usart2_flag = at_send_data(device_massage, strlen((const char *)device_massage));
            	  		HAL_Delay(1000);
                    
                      
	        
			
		
 

                      gpro_t.link_net_step = 3;

                 }

            break;


            case 3:
                
            if(gpro_t.gTimer_link_net_timer_time  > 8){
                      gpro_t.gTimer_link_net_timer_time = 0;

             WIFI_IC_ENABLE();
			
            sprintf((char *)device_massage, "AT+TCPRDINFOSET=1,\"%s\",\"%s\",\"UYIJIA01-%d\"\r\n", PRODUCT_ID, DEVICE_SECRET,gctl_t.randomName[0]);
			usart2_flag = at_send_data(device_massage, strlen((const char *)device_massage));
	  		HAL_Delay(1000);
        
          
         
	        
			gctl_t.wifi_config_net_lable=wifi_set_tcdevreg;



               gpro_t.link_net_step = 4;

              }



            break;


            case 4:
                 if(gpro_t.gTimer_link_net_timer_time  > 10){
                               gpro_t.gTimer_link_net_timer_time = 0;

                   net_t.linking_tencent_cloud_doing =1;
                  wifi_t.soft_ap_config_flag =1; //WE.EIDT 
	            sprintf((char *)device_massage, "AT+TCSAP=\"UYIJIA01-%d\"\r\n",gctl_t.randomName[0]);
                usart2_flag = at_send_data(device_massage, strlen((const char *)device_massage));


                   gpro_t.link_net_step = 5;


                    }

            break;


            case 5:
                

                   if(net_t.soft_ap_config_success==1){

                       net_t.soft_ap_config_success=0;
                	   HAL_UART_Transmit(&huart2, "AT+TCMQTTCONN=1,5000,240,0,1\r\n", strlen("AT+TCMQTTCONN=1,5000,240,0,1\r\n"), 5000);//开始连接
                       HAL_Delay(1000);
                       HAL_Delay(1000);
                       ///HAL_Delay(1000);
       
	 
                    }

               
            break;







        }



    



}




