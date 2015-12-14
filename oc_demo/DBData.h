//
//  DBData.h
//  oc_demo
//
//  Created by zhangxinwei on 15/11/24.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Record.h"

@interface DBData : NSObject
@property (nonatomic, copy) NSString *filePath;
+ (DBData *)share;
- (int64_t)addRecord:(NSData *)data;
- (NSMutableData *)getBytesWidthOffset:(int32_t)offset length:(int32_t)length;
@end
