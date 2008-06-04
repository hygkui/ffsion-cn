#include "include/utils.h"
#include "include/md5.h"
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

/* remove the leading and trailing space(" " or "\t") */
string trim(string& s) {
    int i = 0;
    while( s[i] == ' ' || s[i] == '\t' ) {
        s.erase(i,1);
        if( s[i] != ' ' && s[i] != '\t' ) {
            break;
        }
    }
    i = s.length() - 1;
    while( s[i] == ' ' || s[i] == '\t' ) {
        s.erase(i,1);
        i--;
        if( s[i] != ' ' && s[i] != '\t' ) {
            break;
        }
    }
    return s;
}


string credential(const char *sid, const char *pwd, const char *domain, const char *nonce, const char *cnonce) {
    char *buf = (char*)malloc(1024);
	char *key;
    char *h1;
    char *h2;
    char *response;

    memset(buf, 0, 1024);
    memcpy(buf, sid, strlen(sid));
    memcpy(&(buf[strlen(sid)]), ":", 1);
    memcpy(&(buf[strlen(sid)+1]), domain, strlen(domain));
    memcpy(&(buf[strlen(sid)+1+strlen(domain)]), ":", 1);
    memcpy(&(buf[strlen(sid)+1+strlen(domain)+1]), pwd, strlen(pwd));
    fprintf(stderr, "sid+\":fetion.com.cn:\"+password:\n%s\n", buf);
    md5(buf, &key);
    fprintf(stderr, "key:\n%s\n", key);

    memset(buf, 0, 1024);
    memcpy(buf, key, 16);
    memcpy(&(buf[16]), ":", 1);
    memcpy(&(buf[17]), nonce, 33);
    memcpy(&(buf[49]), ":", 1);
    memcpy(&(buf[50]), cnonce, 33);
    fprintf(stderr, "key+':'+nonce+':'+cnonce:\n%s\n", buf);
    md5String(buf, &h1);
    fprintf(stderr, "H1:\n%s\n", h1);

    memset(buf, 0, 1024);
    memcpy(buf, "REGISTER:", 9);
    memcpy(&(buf[9]), sid, strlen(sid));
    fprintf(stderr, "\"REGISTER:\"+sid:\n%s\n", buf);
    md5String(buf, &h2);
    fprintf(stderr, "H2:\n%s\n", h2);

    memset(buf, 0, 1024);
    memcpy(buf, h1, 32);
    memcpy(&(buf[32]), ":", 1);
    memcpy(&(buf[33]), nonce, 33);
    memcpy(&(buf[65]), ":", 1);
    memcpy(&(buf[66]), h2, 32);
    fprintf(stderr, "H1+':'+nonce+':'+H2:\n%s\n", buf);
    md5String(buf, &response);
    fprintf(stderr, "response:\n%s\n", response);
    free(buf);
    free(key);
    free(h1);
    free(h2);

    return string(response);
}

string toString(const int i) {
    char c[20];
    memset(c, 0, 20);
    sprintf(c, "%d", i);
    return string(c);
}

int toInteger(const string str) {
    return atoi(str.c_str());
}
