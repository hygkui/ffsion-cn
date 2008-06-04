#include "include/sipmsg.h"
#include <string>
#include <iostream>
using namespace std;
using namespace sip;

SIPResponse::SIPResponse() {
}

SIPResponse::SIPResponse(const void *buffer) {
    init(buffer);
}

string SIPResponse::content() {
    string ret;
    ret += _startline.content();
    ret += _header.content();
    ret += "\r\n";
    ret += _body;
    return ret;
}

SIPResponse::SIPResponse(const ResponseLine line, const SIPHeader header, const string body) {
    init(line, header, body);
}

PRStatus SIPResponse::init(const void *buffer) {
    /* put original data into _raw */
    _raw.assign((char*)buffer);
    
    /* split data into three parts, 
     * start line, message header and 
     * message body
     */
    int i = 0, j = 0;
    i = _raw.find("\r\n");
    j = _raw.find("\r\n\r\n");
    _startline.init(_raw.substr(0,i).c_str());
    _header.init(_raw.substr(i+2, j-i).c_str());
    if ( (unsigned int)j+4 <= _raw.size() ) {
        _body = _raw.substr(j+4, string::npos);
    } else {
        _body = "";
    }
    return PR_SUCCESS;
}

PRStatus SIPResponse::init(const ResponseLine line, const SIPHeader header, const string body) {
    SetStartline(line);
    SetHeader(header);
    SetBody(body);
    return PR_SUCCESS;
}
    
PRStatus SIPResponse::SetStartline(const ResponseLine line) {
    _startline = line;
    return PR_SUCCESS;
}
PRStatus SIPResponse::SetHeader(const SIPHeader header) {
    _header = header;
    return PR_SUCCESS;
}
PRStatus SIPResponse::SetBody(const string body) {
    _body = body;
    _header.modify("L", body.size());
    return PR_SUCCESS;
}
    
ResponseLine SIPResponse::GetStartline() {
    return _startline;
}
SIPHeader SIPResponse::GetHeader() {
    return _header;
}
string SIPResponse::GetBody() {
    return _body;
}

string SIPResponse::GetStatus() {
    return _startline.GetStatus();
}

string SIPResponse::GetReason() {
    return _startline.GetReason();
}

string SIPResponse::GetVersion() {
    return _startline.GetVersion();
}

/* implementations of class SIPRequest
 * 
 */
SIPRequest::SIPRequest() {
}

SIPRequest::SIPRequest(const void *buffer) {
    init(buffer);
}

string SIPRequest::content() {
    string ret;
    ret += _startline.content();
    ret += _header.content();
    ret += "\r\n";
    ret += _body;
    return ret;
}

SIPRequest::SIPRequest(const RequestLine line, const SIPHeader header, const string body) {
    init(line, header, body);
}

PRStatus SIPRequest::init(const void *buffer) {
    /* put original data into _raw */
    _raw.assign((char*)buffer);
    
    /* split data into three parts, 
     * start line, message header and 
     * message body
     */
    int i = 0, j = 0;
    i = _raw.find("\r\n");
    j = _raw.find("\r\n\r\n");
    _startline.init(_raw.substr(0,i).c_str());
    _header.init(_raw.substr(i+2, j-i-1).c_str());
    if ( (unsigned int)j+4 <= _raw.size() ) {
        _body = _raw.substr(j+4, string::npos);
    } else {
        _body = "";
    }
    return PR_SUCCESS;
}

PRStatus SIPRequest::init(const RequestLine line, const SIPHeader header, const string body) {
    SetStartline(line);
    SetHeader(header);
    SetBody(body);
    return PR_SUCCESS;
}
    
PRStatus SIPRequest::SetStartline(const RequestLine line) {
    _startline = line;
    return PR_SUCCESS;
}
PRStatus SIPRequest::SetHeader(const SIPHeader header) {
    _header = header;
    return PR_SUCCESS;
}
PRStatus SIPRequest::SetBody(const string body) {
    _body = body;
    _header.modify("L", body.size());
    return PR_SUCCESS;
}

RequestLine SIPRequest::GetStartline() {
    return _startline;
}
SIPHeader SIPRequest::GetHeader() {
    return _header;
}
string SIPRequest::GetBody() {
    return _body;
}
