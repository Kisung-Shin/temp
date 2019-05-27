#include <stdint.h>
#include <stddef.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MIN(x, y) ((x) < (y)) ? (x): (y)

typedef struct{
       uint32_t timestamp;
       union{
               uint16_t maxBytesSent;
               uint16_t laskIndexSent;
       }cStateValue;
}sdp_cont_state_t;

typedef struct{
       uint8_t* data;
       uint32_t data_size;//4byte
       uint32_t buf_size;//4byte
}sdp_buf_t;

typedef struct _sdp_cstate_list sdp_cstate_list_t;

struct _sdp_cstate_list{
       sdp_cstate_list_t* next;
       uint32_t timestamp;
       sdp_buf_t buf;
};

static int sdp_set_cstate_pdu(sdp_buf_t *buf, sdp_cont_state_t *cstate)
{
       uint8_t *pdata = buf->data + buf->data_size;
       int length = 0;

       if (cstate) {
               //SDPDBG("Non null sdp_cstate_t id : 0x%x", cstate->timestamp);
               *pdata = sizeof(sdp_cont_state_t);
               pdata += sizeof(uint8_t);
               length += sizeof(uint8_t);
               memcpy(pdata, cstate, sizeof(sdp_cont_state_t));
               length += sizeof(sdp_cont_state_t);
       } else {
               /* set "null" continuation state */
               //*pdata = 0;
               length += sizeof(uint8_t);
       }
       buf->data_size += length;
       return length;
}
//extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
int main(){
		uint8_t *Data = 0;
		size_t Size = 0;

       sdp_buf_t* buf1;
       sdp_buf_t* buf2;

       buf1 = (sdp_buf_t*)malloc(sizeof(sdp_buf_t));

       buf2 = (sdp_buf_t*)malloc(sizeof(sdp_buf_t));
       buf2->data = (uint8_t*)"YQR";
       printf("buf2 data         :        %s\n\n",buf2->data);
       //sdp_buf_t *pCache = sdp_get_cached_rsp(cstate);
       sdp_buf_t* pCache;

       pCache = (sdp_buf_t*)malloc(sizeof(sdp_buf_t));
       sdp_cont_state_t* cstate;
       cstate = (sdp_cont_state_t*)malloc(sizeof(sdp_cont_state_t));
       cstate->cStateValue.maxBytesSent = 4;
       short cstate_size = 0;
       uint8_t* pResponse;
       int i=0;
	   buf1->data_size = 0;

       while(i<7)
       {

               pCache->data = (uint8_t*)Data;
               pCache->data_size = (uint32_t)Size;
               printf("pCache -> data    :     %s\n",pCache->data);
               if(pCache /*&& cstate->cStateValue.maxBytesSent < pCache-> data_size*/) {
                       //printf("This is in if\n");
                       uint16_t sent = MIN(4, pCache->data_size - cstate->cStateValue.maxBytesSent);

                       pResponse = pCache->data;

                       memcpy(buf1->data+buf1->data_size, pResponse + cstate->cStateValue.maxBytesSent, sent);
                       buf1->data_size += sent;
                       printf("buf1              :     %s\n",buf1->data);
                       cstate->cStateValue.maxBytesSent += sent;
                       if(cstate->cStateValue.maxBytesSent == pCache->data_size)
                               cstate_size = sdp_set_cstate_pdu(buf1,NULL);
                       else
                               cstate_size = sdp_set_cstate_pdu(buf1,cstate);
               }

               i++;
       }
       return 0;
}