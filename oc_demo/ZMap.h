//
//  ZMap.h
//  oc_demo
//
//  Created by 张新伟 on 15/12/12.
//  Copyright (c) 2015年 zhangxinwei. All rights reserved.
//

#ifndef __oc_demo__ZMap__
#define __oc_demo__ZMap__

#include <stdio.h>

typedef struct _ZMap ZMap;


#define ZMAP 11

ZMap* zmapInit();
ZMap* zmapInitWithSize();
void zmapPut(ZMap* self, char* key, void* val);
void* zmapGet(ZMap* self, char* key);

#endif /* defined(__oc_demo__ZMap__) */
