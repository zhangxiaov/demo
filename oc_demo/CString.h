//
//  CString.h
//  oc_demo
//
//  Created by zhangxinwei on 15/12/8.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#ifndef CString_h
#define CString_h

#include <stdio.h>

int csIndexPrefixSkipSpace(char* self, char* prefix);
char* csLineByClientFd(int clientFd);
char* csReplaceCharAtLast(char* self, char c);
char* csAppend(char* self, char* str);
char* csAppendInt(char* self, int intVal);
char* csIntToString(int intVal);
int csIsEqual(char* self, char* str);
int csToInt(char* self);

#endif /* CString_h */
