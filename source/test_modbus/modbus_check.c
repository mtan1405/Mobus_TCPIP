#include "modbus_check.h"
#include "define_modbus.h"

//defince function 
// 

static unsigned int compute_response_length_from_request(modbus_t* ctx, unsigned char* req);
static int _modbus_tcp_pre_check_confirmation(modbus_t* ctx, const unsigned char* req, const unsigned char* rsp, int rsp_length);
int check_confirmation(modbus_t* ctx, unsigned char* req,
unsigned char* rsp, int rsp_length)
{
    int rc = 0;
    int rsp_length_computed;
    const int offset = ctx->backend->header_length;
    const int function = rsp[offset];
    if (ctx->backend_data != 0 ) {
      int a=  _modbus_tcp_pre_check_confirmation(ctx, req, rsp, rsp_length);
      if (a == -1) {
          if (ctx->debug) {
              //log debug overhere
          }
          err = EMBBADDATA;
          return -1;
      }
    }

    rsp_length_computed = compute_response_length_from_request(ctx, req);

    //check Exception code 
    if (function >= 0x80) {
        if (rsp_length == (2 + offset + ctx->backend->checksum_length)
            && (req[offset] == rsp[offset] - 0x80)) {
            int exception_code = rsp[offset + 1];

            err = rsp[offset + 1];

        }
        else {
            err = EMBBADDATA;
        }
        if (ctx->debug) {
            // log debug over here 
        }

            return -1;
    }


    //check length rsp_legnth  = req_length 
    if ((rsp_length == rsp_length_computed || rsp_length_computed == MSG_LENGTH_UNDEFINED)
        && function < 0x80) {
        int rsp_nb_value; 
        int req_nb_value; 
        if (function != req[offset]) {
            err = EMBBADDATA;
            if (ctx->debug) {
                // log debug over here 
            }
            return -1;
        }

        switch (function)
        {
        case MODBUS_FC_READ_COILS:
        case MODBUS_FC_READ_DISCRETE_INPUTS:
            /* Read functions, 8 values in a byte (nb
             * of values in the request and byte count in
             * the response. */
            req_nb_value = (req[offset + 3] << 8) + req[offset + 4];
            req_nb_value = (req_nb_value / 8) + ((req_nb_value % 8) ? 1 : 0);
            rsp_nb_value = rsp[offset + 1];
            break;
        case MODBUS_FC_WRITE_AND_READ_REGISTERS:
        case MODBUS_FC_READ_HOLDING_REGISTERS:
        case MODBUS_FC_READ_INPUT_REGISTERS:
            /* Read functions 1 value = 2 bytes */
            req_nb_value = (req[offset + 3] << 8) + req[offset + 4];
            rsp_nb_value = (rsp[offset + 1] / 2);
            break;
        case MODBUS_FC_WRITE_MULTIPLE_COILS:
        case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
            /* N Write functions */
            req_nb_value = (req[offset + 3] << 8) + req[offset + 4];
            rsp_nb_value = (rsp[offset + 3] << 8) | rsp[offset + 4];
            break;
        case MODBUS_FC_REPORT_SLAVE_ID:
            /* Report slave ID (bytes received) */
            req_nb_value = rsp_nb_value = rsp[offset + 1];
            break;
        default:
            /* 1 Write functions & others */
            req_nb_value = rsp_nb_value = 1;
        
        }

        if (req_nb_value == rsp_nb_value) {
            rc = rsp_nb_value;
            err = EMBOK ;
        }
        else {
            if (ctx->debug) {
                // log debug overhere
            }


            err  = EMBBADDATA;
            rc = -1;
        }

        

    }// err 
    else
    {
        if (ctx->debug) {
            // log debug overhere
        }
        err = EMBBADDATA;
        rc = -1;

    }
    //printf("check success %d", rc);
    return rc;
    }
      
 

static unsigned int compute_response_length_from_request(modbus_t* ctx, unsigned char * req)
{
    int length;
    const int offset = ctx->backend->header_length;

    switch (req[offset]) {
    case MODBUS_FC_READ_COILS:
    case MODBUS_FC_READ_DISCRETE_INPUTS: {
        /* Header + nb values (code from write_bits) */
        int nb = (req[offset + 3] << 8) | req[offset + 4];
        length = 2 + (nb / 8) + ((nb % 8) ? 1 : 0);
    }
                                       break;
    case MODBUS_FC_WRITE_AND_READ_REGISTERS:
    case MODBUS_FC_READ_HOLDING_REGISTERS:
    case MODBUS_FC_READ_INPUT_REGISTERS:
        /* Header + 2 * nb values */
        length = 2 + 2 * (req[offset + 3] << 8 | req[offset + 4]);
        break;
    case MODBUS_FC_READ_EXCEPTION_STATUS:
        length = 3;
        break;
    case MODBUS_FC_REPORT_SLAVE_ID:
        /* The response is device specific (the header provides the
           length) */
        return MSG_LENGTH_UNDEFINED;
    case MODBUS_FC_MASK_WRITE_REGISTER:
        length = 7;
        break;
    default:
        length = 5;
    }

    return offset + length + ctx->backend->checksum_length;
}
int _modbus_tcp_pre_check_confirmation(modbus_t* ctx, const unsigned char* req, const unsigned char* rsp, int rsp_length) {
    if (req[0] != rsp[0] || req[1] != rsp[1]) {
        if (ctx->debug) {
            //log debug over here
        }
        err  = EMBBADDATA;
        return -1;
    }

    /* Check protocol ID */
    if (rsp[2] != 0x0 && rsp[3] != 0x0) {
        if (ctx->debug) {
           //log debug overhere 
        }
        err  = EMBBADDATA;
        return -1;
    }

    return 0;
}
