#ifndef SIPSTARTLN_H_
#define SIPSTARTLN_H_
#include <string>
#include <prio.h>
using namespace std;

namespace sip {

class SIPStartLine {
    public:
    virtual string content() = 0;
    
    protected:
    string _raw;
};

class RequestLine:public SIPStartLine {
    public:
    RequestLine();
    RequestLine(const void *buffer);
    RequestLine(const string method, const string uri, const string version);
    string content();
    PRStatus init(const void *buffer);
    PRStatus init(const string method, const string uri, const string version);
    PRStatus SetMethod(const string method);
    PRStatus SetUri(const string uri);
    PRStatus SetVersion(const string version);
    string GetMethod();
    string GetUri();
    string GetVersion();
    
    
    private:
    string _method;
    string _uri;
    string _version;
};

class ResponseLine:public SIPStartLine {
    public:
    ResponseLine();
    ResponseLine(const void *buffer);
    ResponseLine(const string version, const string status, const string reason);
    string content();
    
    PRStatus init(const void *buffer);
    PRStatus init(const string version, const string status, const string reason);
    
    PRStatus SetVersion(const string version);
    PRStatus SetStatus(const string status);
    PRStatus SetReason(const string reason);
    
    string GetVersion();
    string GetStatus();
    string GetReason();
    
    private:
    string _version;
    string _status;
    string _reason;

};

};
#endif /*SIPSTARTLN_H_*/
