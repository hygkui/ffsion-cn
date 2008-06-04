#ifndef SIP_H_
#define SIP_H_
#include <string>
#include "sipstartln.h"
#include "sipheader.h"
using namespace std;

namespace sip {

class SIPMessage {
    public:
    virtual string content() = 0;
    
    protected:
    string _raw;
    string _body;
    SIPHeader _header;

};

class SIPResponse: public SIPMessage {
    public:
    SIPResponse();
    SIPResponse(const void *buffer);
    SIPResponse(const ResponseLine line, const SIPHeader header, const string body);
    
    PRStatus init(const void *buffer);
    PRStatus init(const ResponseLine line, const SIPHeader header, const string body);
    
    PRStatus SetStartline(const ResponseLine line);
    PRStatus SetHeader(const SIPHeader header);
    PRStatus SetBody(const string body);
    
    ResponseLine GetStartline();
    string GetStatus();
    string GetReason();
    string GetVersion();
    SIPHeader GetHeader();
    string GetBody();
    
    virtual string content();
    
    protected:
    ResponseLine _startline;

};

class SIPRequest: public SIPMessage {
    public:
    SIPRequest();
    SIPRequest(const void *buffer);
    SIPRequest(const RequestLine line, const SIPHeader header, const string buffer);
    
    PRStatus init(const void *buffer);
    PRStatus init(const RequestLine line, const SIPHeader header, const string body);
    
    PRStatus SetStartline(const RequestLine line);
    PRStatus SetHeader(const SIPHeader header);
    PRStatus SetBody(const string body);
    
    RequestLine GetStartline();
    SIPHeader GetHeader();
    string GetBody();
    
    virtual string content();
    
    protected:
    RequestLine _startline;
};

};



#endif /*SIP_H_*/
