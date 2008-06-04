#ifndef XYGREG_H_
#define XYGREG_H_

#include "sipmsg.h"
#include <prio.h>
#include <string>
using namespace std;
using namespace sip;

namespace xyg {

class msg_reg_1 : public SIPRequest{
    public:
    msg_reg_1();
    msg_reg_1(const string sid, const int id, const int cseq, const string body);

    PRStatus init(const string sid, const int id, const int cseq, const string body);
    
    PRStatus SetSID(string sid);
    PRStatus SetID(int id);
    PRStatus SetCSeq(int cseq);

};

class msg_reg_rsp_1 : public SIPResponse {
    public:
    msg_reg_rsp_1();
    msg_reg_rsp_1(const void* buffer);
    

    string GetNonce();
    int GetID();
    int GetCSeq();
    
};

class msg_reg_2 : public SIPRequest {
    public:
    msg_reg_2();
    msg_reg_2(const string sid, const int id, const int cseq, const string response, const string cnonce, const string body);

    PRStatus init( const string sid, \
    		       const int id, \
    		       const int cseq, \
    		       const string response,\
    		       const string cnonce ,\
    		       const string body);

    PRStatus SetDomain(string domain);
    PRStatus SetSID(string sid);
    PRStatus SetID(int id);
    PRStatus SetCSeq(int cseq);
    PRStatus SetResponse(string response);
    PRStatus SetCnonce(string cnonce);

};

class msg_reg_rsp_2 : public SIPResponse {
    public:
    msg_reg_rsp_2();
    msg_reg_rsp_2(const void* buffer);


    string GetExpiresTime();
    int GetID();
    int GetCSeq();
};


class msg_reg_3 : public SIPRequest {
    public:
	msg_reg_3();
    msg_reg_3(const string sid, const int id, const int cseq);

    PRStatus init(const string sid, const int id, const int cseq);
    
    PRStatus SetSID(string sid);
    PRStatus SetID(int id);
    PRStatus SetCSeq(int cseq);
};

class msg_reg_rsp_3 : public SIPResponse {
    public:
    msg_reg_rsp_3();
    msg_reg_rsp_3(const void* buffer);

    string GetExpiresTime();
    int GetID();
    int GetCSeq();	
};

class msg_unreg_1 : public SIPRequest {
    public:
    msg_unreg_1();
    msg_unreg_1(string sid, int id, int cseq);
    PRStatus init(string sid, int id, int cseq);
    
    PRStatus SetSID(string sid);
    PRStatus SetID(int id);
    PRStatus SetCSeq(int cseq);
};

class msg_unreg_rsp_1 : public SIPResponse {
    public:
    msg_unreg_rsp_1();
    msg_unreg_rsp_1(void *buffer);
    
    int GetID();
    int GetCSeq();
};



};



#endif /*XYGREG_H_*/
