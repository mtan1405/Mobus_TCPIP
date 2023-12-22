#include <test_modbus/modbus_thread/modbus_connect.h>
#include "lwipopts.h"
#include "test_modbus/modbus_tcp.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "FreeRTOS.h"
#include <test_modbus/modbus_lwip_/lwip_err_.h>
#include <test_modbus/define_modbus.h>




static void modbus_thread (void *) ;
void task_modbus_init () {
	sys_thread_new("modbus_thread", modbus_thread, NULL , DEFAULT_THREAD_STACKSIZE ,DEFAULT_THREAD_PRIO ) ;
}
void modbus_thread (void *) {
ModbusClient client ;
struct sockaddr_in  addr_serve ;
memset(&client , 0 , sizeof (client)) ;
//addr_serve.sin_family = AF_INET ;
//addr_serve.sin_len	 = sizeof (struct sockaddr_in) ;
//addr_serve.sin_port  = htons (30) ;
//inet_pton(AF_INET , "192.168.1.178" ,&(addr_serve.sin_addr.s_addr)) ;




/*client._mb->s = lwip_socket(AF_INET, SOCK_STREAM, 0) ;
if (client._mb->s == -1) {
	vTaskDelete(NULL) ;
}
int c = lwip_connect(client._mb->s, (struct sockaddr * ) & addr_serve , sizeof (addr_serve)) ;
PRINTF (" status = %d , %s \n" , c , get_string_erro(errno) ) ;
vTaskDelay(pdMS_TO_TICKS(1000));
uint8_t mem[1500] ;
struct timeval timeout = {.tv_usec = 50 * 1000, .tv_sec = 0};



lwip_setsockopt(client._mb->s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
unsigned char req[] = { 0x00,0xD5 , 0x00,0x00 ,0x00, 0x06, 0x03, 0x03, 0x00 , 0x00,  0x00, 0x0A };
while (1){
		int status_write =lwip_write(client._mb->s, req , sizeof (req));
		if (status_write != -1 ){
			int status_read = lwip_read(client._mb->s, mem, 1500) ;
			PRINTF ("status_read = %d" , status_read);
		}else {
			 PRINTF ("err = %s" ,   get_string_erro(errno));
		}
		PRINTF("_\n");
		vTaskDelay(pdMS_TO_TICKS(1000)) ;
}*/

	modbus_client_intit (&client) ;
while (1){
	if (!modbus_connected(&client))
	modbus_begin(&client, "192.168.1.178", 502) ;
	else {
	mobus_request_from (&client , 3 , HOLDING_REGISTERS , 0 , 10 )  ;
	PRINTF ("%s \r\n" , get_last_modbus_err_string(err)) ;
	}
	vTaskDelay(pdMS_TO_TICKS(5000)) ;
}
}
