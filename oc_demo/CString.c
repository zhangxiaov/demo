//
//  CString.c
//  oc_demo
//
//  Created by zhangxinwei on 15/12/8.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#include "CString.h"
#include <sys/malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>

int csSearchSunday(char* self, char* smallChars) {
    size_t bigCharsLen = strlen(self);
    size_t smallCharLen = strlen(smallChars);
    
    int ibig = 0;
    int ismall = 0;
    
    int tbig = 0;
    int tsmall = 0;
    
    int st = 0;
    int count = 0;
    while (ibig < bigCharsLen) {
        if (self[ibig] == smallChars[ismall]) {
            ++ibig;
            ++ismall;
        }else {
            //移动小串＋1
            //这个字符是否在小串里
            char checkChar = self[st + smallCharLen];
            for (int i = 0; i < smallCharLen; i++) {
                if (checkChar == smallChars[i]) {
                    ibig -= i;
                    break;
                }
            }
            
            ibig += 1;
        }
        
        if (ismall == smallCharLen - 1) {
            return (int)(ibig - smallCharLen);
        }
    }
    
    return -1;
}

int csIsEqual(char* self, char* str) {
    if (self == NULL) {
        return -1;
    }
    size_t strLen = strlen(self);
    if (strLen != strlen(str)) {
        return -1;
    }
    
    for (int i = 0; i < strLen; i++) {
        if (*self++ != *str++) {
            return -1;
        }
    }
    
    return 1;
}

char* csLineByClientFd(int clientFd) {
    char c = '\0';
    ssize_t n;
    
    char* buf = (char*)malloc(1024);
    
    while (c != '\n') {
        n = recv(clientFd, &c, 1, 0);
        *buf++ = c;
    }
    *buf = '\0';
    
    return buf;
}

int csIndexPrefixSkipSpace(char* self, char* prefix) {
    size_t prefixLen = strlen(prefix);
    int index = 0;
    char* addr = self;
    // skip space
    while (isspace((char)*self)){
        ++self;
    }
    index = (int)(self - addr);
    
    for (int i = 0; i < prefixLen; i++) {
        if (*prefix++ != *self++) {
            printf("%c\n", (char)*self);
            return -1;
        }
    }
    
    return index;
}

char* csReplaceCharAtLast(char* self, char c) {
    if (self == NULL) {
        return "";
    }
    size_t selfLen = strlen(self);

    void* temp = self;

    self += (selfLen-1);
    *self = c;
    
    return temp;
}

char* csAppend(char* self, char* str) {
    if (self == NULL) {
        return "";
    }
    size_t selfLen = strlen(self);
    
    if (str == NULL) {
        return self;
    }
    size_t strLen = strlen(str);
    
    char* newS = (char*)malloc(selfLen + strLen + 1);
    if (newS == NULL) {
        printf("malloc no mem");
        return NULL;
    }

    void* temp = newS;
    
    for (int i = 0; i < selfLen; i++) {
        *newS++ = *self++;
    }
    
    for (int i = 0; i < strLen; i++) {
        *newS++ = *str++;
    }
    
    *newS = '\0';
    
    return temp;
}

char* csAppendInt(char* self, int intVal) {
    char* str = csIntToString(intVal);
    size_t selfLen = strlen(self);
    size_t strLen = strlen(str);
    
    char* newS = (char*)malloc(selfLen + strLen + 1);
    if (newS == NULL) {
        printf("malloc no mem");
        return NULL;
    }
    
    void* temp = newS;
    
    for (int i = 0; i < selfLen; i++) {
        *newS++ = *self++;
    }
    
    for (int i = 0; i < strLen; i++) {
        *newS++ = *str++;
    }
    
    *newS = '\0';
    
//    free(str);
//    free(self);
    return temp;
}

char* csIntToString(int intVal) {
    int temp = intVal;
    char* str = (char*)malloc(12);
    size_t count = 0;
    if (temp < 0) {
        intVal = -intVal;
    }
    
    do {
        ++count;
        *str++ = intVal % 10 + '0';
        intVal = intVal / 10;
    } while (intVal > 0);
    
    if (temp < 0) {
        *str++ = '-';
        ++count;
    }
    
    
    //reverse
    char* c = (char*)malloc(count+1);
    void* addr = c;
    while (count > 0) {
        *c++ = *(--str);
        --count;
    }
    
    *c = '\0';
    
    free(str);
    return addr;
}


int csToInt(char* self) {
    
    return 0;
}

void test () {
    int test = 12306;
}

//void main_cstring() {
void main() {
//    char* str = "{{{{{{{{";
//
//    char* s2 = csAppend(str, "zhangafafafafa");
//
//    printf("%s\n", s2);
//    printf("%s\n", str);
//    
//    printf("%s\n", csIntToString(-24343434));
//    
//    printf("%s\n", csAppendInt(str, -4434343));
//    
//    printf("%d\n", csIndexPrefixSkipSpace("prefixffff", "pre"));
//    
//    printf("%d\n", csIsEqual("test1", "testc"));
//    printf("%d\n", csIsEqual("张新伟", "张新伟b"));
    
    char* str2 = "zhangxinweitest";
    
    printf("index %d\n", csSearchSunday(str2, "test"));
}