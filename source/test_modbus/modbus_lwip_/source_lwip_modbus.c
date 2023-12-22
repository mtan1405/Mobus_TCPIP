
#include "lwip_err_.h"
#include "lwip/errno.h"
#include "lwip_modbus.h"
#include "test_modbus/modbus_tcp.h"

//
//  0,             /* ERR_OK          0      No error, everything OK. */
//  ENOMEM,        /* ERR_MEM        -1      Out of memory error.     */
//  ENOBUFS,       /* ERR_BUF        -2      Buffer error.            */
//  EWOULDBLOCK,   /* ERR_TIMEOUT    -3      Timeout                  */
//  EHOSTUNREACH,  /* ERR_RTE        -4      Routing problem.         */
//  EINPROGRESS,   /* ERR_INPROGRESS -5      Operation in progress    */
//  EINVAL,        /* ERR_VAL        -6      Illegal value.           */
//  EWOULDBLOCK,   /* ERR_WOULDBLOCK -7      Operation would block.   */
//  EADDRINUSE,    /* ERR_USE        -8      Address in use.          */
//  EALREADY,      /* ERR_ALREADY    -9      Already connecting.      */
//  EISCONN,       /* ERR_ISCONN     -10     Conn already established.*/
//  ENOTCONN,      /* ERR_CONN       -11     Not connected.           */
//  -1,            /* ERR_IF         -12     Low-level netif error    */
//  ECONNABORTED,  /* ERR_ABRT       -13     Connection aborted.      */
//  ECONNRESET,    /* ERR_RST        -14     Connection reset.        */
//  ENOTCONN,      /* ERR_CLSD       -15     Connection closed.       */
//  EIO            /* ERR_ARG        -16     Illegal argument.        */
//
// rerturn 1 or 0
char * get_string_erro (int lwip_err ){
	 switch (lwip_err) {
	        case 0:
	            return "No error, everything OK.";
	        case ENOMEM:
	            return "Out of memory error.";
	        case ENOBUFS:
	            return "Buffer error.";
	        case EWOULDBLOCK:
	            return "Timeout or Operation would block..";
	        case EHOSTUNREACH:
	            return "Routing problem.";
	        case EINPROGRESS:
	            return "Operation in progress.";
	        case EINVAL:
	            return "Illegal value.";
	        case EADDRINUSE:
	            return "Address in use.";
	        case EALREADY:
	            return "Already connecting.";
	        case EISCONN:
	            return "Conn already established.";
	        case ENOTCONN:
	            return "Not connected or Connection closed..";
	        case -1 :
	            return "Low-level netif error.";
	        case ECONNABORTED:
	            return "Connection aborted.";
	        case ECONNRESET:
	            return "Connection reset.";
	        case EIO:
	            return "Illegal argument.";
	        default:
	            return "Unknown error code.";
}
}
int modbus_connected (ModbusClient * client) {
	return client->connected  ;
}
int modbus_client_intit (ModbusClient* client)  {
	client->_mb = modbus_new_tcp () ;
	client->_mb->debug = 0 ;
	int s = lwip_socket(AF_INET, SOCK_STREAM, 0) ;
	client->_mb->s  = s ;
	 return s ;
}
int modbus_connect (ModbusClient * client , const char * server , uint16_t port ) {
		client->_mb->s = lwip_socket(AF_INET, SOCK_STREAM, 0) ;
		client->addr_serve.sin_family = AF_INET;
		client->addr_serve.sin_len	= sizeof (struct sockaddr_in) ;
		client->addr_serve.sin_port = htons (port) ;
		modbus_set_re_timeout (client->_mb->s , 10 , 10) ;
		inet_pton(AF_INET , server ,&(client->addr_serve.sin_addr.s_addr)) ;
		int status = lwip_connect (client->_mb->s ,(struct sockaddr * ) &client->addr_serve , sizeof (struct sockaddr  )) ;
		if (!status) client->connected = 1 ;
		else client->connected = 0 ;
		if (client->_mb->debug == 1){
			PRINTF ("Err connected  , status =  %d : %s \n\r", status ,get_string_erro (errno)) ;
		}
		if (status == -1 ){
			modbus_close(client) ;
		}
		return status ;
}
int modbus_begin (ModbusClient *client , const char * server , uint16_t port) {
	int status = modbus_connect (client , server , port) ;
	return status ;
}
int modbus_set_re_timeout (int s , long    second , long    msecond  ) {
	struct timeval tim ;
	tim.tv_sec = second ;
	tim.tv_usec = msecond ;
	lwip_setsockopt(s, SOL_SOCKET , SO_RCVTIMEO ,  &tim , sizeof (tim)) ;
}

int modbus_read (modbus_t * client , uint8_t * rsp , u32_t length ) {
	modbus_t * _mb  = client ;
	int status = lwip_read(_mb->s, rsp , length) ;
	if (status == -1 || status == 0 ) {
			if (_mb->debug == 1){
				PRINTF ("Err read %d  : %s \n\r" , errno, get_string_erro (errno)) ;
			}
	}
	return status ;
}
int modbus_wirte (modbus_t * client , uint8_t * req, u32_t length ) {
	modbus_t * _mb  = client ;
	int status = lwip_write( _mb->s, req, length) ;
	if (status == -1 )
			if ( _mb->debug == 1){
				PRINTF ("Err write  : %s  and status = %d \n\r " , get_string_erro (errno) , status) ;
			}

	return status ;
}
int  modbus_close (ModbusClient * client ){
	client->connected= 0 ;
	return lwip_close(client->_mb->s);
}
int modbus_close_2 (modbus_t * _mb) {
	return lwip_close( _mb->s);
}


