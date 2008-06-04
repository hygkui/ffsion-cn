#include "include/recv.h"
#include "include/global.h"
#include "include/sipmsg.h"
#include "include/libxyg.h"
#include <cstdlib>
#include <string>
using namespace std;

extern TCPConnection TCPCONN;
extern ServiceConnector *SRVCONN;

RecvThread::RecvThread() {
    
}


/* the function that determines what a data packet is
 * a sip requst or a sip response.
 * 
 * Return Value:
 * 1: A request packet
 * 0: A response packet
 */
int Type(void *buf) {
   string packet((char*)buf);
   int ret = packet.find(" ", 0);
   return (ret==1);
}

void PR_CALLBACK RecvProgress(void* arg) {
    TCPConnection conn = TCPCONN;
    void *buf = malloc(RECV_BUFFER_SIZE); 
    while(1) {
        /* clean the buffer */
        memset(buf, 0, RECV_BUFFER_SIZE);
        
        /* block if no data reaches */
        conn.Receive(buf);
        
        /* some data reaches */
        
        
        /* first determine the type of packet */
        if(Type(buf) == 0) {
            sip::SIPResponse packet(buf);
            string strid = packet.GetHeader().GetValue("I");
            int id = atoi(strid.c_str());
            Transaction trans = SRVCONN->GetTransQ().GetTransaction(id);
            Command cmd(trans.GetType(), trans.GetTargetsid(), packet.content());
            SRVCONN->GetTransQ().SetCommand(id, cmd);
            SRVCONN->GetTransQ().DoTransaction(id);
        } else {
            sip::SIPRequest packet(buf);
        }
     
    }

}

void RecvThread::run() {
    _thread = PR_CreateThread(PR_USER_THREAD,
            RecvProgress,
            NULL,
            PR_PRIORITY_NORMAL,
            PR_LOCAL_THREAD,
            PR_JOINABLE_THREAD,
            0);
}


