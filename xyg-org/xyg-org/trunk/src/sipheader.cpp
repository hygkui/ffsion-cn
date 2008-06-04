#include "include/sipheader.h"
#include "include/utils.h"
#include <prio.h>
#include <iostream>
using namespace std;
using namespace sip;


SIPHeaderLine::SIPHeaderLine() {
}
SIPHeaderLine::SIPHeaderLine(const void *buffer) {
    init(buffer);
}
SIPHeaderLine::SIPHeaderLine(const string field, const string value) {
    init(field, value);
}
SIPHeaderLine::SIPHeaderLine(const string field, const int value) {
    init(field, value);
}

PRStatus SIPHeaderLine::init(const void *buffer) {
    _raw.assign((char*)buffer);
    int i = 0, j = 0;
    i = _raw.find(":");
    j = _raw.find("\r\n");
    _field = _raw.substr(0, i-0);
    _value = _raw.substr(i+1, j-i-1);
    trim(_field);
    trim(_value);
    return PR_SUCCESS;
}
PRStatus SIPHeaderLine::init(const string field, const string value) {
    SetField(field);
    SetValue(value);
    return PR_SUCCESS;
}

PRStatus SIPHeaderLine::init(const string field, const int value) {
    SetField(field);
    SetValue(value);
    return PR_SUCCESS;
}

PRStatus SIPHeaderLine::SetField(const string field) {
    string tmp = field;
    _field = trim(tmp);
    _raw = _field + ": " + _value + "\r\n"; 
    return PR_SUCCESS;
}
PRStatus SIPHeaderLine::SetValue(const string value) {
    string tmp = value;
    _value = trim(tmp);
    _raw = _field + ": " + _value + "\r\n";
    return PR_SUCCESS;
}

PRStatus SIPHeaderLine::SetValue(const int value) {
    char tmp[20];
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%d", value);
    _value = string(tmp);
    return PR_SUCCESS;
}


string SIPHeaderLine::GetField() {
    return _field;
}
string SIPHeaderLine::GetValue() {
    return _value;
}
string SIPHeaderLine::content() {
    _raw = _field + ": " + _value + "\r\n";
    return _raw;
}


SIPHeader::SIPHeader() {
}

SIPHeader::SIPHeader(const void *buffer) {
    init(buffer);
}

string SIPHeader::content() {
    string r;
    vector<SIPHeaderLine>::iterator it;

    for ( it=_header.begin() ; it < _header.end(); it++ ) {
        r += (*it).content();
    }
    return r;
}


PRStatus SIPHeader::init(const void *buffer) {
    unsigned int i = 0;
    string tmp((char*)buffer);
    while( (i = tmp.find("\r\n", 0)) != string::npos) {
    	//cerr <<tmp.substr(0,i) <<endl;
        append(SIPHeaderLine(tmp.substr(0,i).c_str()));
        tmp.erase(0, i+2);

    }
    return PR_SUCCESS;
}

PRStatus SIPHeader::append(const SIPHeaderLine hdln) {
    _header.push_back(hdln);
    return PR_SUCCESS; 
}

PRStatus SIPHeader::modify(const string field, const string value) {
    vector<SIPHeaderLine>::iterator it;
    int flag = 0;
    
    /* search the headerline */
    for( it = _header.begin() ; it < _header.end(); it++) {
        if( (*it).GetField() == field ) {
        	flag = 1;/* found, set flag*/
        	(*it).SetValue(value);/* modify the value */
        }
    }
    if(flag == 0) { /* not found, append a new one */
        append(SIPHeaderLine(field, value));
    }
    return PR_SUCCESS;
}

PRStatus SIPHeader::modify(const string field, const int value) {
    vector<SIPHeaderLine>::iterator it;
    int flag = 0;
    char tmp[20];
    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "%d", value);
    
    /* search the headerline */
    for( it = _header.begin() ; it < _header.end(); it++) {
        if( (*it).GetField() == field ) {
        	flag = 1;/* found, set flag*/
        	(*it).SetValue(tmp);/* modify the value */
        }
    }
    if(flag == 0) { /* not found, append a new one */
        append(SIPHeaderLine(field, tmp));
    }
    return PR_SUCCESS;
}


string SIPHeader::GetValue(const string field) {
    vector<SIPHeaderLine>::iterator it;
    for( it = _header.begin() ; it < _header.end(); it++) {
        if( (*it).GetField() == field ) {
            return (*it).GetValue();
        }
    }
    return NULL;
}
PRStatus SIPHeader::remove(const string field) {
    vector<SIPHeaderLine>::iterator it;
    for( it = _header.begin() ; it < _header.end(); it++) {
        if( (*it).GetField() == field ) {
            _header.erase(it);
        }
    }
    return PR_SUCCESS;
}
