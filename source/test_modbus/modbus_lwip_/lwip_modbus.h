/*
 * lwip_modbus.h
 *
 *  Created on: Sep 15, 2023
 *      Author: os
 */
#include "test_modbus/modbus_check.h"
#pragma once
int modbus_client_intit (ModbusClient* client) ;
int modbus_connected (ModbusClient * client) ;
int modbus_connect (ModbusClient * client , const char * , uint16_t port ) ;
int modbus_begin (ModbusClient * , const char * , uint16_t port ) ;
int modbus_read (modbus_t * , uint8_t * rsp , u32_t lenght ) ;
int modbus_close (ModbusClient * client ) ;
int modbus_wirte (modbus_t * client , uint8_t * req, u32_t lenght ) ;
int modbus_close_2 (modbus_t * client ) ;
int modbus_set_re_timeout (int s , long    second , long    msecond  ) ;

