//
//  ZArray.c
//  oc_demo
//
//  Created by 张新伟 on 15/12/13.
//  Copyright (c) 2015年 zhangxinwei. All rights reserved.
//

#include "ZArray.h"
#include <string.h>
#include "CString.h"
#include <stdlib.h>
#include <stdarg.h>



struct _ZArray {
    char type;
    int typeSize;
    int len;
    void* data;
};

ZArray* zarrayInit(int n, void* val1,...) {
    ZArray* array = (ZArray*)malloc(sizeof(ZArray));
    array->type = 12;
    array->data = malloc(n*8);
    
    va_list va;
    va_start(va, val1);
    
    for (int i = 0; i < n; i++) {
        array->data += i;
        array->data = val1;
        val1 = va_arg(va, void*);
    }
    
    return array;
}

void* zarrayGet(ZArray* self, int index) {
    return self->data + index;
}

//void main_array(){
void main() {
    
    
    ZArray* a = zarrayInit(3, "fafa", "zzz", "333");

    printf("%s\n", zarrayGet(a, 0));
    printf("%s\n", zarrayGet(a, 1));

    printf("%s\n", zarrayGet(a, 2));


}