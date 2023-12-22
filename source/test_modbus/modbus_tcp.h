#pragma once
#include "lwip/sockets.h"
typedef struct modbus modbus_t;
typedef struct mb_client ModbusClient_t ;
typedef struct {
	int port;
	unsigned long t_id;

} modbus_tcp_t;
typedef struct modbus_backend {
	unsigned int backend_type;
	unsigned int header_length;
	unsigned int checksum_length;
	unsigned int max_adu_length;
	int connected ;
	int (*check_connection) ();
	int (*build_request_basis) (modbus_t*, int function, int addr, int  number, char* req);
	int (*send_msg_pre)  (unsigned char*, int);
	ModbusClient_t * client  ;
} modbus_backend_type;

// int tcp_build_request_basis (modbus_t* ctx, int function, int addr, int nb, unsigned char* req);

struct modbus {
	int id;
	int debug;
	int slave; // addr for slave 
	int s;  // number of socket description 
	modbus_tcp_t* backend_data;
	modbus_backend_type* backend;
};


typedef struct mb_client {
	// attribute 

	modbus_t* _mb;
	void* _value;
	int connected ;
	struct sockaddr_in  addr_serve ;

	// method 
	int (*holdingResRead) (unsigned int id, unsigned int  address, char* data, unsigned int length);
	int (*inputResRead) (unsigned int id, unsigned int  address, char* data, unsigned int length);


} ModbusClient;

// define modbus_backed 
extern  modbus_backend_type modbus_backend;
extern int err;

// define function 

modbus_t* modbus_new_tcp() ; 
int mobus_request_from(ModbusClient*, int id, int type, int addr, int number);
