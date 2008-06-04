#ifndef SIPHEADER_H_
#define SIPHEADER_H_

#include <prio.h>
#include <vector>
#include <string>
using namespace std;

namespace sip {

class SIPHeaderLine {
    public:
    string content();
    SIPHeaderLine();
    SIPHeaderLine(const void *buffer);
    SIPHeaderLine(const string field, const string value);
    SIPHeaderLine(const string field, const int value);
    
    PRStatus init(const void *buffer);
    PRStatus init(const string field, const string value);
    PRStatus init(const string field, const int value);
    
    PRStatus SetField(const string field);
    PRStatus SetValue(const string value);
    PRStatus SetValue(const int value);
    
    string GetField();
    string GetValue();
    
    
    private:
    string _raw; 
    string _field;
    string _value;
};

class SIPHeader {
    public:
    SIPHeader();
    SIPHeader(const void *buffer);
    
    PRStatus init(const void *buffer);
    string content();
    PRStatus append(const SIPHeaderLine hdln);
    PRStatus modify(const string field, const string value);
    PRStatus modify(const string field, const int value);
    PRStatus remove(const string field);
    string   GetValue(const string field);
    
	
    private:
    vector<SIPHeaderLine> _header;
};

};

#endif /*SIPHEADER_H_*/
