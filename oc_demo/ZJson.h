//
//  ZJson.h
//  oc_demo
//
//  Created by zhangxinwei on 15/12/7.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#ifndef ZJson_h
#define ZJson_h

#include <stdio.h>


#define ZJSON 1
#define ZJSONARRAY 2
#define ZI 3
#define ZS 4

typedef struct _ZJson ZJson;
typedef struct _zi zi;
typedef struct _zs zs;
typedef struct _KV KV;
typedef struct _CZ CZ;

#define zi(intVal) \
    &((struct _zi){.type=ZI,.val=intVal})
#define zs(strVal) \
    &((struct _zs){.type=ZS,.val=strVal, .valLen=strlen(strVal)})


#define var2(left, right) __typeof__(right) left = (right)


struct _zi {
    char type;
    int typeSize;
    int val;
};

struct _zs {
    char type;
    int typeSize;
    char* val;
    int valLen;
};

char* zjsonToString(ZJson* json);

#endif /* ZJson_h */
