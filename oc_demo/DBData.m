//
//  DBData.m
//  oc_demo
//
//  Created by zhangxinwei on 15/11/24.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#import "DBData.h"

@implementation DBData

+ (DBData *)share {
    static DBData *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[DBData alloc] init];
        
        NSString *filePath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
        filePath = [filePath stringByAppendingPathComponent:@"db"];
        
        NSFileManager *fm = [NSFileManager defaultManager];
        if ([fm fileExistsAtPath:filePath]) {
            NSLog(@"db :%@", filePath);
        }else {
            [fm createFileAtPath:filePath contents:nil attributes:nil];
        }
    });
    
    return instance;
}

- (int64_t)addRecord:(NSData *)data {
    if (!_filePath) {
        NSString *filePath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
        filePath = [filePath stringByAppendingPathComponent:@"db"];
        _filePath = filePath;
    }
    
    NSFileHandle *fh = [NSFileHandle fileHandleForUpdatingAtPath:_filePath];
    int64_t offset = [fh seekToEndOfFile];
    [data writeToFile:_filePath atomically:YES];
    
    [fh closeFile];
    
    return offset;
}

- (NSMutableData *)getBytesWidthOffset:(int32_t)offset length:(int32_t)length {
    if (!_filePath) {
        NSString *filePath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
        filePath = [filePath stringByAppendingPathComponent:@"db"];
        _filePath = filePath;
    }
    
    NSFileHandle *fh = [NSFileHandle fileHandleForUpdatingAtPath:_filePath];
    [fh seekToFileOffset:offset];
    NSData *d1 = [fh readDataOfLength:length];
    NSMutableData *data = [[NSMutableData alloc] init];
    
    if (d1.length <= 0) {
        int8_t count = 0;
        NSData *dc = [NSData dataWithBytes:&count length:sizeof(count)];
        [data appendData:dc];
        
        int32_t len = 5;
        NSData *dl = [NSData dataWithBytes:&length length:sizeof(len)];
        
        [data appendData:dl];
    }else {
        [data appendData:d1];
    }
    
    return data;
}

@end
