//
//  IDMap.m
//  oc_demo
//
//  Created by zhangxinwei on 15/11/26.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#import "IDMap.h"
#import "FH.h"

@implementation IDMap

+ (IDMap *)share {
    static IDMap *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[IDMap alloc] init];
        
        //
        NSString *dbpath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingPathComponent:@"records"];
        FH *fh0 = [FH fileHandleForUpdatingAtPath:dbpath];
        instance.fileLen = [fh0 seekToEndOfFile];
        
        NSString *idmappath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingPathComponent:@"IDMap"];
        
        NSFileManager *fm = [NSFileManager defaultManager];
        if ([fm fileExistsAtPath:idmappath]) {
            
        }else {
            [fm createFileAtPath:idmappath contents:nil attributes:nil];
        }
        
        instance.path = idmappath;
        FH *fh = [FH fileHandleForUpdatingAtPath:idmappath];
        NSData *data = [fh readDataToEndOfFile];
        [fh closeFile];
        if (data.length <= 0) {
            instance.isDroppedList = [@[] mutableCopy];
            instance.IDList = [@[] mutableCopy];
            instance.offsetList = [@[] mutableCopy];
            instance.RLenList = [@[] mutableCopy];
        }else {
            instance.isDroppedList = [@[] mutableCopy];
            instance.IDList = [@[] mutableCopy];
            instance.offsetList = [@[] mutableCopy];
            instance.RLenList = [@[] mutableCopy];
            
            int64_t len = data.length;
            for (int i = 0; i < len;) {
                NSData *dt = [data subdataWithRange:NSMakeRange(i, 17)];
                int8_t isd;
                int32_t ID;
                int64_t offset;
                int32_t rlen;
                
                [dt getBytes:&isd range:NSMakeRange(0, sizeof(int8_t))];
                [dt getBytes:&ID range:NSMakeRange(1, sizeof(int32_t))];
                [dt getBytes:&offset range:NSMakeRange(5, sizeof(int64_t))];
                [dt getBytes:&rlen range:NSMakeRange(13, sizeof(int32_t))];
                
                [instance.isDroppedList addObject:[NSNumber numberWithInt:isd]];
                [instance.IDList addObject:[NSNumber numberWithInt:ID]];
                [instance.offsetList addObject:[NSNumber numberWithLong:offset]];
                [instance.RLenList addObject:[NSNumber numberWithInt:rlen]];
                
                i += 17;
            }
        }
        
    });
    
    return instance;
}


// isd = 1 drop
- (int32_t)getIDForSameLen:(int32_t)len {
    int32_t oid = 0;
    NSArray *a = [IDMap share].isDroppedList;
    for (int i = 0; i < a.count; i++) {
        NSNumber *n = (NSNumber *)a[i];
        if (n.intValue == 1) {
            NSNumber *n2 = (NSNumber *)[IDMap share].RLenList[i];
            if (n2.integerValue >= len) {
                oid = (int32_t)n2.integerValue;
                break;
            }
        }
    }
    
    return oid;
}

- (void)updateFile:(NSData *)data {
    FH *fh = [FH fileHandleForUpdatingAtPath:[IDMap share].path];
    [fh seekToEndOfFile];
    [fh writeData:data];
    [fh closeFile];
}

@end
