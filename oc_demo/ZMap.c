//
//  ZMap.c
//  oc_demo
//
//  Created by 张新伟 on 15/12/12.
//  Copyright (c) 2015年 zhangxinwei. All rights reserved.
//

#include "ZMap.h"
#include <sys/malloc.h>
#include "ZHash.h"
#include <string.h>
#include "CString.h"
#include <stdlib.h>
#include "ZTime.h"

typedef struct _zmapNode zmapNode;

struct _zmapNode {
    char* key;
    void* val;
    zmapNode* next;
};

struct _ZMap {
    char type;
    int typeSize;
    int size;
    int count;
    zmapNode* data;
};

zmapNode* zmapGetNode(ZMap* self, char* key, int index);
void zmapReHash(ZMap* self, char* akey, void* aval);

ZMap* zmapInit() {
    ZMap* map = (ZMap*)malloc(sizeof(ZMap));
    map->type = ZMAP;
    map->typeSize = sizeof(ZMap);
    map->size = 11;
    
    zmapNode* nodeData = (zmapNode*)malloc(sizeof(zmapNode)*11);
    memset(nodeData, 0, sizeof(zmapNode)*11);
    
    map->data = nodeData;
    return map;
}

ZMap* zmapInitWithSize(int size) {
    ZMap* map = (ZMap*)malloc(sizeof(ZMap)*size);
    map->type = ZMAP;
    map->typeSize = sizeof(ZMap);
    map->size = size;
    
    return map;
}

ZMap* zmapInitWithKV(int n, char* key,...) {
    ZMap* map = (ZMap*)malloc(sizeof(ZMap)*11);
    map->type = ZMAP;
    map->typeSize = sizeof(ZMap);
    map->size = 11;
    
    return map;
}

void zmapPut(ZMap* self, char* key, void* val) {
    if (self == NULL || key == NULL) {
        return;
    }
    
    uint64_t h = zhashCode(key, strlen(key));
    int index = (int)(h % self->size);
    
   
    // check
    ++self->count;
    float f = self->count / self->size;
    if (f >= 0.75) {
        zmapReHash(self, key, val);
        return;
    }

    // < 0.75
    zmapNode* node = self->data + index;
    for (; node != NULL; node = node->next) {
        if (node->key == NULL) {
            node->key = key;
            node->val = val;

            return;
        }
        if (csIsEqual(key, node->key)) {
            node->val = val;

            return;
        }
        if (node->next == NULL) {
            zmapNode* newNode = (zmapNode*)malloc(sizeof(zmapNode));
            newNode->key = key;
            newNode->val = val;
            newNode->next = NULL;
            node->next = newNode;
            
            return;
        }
    }
}

void zmapReHash(ZMap* self, char* akey, void* aval) {
    int oldSize = self->size;
    int oldCount = self->count;
    
    int newSize = oldSize*2 + 1;
    int newCount = oldCount + 1;
    
    self->count = newCount;
    self->size = newSize;
    
    int index = 0;
    int keyIndex = 0;
    
    zmapNode* oldNodeData = self->data;
    
    zmapNode* newNodeData = (zmapNode*)malloc(newSize*sizeof(zmapNode));
    memset(newNodeData, 0, newSize*sizeof(zmapNode));
    
    while (index < oldSize) {
        zmapNode* node = oldNodeData + index;
        for (; node != NULL; node = node->next) { //old node data
            if (node->key == NULL) {
                break;
            }
            char* key = node->key;
           
            keyIndex = zhashCode(key, strlen(key)) % newSize;
            zmapNode* addr = newNodeData + keyIndex;
            
            for (; addr != NULL; addr = addr->next) { //new node data
                if (addr->key == NULL) {
                    addr->key = node->key;
                    addr->val = node->val;

                    goto label1;
                }
                if (csIsEqual(key, addr->key)) {
                    addr->val = node->val;

                    goto label1;
                }
                
                if (addr->next == NULL) {
                    zmapNode* newNode = (zmapNode*)malloc(sizeof(zmapNode));
                    newNode->key = node->key;
                    newNode->val = node->val;
                    newNode->next = NULL;
                    addr->next = newNode;
                    
                    goto label1;
                }
            }
        label1:
            ;
        }
        ++index;
    }
    
    //
    keyIndex = zhashCode(akey, strlen(akey)) % newSize;
    zmapNode* addr = newNodeData + keyIndex;

    for (; addr != NULL; addr = addr->next) {
        if (addr->key == NULL) {
            addr->key = akey;
            addr->val = aval;
            
            goto label2;
        }
        if (csIsEqual(akey, addr->key)) {
            addr->val = aval;

            goto label2;
        }
        if (addr->next == NULL) {
            zmapNode* newNode = (zmapNode*)malloc(sizeof(zmapNode));
            newNode->key = akey;
            newNode->val = aval;
            newNode->next = NULL;
            addr->next = newNode;

            goto label2;
        }
    }
    
label2:
    ;
    
    self->data = newNodeData;
}

void* zmapGet(ZMap* self, char* key) {
    int index = zhashCode(key, strlen(key)) % self->size;
    zmapNode* node = self->data + index;
    
    for (; node->key != NULL; node = node->next) {
        if (csIsEqual(key, node->key)) {
            return node->val;
        }
    }
    
    return NULL;
}

void main_zmap() {
//void main() {

    char* str = "fafafafafaf";
    printf("%p\n", str);
    
    ZMap* map = zmapInit();
    zmapPut(map, "fa", "valuefa");
    zmapPut(map, "fa2", str);
    
    str = "test";

    printf("%s, %p\n", zmapGet(map, "fa2"), str);
    
    
    
    int s = ztimeSince1970();
    for (int i = 0; i < 200000; i++) {
        zmapPut(map, csAppendInt("tiankong", i), "value");
    }
//
    printf("%d, %s\n", ztimeSince1970() - s, zmapGet(map, "tiankong3333"));
}