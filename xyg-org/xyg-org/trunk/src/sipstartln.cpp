#include "include/sipstartln.h"
#include "include/utils.h"
#include <string>
#include <iostream>
using namespace std;
using namespace sip;

RequestLine::RequestLine() {
}

RequestLine::RequestLine(const void *buffer) {
    init(buffer);
}

RequestLine::RequestLine(const string method, const string uri, const string version) {
    init(method, uri, version);
}

PRStatus RequestLine::init(const void *buffer) {
    _raw.assign((char*)buffer);
    
    int i = 0, j = 0, k = 0;
    i = _raw.find(" ", 0);
    j = _raw.find(" ", i+1);
    k = _raw.find("\r\n", j+1);
    
    _method = _raw.substr(0, i-0);
    _uri    = _raw.substr(i+1, j-i-1);
    _version= _raw.substr(j+1, k-j-1);

    return PR_SUCCESS;
}
PRStatus RequestLine::init(const string method, const string uri, const string version) {
    SetMethod(method);
    SetUri(uri);
    SetVersion(version);
    return PR_SUCCESS;
}


string RequestLine::GetMethod() {
    return _method;
}
string RequestLine::GetUri() {
    return _uri;
}
string RequestLine::GetVersion() {
    return _version;
}

PRStatus RequestLine::SetMethod(const string method) {
    string tmp = method;
    _method = trim(tmp);
    _raw = _method + " " + _uri + " " + _version + "\r\n";
    return PR_SUCCESS;
}

PRStatus RequestLine::SetUri(const string uri) {
    string tmp = uri;
    _uri = trim(tmp);
    _raw = _method + " " + _uri + " " + _version + "\r\n";
    return PR_SUCCESS;
}

PRStatus RequestLine::SetVersion(const string version) {
    string tmp = version;
    _version = trim(tmp);
    _raw = _method + " " + _uri + " " + _version + "\r\n";
    return PR_SUCCESS;
}

string RequestLine::content(){
    _raw = _method + " " + _uri + " " + _version + "\r\n";
    return _raw;
}


/* implementation for class ResponseLine */

ResponseLine::ResponseLine() {
}

ResponseLine::ResponseLine(const void *buffer) {
    init(buffer);
}

ResponseLine::ResponseLine(const string version, const string status, const string reason) {
    init(version, status, reason);
}

PRStatus ResponseLine::init(const void *buffer) {
    _raw.assign((char*)buffer);
    
    int i = 0, j = 0, k = 0;
    i = _raw.find(" ", 0);
    j = _raw.find(" ", i+1);
    k = _raw.find("\r\n", j+1);
    
    _version = _raw.substr(0, i-0);
    _status  = _raw.substr(i+1, j-i-1);
    _reason  = _raw.substr(j+1, k-j-1);

    return PR_SUCCESS;
}
PRStatus ResponseLine::init(const string version, const string status, const string reason) {
    SetVersion(version);
    SetStatus(status);
    SetReason(reason);
    return PR_SUCCESS;
}


string ResponseLine::content(){
    _raw = _version + " " + _status + " " + _reason + "\r\n";
    return _raw;
}

string ResponseLine::GetStatus() {
    return _status;
}
string ResponseLine::GetReason() {
    return _reason;
}
string ResponseLine::GetVersion() {
    return _version;
}

PRStatus ResponseLine::SetStatus(const string status) {
    string tmp = status;
    _status = trim(tmp);
    _raw = _version + " " + _status + " " + _reason + "\r\n";
    return PR_SUCCESS;
}

PRStatus ResponseLine::SetReason(const string reason) {
    string tmp = reason;
    _reason = trim(tmp);
    _raw = _version + " " + _status + " " + _reason + "\r\n";
    return PR_SUCCESS;
}

PRStatus ResponseLine::SetVersion(const string version) {
    string tmp = version;
    _version = trim(tmp);
    _raw = _version + " " + _status + " " + _reason + "\r\n";
    return PR_SUCCESS;
}
