#pragma once
#define MODBUS_BACKEND_TYPE_TCP 	1 
#define MODBUS_TCP_HEADER_LENGTH 	7 
#define MODBUS_TCP_CHECKSUM_LENGTH 	0 
#define MODBUS_TCP_MAX_ADU_LENGTH 	260



#define COILS 				0 
#define DISCRETE_INPUTS 	1
#define HOLDING_REGISTERS	2
#define INPUT_REGISTERS		3

#define MODBUS_MAX_READ_REGISTERS          125
#define MODBUS_MAX_WRITE_REGISTERS         123
#define MODBUS_MAX_WR_WRITE_REGISTERS      121
#define MODBUS_MAX_WR_READ_REGISTERS       125


// define  function of modbus  
#define MODBUS_FC_READ_COILS                0x01
#define MODBUS_FC_READ_DISCRETE_INPUTS      0x02
#define MODBUS_FC_READ_HOLDING_REGISTERS    0x03
#define MODBUS_FC_READ_INPUT_REGISTERS      0x04
#define MODBUS_FC_WRITE_SINGLE_COIL         0x05
#define MODBUS_FC_WRITE_SINGLE_REGISTER     0x06
#define MODBUS_FC_READ_EXCEPTION_STATUS     0x07
#define MODBUS_FC_WRITE_MULTIPLE_COILS      0x0F
#define MODBUS_FC_WRITE_MULTIPLE_REGISTERS  0x10
#define MODBUS_FC_REPORT_SLAVE_ID           0x11
#define MODBUS_FC_MASK_WRITE_REGISTER       0x16
#define MODBUS_FC_WRITE_AND_READ_REGISTERS  0x17

#define _MIN_REQ_LENGTH 12 
#define _REPORT_SLAVE_ID 180
#define MAX_MESSAGE_LENGTH 260


#define _MODBUS_TCP_PRESET_REQ_LENGTH 12
#define UINT16_MAX 0xFFFF


#define SIGNAL_CLOSE_CONNECT  30000

#define MSG_LENGTH_UNDEFINED -1 

typedef enum {
	EMBOK,
	EMBXILFUN = 0x01,
	EMBXILADD = 0x02,
	EMBXILVAL = 0x03,
	EMBXSFAIL = 0x04,
	EMBXACK   = 0x05,
	EMBXSBUSY = 0x06,
	EMBXNACK    ,
	EMBXMEMPAR = 0x08, 
	EMBXGPATH  = 0x0A,
	EMBXGTAR   = 0x0B,
	EMBBADCRC,
	EMBBADDATA,
	EMBBADEXC,
	EMBMDATA,
	EMBBADSLAVE,
	EMBEINVAL,
	EMBENOMEM
} ModbusErr;

enum {
	MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
	MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
	MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,
	MODBUS_EXCEPTION_ACKNOWLEDGE,
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,
	MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,
	MODBUS_EXCEPTION_MEMORY_PARITY,
	MODBUS_EXCEPTION_NOT_DEFINED,
	MODBUS_EXCEPTION_GATEWAY_PATH,
	MODBUS_EXCEPTION_GATEWAY_TARGET,
	MODBUS_EXCEPTION_MAX
};


const char* get_last_modbus_err_string(int  error); 
