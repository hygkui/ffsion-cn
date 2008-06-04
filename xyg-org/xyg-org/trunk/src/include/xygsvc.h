#ifndef XYGSVC_H_
#define XYGSVC_H_

#include "sipmsg.h"
#include <string>
#include <prio.h>
using namespace std;
using namespace sip;

namespace xyg {

class msg_svc_getpersonalinfo : public SIPRequest {
    public:
    msg_svc_getpersonalinfo();
    msg_svc_getpersonalinfo(string sid, string id, string cseq, string body);
    
    PRStatus init(string sid, string id, string cseq, string body);
    PRStatus SetSid(string sid);
    PRStatus SetID(string id);
    PRStatus SetCSeq(string cseq);

};

class msg_svc_rsp_getpersonalinfo : public SIPResponse {
    public:
    msg_svc_rsp_getpersonalinfo();
    msg_svc_rsp_getpersonalinfo(const void *buffer);

};

};
#endif /*XYGSVC_H_*/
