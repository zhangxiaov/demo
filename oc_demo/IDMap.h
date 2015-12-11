//
//  IDMap.h
//  oc_demo
//
//  Created by zhangxinwei on 15/11/26.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IDMap : NSObject
@property (nonatomic, copy) NSString *path;

@property (nonatomic) NSMutableArray *isDroppedList;
@property (nonatomic) NSMutableArray *IDList;
@property (nonatomic) NSMutableArray *offsetList;
@property (nonatomic) NSMutableArray *RLenList;
@property (atomic) int64_t fileLen;

+ (IDMap *)share;
- (int32_t)getIDForSameLen:(int32_t)len;
- (void)updateFile:(NSData *)data;
@end
