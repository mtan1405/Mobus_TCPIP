#include "modbus_tcp.h"
#include "define_modbus.h"

#include <fsl_debug_console.h>
#include <test_modbus/modbus_lwip_/lwip_modbus.h>

#include <test_modbus/modbus_lwip_/lwip_err_.h>

static int connected = 0; 
int err = 0 ; 
 modbus_backend_type modbus_backend = {
	.backend_type    =  MODBUS_BACKEND_TYPE_TCP		,
	.header_length   =  MODBUS_TCP_HEADER_LENGTH	,
	.checksum_length =  MODBUS_TCP_CHECKSUM_LENGTH	,
	.max_adu_length  =  MODBUS_TCP_MAX_ADU_LENGTH	,
	.client = NULL ,
	
};
 modbus_tcp_t modbus_tcp = {
	 .port = 0,
	 .t_id = 0,
 };
 static int modbus_set_slave(modbus_t*  , int ); // set id mbap header 
 static int modbus_read_registers(modbus_t*, int addr, int nb, unsigned short*); // read holding register 
 static int read_registers(modbus_t*, int function, int addr, int nb, unsigned short*); // read register  ( have to set function ) 
 static int  build_request_basis  (modbus_t* ctx, int function, int addr, int nb, char * req); // build request register 
 static int _modbus_tcp_send_msg_pre(unsigned char* req, int req_length);  // build length mbap
 static int send_msg(modbus_t* ctx, unsigned char * msg, int msg_length) ;
modbus_t* modbus_new_tcp() {
	modbus_t* ctx =  (modbus_t*)malloc(sizeof(modbus_t));
	//	NULL;
	if (ctx == NULL) {
		
	}
	else
	{
		ctx->backend = &modbus_backend;
		ctx->backend_data = &modbus_tcp;
		
	}
	return ctx; 
}

int mobus_request_from(ModbusClient* client , int id, int type, int addr, int numbers) {
	if ((type != COILS && type != DISCRETE_INPUTS && type != HOLDING_REGISTERS && type != INPUT_REGISTERS)
		|| (numbers < 1)) {
		err = EMBEINVAL;
		return 0;
	}
	if (client == NULL || client->_mb == NULL) {
		err = EMBEINVAL;
		return  0; 
	}
	int value_size = (type == COILS || type == DISCRETE_INPUTS) ? sizeof(char) : sizeof(short);
	void* value;
	value  = realloc ( client->_value, numbers * value_size);
	if (value == NULL) {
		err = EMBENOMEM; return 0;
	}
	client->_value = value;
	modbus_set_slave(client->_mb, id);
	int result2 = 0;
	switch (type)
	{
	case COILS :
		break;
	case DISCRETE_INPUTS :
		break;
	case HOLDING_REGISTERS :
		result2 = modbus_read_registers(client->_mb, addr, numbers, client->_value);
		break;
	case INPUT_REGISTERS :
		break;
	default:
		break;
	}
	vTaskDelay(pdMS_TO_TICKS(1000));
	PRINTF ("result2_1 =%d  \r\n" , 	result2) ;
	vTaskDelay(pdMS_TO_TICKS(1000));
	PRINTF ("result2_2 =%d   \r\n" , 	result2) ;
	if (result2 ==  SIGNAL_CLOSE_CONNECT ){
		client->connected = 0 ;
		PRINTF ("\r\n   close connected    " ) ;
		modbus_close (client) ;
	}
	//PRINTF (" result  =%d  \r\n" , result2) ;
	return result2 ;

}

int modbus_set_slave(modbus_t* mb ,int slave ) {
	mb->slave = slave; 
	return slave; 

}
int modbus_read_registers(modbus_t* ctx, int addr, int nb, unsigned short* dest) {
	if (nb > MODBUS_MAX_READ_REGISTERS) {
		err = EMBMDATA; 
		return -1;
	}
	int status = 0;
	status = read_registers(ctx, MODBUS_FC_READ_HOLDING_REGISTERS, addr, nb, dest);
	return status;
}



int read_registers(modbus_t* ctx , int function, int addr, int nb, unsigned short* dest ) {
	int rc = -1 ; 
	int request_lengths;  
	unsigned char req[_MIN_REQ_LENGTH];
	memset(req , 0 , _MIN_REQ_LENGTH);
	unsigned char  rsp [MAX_MESSAGE_LENGTH ] ;
	memset (rsp , 0 , MAX_MESSAGE_LENGTH) ;
	request_lengths = build_request_basis(ctx, function, addr, nb, req);
	rc = send_msg(ctx, req, request_lengths); //send msg
	if (rc == -1 ) {
		return  SIGNAL_CLOSE_CONNECT ;
	}
	// get data from lwip 

	rc = modbus_read(ctx, rsp, MAX_MESSAGE_LENGTH)  ;
	if (rc == -1 )  {
		// Check timeout ;
		return SIGNAL_CLOSE_CONNECT ;
	}
	rc = check_confirmation (ctx ,req , rsp ,rc ) ;
	return rc; 
}


  int  build_request_basis(modbus_t* ctx, int function, int addr, int nb, char* req) {
	  modbus_tcp_t* modbus_tcp = ctx->backend_data; 
	  if (modbus_tcp->t_id < UINT16_MAX) {
		  modbus_tcp->t_id++; 
	  }
	  else
	  {
		  modbus_tcp->t_id = 0;
	  }
	  req[0] = modbus_tcp->t_id >> 8;
	  req[1] = modbus_tcp->t_id & 0x00ff;

	  /* Protocol Modbus */
	  req[2] = 0;
	  req[3] = 0;

	  /* Length will be defined later by set_req_length_tcp at offsets 4
		 and 5 */

	  
	  req[6] = ctx->slave;
	  req[7] = function;
	  req[8] = addr >> 8;
	  req[9] = addr & 0x00ff;
	  req[10] = nb >> 8;
	  req[11] = nb & 0x00ff;


	  return _MODBUS_TCP_PRESET_REQ_LENGTH;
	  
}

// buid lenghth for request in MBAP Header 
  static int _modbus_tcp_send_msg_pre(unsigned char * req, int req_length)
  {
	 
	  int mbap_length = req_length - 6;

	  req[4] = mbap_length >> 8;
	  req[5] = mbap_length & 0x00FF;

	  return req_length;
  }
  static int send_msg(modbus_t* ctx, unsigned char * msg, int msg_length) {
	  int rc, i;
	  _modbus_tcp_send_msg_pre(msg, msg_length);
	  if (ctx->debug == 1)
	  {
		  PRINTF("\n\r " );
	  for (int i = 0; i < msg_length; i++) {
		  PRINTF("%X   ", msg [i]);
	  }
	  	  PRINTF("\n\r" );
	  }
	   rc =  modbus_wirte(ctx, msg, msg_length) ;
	  if (rc >0 && rc != msg_length){
		  err = EMBBADDATA ;
		  rc = -1 ;
	  }
	  return rc ;

  }
  const char* get_last_modbus_err_string(int  error) {
	  switch (error) {
	  case EMBOK:
		  return "No error";
	  case EMBXILFUN:
		  return "Illegal function";
	  case EMBXILADD:
		  return "Illegal data address";
	  case EMBXILVAL:
		  return "Illegal data value";
	  case EMBXSFAIL:
		  return "Slave device failure";
	  case EMBXACK:
		  return "Acknowledge";
	  case EMBXSBUSY:
		  return "Slave device is busy";
	  case EMBXNACK:
		  return "Negative acknowledge";
	  case EMBXMEMPAR:
		  return "Memory parity error";
	  case EMBXGPATH:
		  return "Gateway path unavailable";
	  case EMBXGTAR:
		  return "Gateway target device failed to respond";
	  case EMBBADCRC:
		  return "Bad CRC checksum";
	  case EMBBADDATA:
		  return "Bad data";
	  case EMBBADEXC:
		  return "Gateway device failed to execute";
	  case EMBMDATA:
		  return "Gateway device reports data error";
	  case EMBBADSLAVE:
		  return "Slave device is not responding";
	  case EMBEINVAL:
		  return "Invalid parameter";
	  case EMBENOMEM:
		  return "Insufficient memory";
	  default:
		  return "Unknown error code";
	  }
  }
