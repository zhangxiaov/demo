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

int csIsEqual(char* self, char* str) {
    if (self == NULL) {
<<<<<<< HEAD
        return 0;
    }
    size_t strLen = strlen(self);
    if (strLen != strlen(str)) {
        return 0;
=======
        return -1;
    }
    size_t strLen = strlen(self);
    if (strLen != strlen(str)) {
        return -1;
>>>>>>> 93111ae4fd540c7e13021592a0586d930243a041
    }
    
    for (int i = 0; i < strLen; i++) {
        if (*self++ != *str++) {
<<<<<<< HEAD
            return 0;
=======
            return -1;
>>>>>>> 93111ae4fd540c7e13021592a0586d930243a041
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

<<<<<<< HEAD
int csToInt(char* self) {
    
    return 0;
}

=======
>>>>>>> 93111ae4fd540c7e13021592a0586d930243a041
void test () {
    int test = 12306;
}

void main_cstring() {
<<<<<<< HEAD
//void main() {
=======
>>>>>>> 93111ae4fd540c7e13021592a0586d930243a041
    char* str = "{{{{{{{{";

    char* s2 = csAppend(str, "zhangafafafafa");

    printf("%s\n", s2);
    printf("%s\n", str);
    
    printf("%s\n", csIntToString(-24343434));
    
    printf("%s\n", csAppendInt(str, -4434343));
    
    printf("%d\n", csIndexPrefixSkipSpace("prefixffff", "pre"));
    
<<<<<<< HEAD
    printf("%d\n", csIsEqual("test1", "testc"));
=======
    printf("%d\n", csIsEqual("张新伟", "张新伟b"));
>>>>>>> 93111ae4fd540c7e13021592a0586d930243a041
}