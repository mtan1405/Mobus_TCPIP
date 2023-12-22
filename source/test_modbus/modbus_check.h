#pragma once
#include "modbus_tcp.h"
int check_confirmation(modbus_t* ctx, unsigned char* req,
    unsigned char* rsp, int rsp_length);
