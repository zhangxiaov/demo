//
//  ZJson.c
//  oc_demo
//
//  Created by zhangxinwei on 15/12/7.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#include "ZJson.h"
#include <stdarg.h>
#include <sys/malloc.h>
#include <string.h>
#include "ZTime.h"
#include "CString.h"



#define DOUBLE(a) ({\
__typeof__(a) _x_in_DOUBLE = (a);\
_x_in_DOUBLE + _x_in_DOUBLE;\
})
// type = 1 obj, = 0 array
struct _CZ {
    char type;
    int typeSize;
};

// type = 11 obj, = 10 array
struct _ZJson {
    char type;
    int typeSize;
    KV* data;
    char count;
};

struct _KV {
    char* key;
    void* val;
    KV* next;
};

ZJson* zjsonArrayInitWithVal(int n,void* v1,...) {
    ZJson* jsonArray = (ZJson*)malloc(sizeof(ZJson));
    jsonArray->type = ZJSONARRAY;
    jsonArray->data = (KV*)malloc(sizeof(KV));
    jsonArray->count = n;
    
    va_list argp;
    va_start(argp, v1);
    
    KV* next = jsonArray->data;
    
    for (int i = 0; i < n; i++) {
        KV* kv = next;
        kv->val = v1;
        
        next = (KV*)malloc(sizeof(KV));
        next->next = NULL;
        kv->next = next;
        
        v1 = va_arg(argp, void*);
    }
    
    return jsonArray;
}

ZJson* zjsonInitWithJson(ZJson* json) {
    
    return 0;
}

ZJson* zjsonInitWithKV(int n, void* k1,...) {
    ZJson* json = (ZJson*)malloc(sizeof(ZJson));
    json->type = ZJSON;
    json->data = (KV*)malloc(sizeof(KV));
    json->count = n;

    va_list argp;
    va_start(argp, k1);
    
    KV* next = json->data;

    for (int i = 0; i < n; i++) {
        KV* kv = next;
        
        // key
        CZ* k_obj = (CZ*)k1;
        kv->key = ((zs*)k_obj)->val;
        
        // val
        k1 = va_arg(argp, void*);
        kv->val = k1;

        next = (KV*)malloc(sizeof(KV));
        next->next = NULL;
        kv->next = next;

        k1 = va_arg(argp, void*);
    }
    
    return json;
}

char* zjsonArrayToString(ZJson* jsonArray) {
    char* str = "[";
    
    char type = jsonArray->type;
    int count = jsonArray->count;
    KV* data = jsonArray->data;
    
    KV* kv = data;
    for (int i = 0; i < count; i++) {
        char* k = kv->key;

        // val
        CZ* cz = (CZ*)kv->val;
        char type = cz->type;
        switch (type) {
            case ZI:
                str = csAppendInt(str, ((zi*)cz)->val);
                str = csAppend(str, ",");
                break;
            case ZJSONARRAY:
                str = csAppend(str, zjsonArrayToString(((ZJson*)cz)));
                break;
            case ZJSON:
                str = csAppend(str, zjsonToString(((ZJson*)cz)));
                break;
            case ZS:
                str = csAppend(str, "\"");
                str = csAppend(str, ((zs*)cz)->val);
                str = csAppend(str, "\",");
                break;
            default:
                break;
        }
        
        kv = kv->next;
    }
    
    str = csReplaceCharAtLast(str, ']');
    str = csAppend(str, ",");
    return str;
}

char* zjsonToString(ZJson* json) {
    char* str = "{";
    
    char type = json->type;
    int count = json->count;
    KV* data = json->data;
    
    // array
    if (type == ZJSONARRAY) {
        zjsonArrayToString(json);
    }else if (type == ZJSON) {//kv
        
        KV* kv = data;
        for (int i = 0; i < count; i++) {
            char* k = kv->key;
            
            // key
            str = csAppend(str, "\"");
            str = csAppend(str, k);
            str = csAppend(str, "\"");
            
//            printf("%s\n", str);
            
            str = csAppend(str, "\:");
            // val
            CZ* cz = (CZ*)kv->val;
            char type = cz->type;
            switch (type) {
                case ZI:
                    str = csAppendInt(str, ((zi*)cz)->val);
                    str = csAppend(str, ",");
                    break;
                case ZJSONARRAY:
                    str = csAppend(str, zjsonArrayToString(((ZJson*)cz)));
                    break;
                case ZJSON:
                    str = csAppend(str, zjsonToString(((ZJson*)cz)));
                    break;
                case ZS:
                    str = csAppend(str, "\"");
                    str = csAppend(str, ((zs*)cz)->val);
                    str = csAppend(str, "\",");
                    break;
                default:
                    break;
            }
            
            kv = kv->next;
        }
    }
    
    str = csReplaceCharAtLast(str, '}');
    return str;
}

void main_zjson() {

    uint64_t s = ztimeSince1970();
    ZJson* json = zjsonInitWithKV(4, zs("name"), zs("张新伟"), zs("age"), zi(26), zs("mobile"), zs("15210743874"), zs("test"), zjsonArrayInitWithVal(2, zs("zhangxinwei"), zi(100)));

    char* str = zjsonToString(json);
    char* str2 = zjsonToString(json);

    printf("time := %llu\n", ztimeSince1970() - s);
    printf("%s\n", str);
    printf("%s\n", str2);
    
    printf("%d\n", strlen("正"));
}










