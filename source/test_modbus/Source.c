#include <stdio.h>
#include <stdlib.h>
#include "modbus_tcp.h"
#include "define_modbus.h"
#include "modbus_check.h"
// mobus_request_from

///*
//
//
//int main()
//{
//    ModbusClient client;
//    memset(&client, 0, sizeof(ModbusClient));
//
//
//    client._mb = modbus_new_tcp();
//    //Tx:000042 - 00 D5 00 00 00 06 03 03 00 00 00 0A
//    //Rx : 000043 - 00 D5 00 00 00 17 03 03 14 00 00 00 00 00 00 00 05 00 00 00 00 00 00 00 00 00 00 00 00
//    printf("\n");
//
//    unsigned char req[] = { 0x00,0xD5 , 0x00,0x00 ,0x00, 0x06, 0x03, 0x03, 0x00 , 0x00,  0x00, 0x0A };
//    //unsigned char rsp[] = { 0x00, 0xD5 , 0 , 00, 00, 0x17, 03, 03, 0x14, 00, 00 , 00, 00, 00, 00, 00, 05, 00, 00 ,00 ,00 ,00, 00, 00, 00, 00, 00, 00 ,00 };
//    unsigned char rsp[] = { 0x00, 0xD5 , 0 , 00, 00  ,3 , 3 , 0x83 , 2 };
//    client._mb->backend_data->t_id = 0xD500;
//    mobus_request_from(&client, 3, HOLDING_REGISTERS, 0, 2);
//
//    //int check = check_confirmation(client._mb, req, rsp, sizeof(rsp));
//    //
//    //printf("\n num is %X \n", check);
//    //printf("%s ", get_last_modbus_err_string(err));
//    void* cc = malloc(10);
//    char c =0xff;
////    printf("sizeof malloc %u  ", c);
//    return 0;
//
//}*/
