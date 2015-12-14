//
//  Record.m
//  oc_demo
//
//  Created by zhangxinwei on 15/11/24.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#import "Record.h"
#import "Groups.h"
#import "DBData.h"
#import "IDMap.h"
#import "SimpleFileHandle.h"

@interface Record ()

// count(8) totalLen(32) len1(32) len2(32) ... data
@property (nonatomic, strong) NSData *bytes;
@property (nonatomic) int64_t offset;
@property (nonatomic, copy) NSString *dbpath;
@property (nonatomic, copy) NSString *offsetIdMapPath;
@end

@implementation Record

- (instancetype)initWithGroupName:(NSString *)groupName
{
    self = [super init];
    if (self) {
        _groupName = groupName;
        _dbpath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingPathComponent:@"records"];
        
        NSFileManager *fm = [NSFileManager defaultManager];
        if ([fm fileExistsAtPath:_dbpath]) {
            
        }else {
            [fm createFileAtPath:_dbpath contents:nil attributes:nil];
        }
        
        NSLog(@"%@", _dbpath);
    }
    return self;
}

- (int32_t)insert:(NSDictionary *)dict {
    
    int32_t rid0 = -1;
    
    SimpleFileHandle *fh = [SimpleFileHandle fileHandleForUpdatingAtPath:_dbpath];
    
    NSArray *keys = [dict allKeys];
    NSString *keysstr = [keys componentsJoinedByString:@","];

    // count keyslen keys  , val1 len  val2 len  vals
    NSMutableData *data = [[NSMutableData alloc] init];
    
    int8_t count = keys.count;
    [data appendBytes:&count length:sizeof(int8_t)];
    
    int16_t keysLen = keysstr.length;
    [data appendBytes:&keysLen length:sizeof(int16_t)];
    [data appendData:[keysstr dataUsingEncoding:NSUTF8StringEncoding]];
    
    
    for (int i = 0; i < dict.count; i++) {
        NSString *val = (NSString *)dict[keys[i]];
        int32_t valLen = (int32_t)[val dataUsingEncoding:NSUTF8StringEncoding].length;
        [data appendBytes:&valLen length:sizeof(int32_t)];
        [data appendData:[val dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    int32_t totalLen = (int32_t)data.length;
    
    // write file
    int32_t oid = [[IDMap share] getIDForSameLen:totalLen];
    if (oid <= 0) {
        
        //new offset, add to idmap
        int8_t isd = 0;
        int32_t rid = (int32_t)[IDMap share].IDList.count;
        int64_t offset = [fh seekToEndOfFile];
        int32_t rlen = (int32_t)data.length;
        
        NSMutableData *mapdata = [[NSMutableData alloc] init];
        [mapdata appendBytes:&isd length:sizeof(int8_t)];
        [mapdata appendBytes:&rid length:sizeof(int32_t)];
        [mapdata appendBytes:&offset length:sizeof(int64_t)];
        [mapdata appendBytes:&rlen length:sizeof(int32_t)];
        
        [[IDMap share] updateFile:mapdata];
        
        [[IDMap share].isDroppedList addObject:[NSNumber numberWithInt:isd]];
        [[IDMap share].IDList addObject:[NSNumber numberWithInt:rid]];
        [[IDMap share].offsetList addObject:[NSNumber numberWithLong:offset]];
        [[IDMap share].RLenList addObject:[NSNumber numberWithInt:rlen]];
        
//        [fh seekToEndOfFile];
        [fh seekToFileOffset:[IDMap share].fileLen];
        
        [fh writeData:data];
        
        rid0 = rid;
        
        [IDMap share].fileLen += data.length;
    }else {
        [fh seekToFileOffset:(int64_t)[IDMap share].offsetList[oid]];
        [fh writeData:data];
        rid0 = oid;
    }
    
//    [fh closeFile];
    return rid0;
}

- (NSDictionary *)selectByPublicId:(int64_t)publicId {
    NSMutableDictionary *md = [[NSMutableDictionary alloc] init];
    
    int64_t offset = (int64_t)[IDMap share].offsetList[publicId];
    int32_t rlen = (int32_t)[IDMap share].RLenList[publicId];
    SimpleFileHandle *fh = [SimpleFileHandle fileHandleForUpdatingAtPath:_dbpath];
    [fh seekToFileOffset:offset];
    NSData *data = [fh readDataOfLength:rlen];
    [fh closeFile];
    
    int8_t count;
    int16_t keyLen;
    
    [data getBytes:&count length:sizeof(int8_t)];
    [data getBytes:&keyLen range:NSMakeRange(1, sizeof(int16_t))];
    
    NSString *keys = [[NSString alloc] initWithData:[data subdataWithRange:NSMakeRange(3, keyLen)] encoding:NSUTF8StringEncoding];
    NSArray *keys_a = [keys componentsSeparatedByString:@","];
//    for (int i = 0; i < keys_a.count; i++) {
//        [md setObject:nil forKey:keys_a[i]];
//    }
    
    int32_t offset_inner = keyLen + 3;
    for (int i = 0; i < count; i++) {
        int8_t valLen;
        [data getBytes:&valLen range:NSMakeRange(offset_inner, sizeof(int8_t))];
        
        id val;
        offset_inner += valLen;
        val = [data subdataWithRange:NSMakeRange(offset_inner, valLen)];
        
        [md setObject:val forKey:keys_a[i]];
    }
    
    return md;
}

- (void)addK:(NSString *)key V:(NSString *)value {
    if (key.length <= 0) {
        return ;
    }
    
    if (value == nil) {
        value = @"";
    }
    
    if (![[Groups share] addKey:key groupName:_groupName]) {
        NSLog(@"key已存在,请用set");
        return;
    }
    
    int8_t indexForKey = [[Groups share] getKeyIndex:key groupName:_groupName];
    int32_t len = value.length;
    
    
    //二进制格式 处理
    
    // 1,获取二进制
    NSMutableData *bytes = [[DBData share] getBytesWidthOffset:_offset length:5];
    int32_t oldTotalLen;
    [bytes getBytes:&oldTotalLen range:NSMakeRange(1, 4)];
    NSMutableData *totalBytes = [[DBData share] getBytesWidthOffset:_offset length:oldTotalLen];
    
    int8_t count;
    [bytes getBytes:&count range:NSMakeRange(0, 1)];
    
    //2，获取原value len
    int32_t oldValueLen;
    NSRange range1 = {5+indexForKey*4, 4};
    if (range1.location >= bytes.length) {
        oldValueLen = 0;
    }else {
        [bytes getBytes:&oldValueLen range:range1];
    }
    
    //3, new value len
    int32_t newValueLen = [value dataUsingEncoding:NSUTF8StringEncoding].length;
    
    // 4, new totalLen
    int32_t newTotalLen = oldTotalLen - oldValueLen + newValueLen + 4;
    
    //6, 建 新 data
    NSMutableData *newData = [[NSMutableData alloc] init];
    // append count
    count += 1;
    NSData *data_count = [NSData dataWithBytes:&count length:sizeof(int8_t)];
    
    [newData appendData:data_count];
    
    // append totalLen
    [newData appendData:[NSData dataWithBytes:&newTotalLen length:sizeof(int32_t)]];
    // append len1 len2 ...
    
    for (int i = 0; i < count; i++) {
        int32_t len ;
        
        if (i == indexForKey) {
            len = newValueLen;
        }else {
            NSRange range = {5+i*4,4};
            [totalBytes getBytes:&len range:range];
        }
        
        [newData appendData:[NSData dataWithBytes:&len length:sizeof(int32_t)]];
    }
    
    // append data1 data2
    // count 是 totalbytes里的 count
    int64_t offset = 1+(count -1 +1)*4 - 1;
    for (int i = 0; i < count; i++) {
        int32_t len ;
        NSRange range = {5+i*4,4};
        [newData getBytes:&len range:range];
        
        NSData *data;
        if (i == indexForKey) {
            data = [value dataUsingEncoding:NSUTF8StringEncoding];
        }else {
            NSRange range = {offset, len};
            data = [totalBytes subdataWithRange:range];
        }
        
        [newData appendData:data];
    }
    // new data end
    
    [[DBData share] addRecord:newData];
}

- (void)setK:(NSString *)key V:(NSString *)value {
    if (key.length <= 0) {
        return ;
    }
    
    if (value == nil) {
        value = @"";
    }
    
    int8_t indexForKey = [[Groups share] getKeyIndex:key groupName:_groupName];
    int32_t len = value.length;

    
    //二进制格式 处理
    
    // 1,获取二进制
    NSMutableData *bytes = [[DBData share] getBytesWidthOffset:_offset length:5];
    int32_t oldTotalLen;
    [bytes getBytes:&oldTotalLen range:NSMakeRange(1, 4)];
    NSMutableData *totalBytes = [[DBData share] getBytesWidthOffset:_offset length:oldTotalLen];
    
    int8_t count;
    [bytes getBytes:&count range:NSMakeRange(0, 1)];
    
    //2，获取原value len
    int32_t oldValueLen;
    NSRange range1 = {5+indexForKey*4, 4};
    if (range1.location >= bytes.length) {
        oldValueLen = 0;
    }else {
        [bytes getBytes:&oldValueLen range:range1];
    }
    
    //3, new value len
    int32_t newValueLen = [value dataUsingEncoding:NSUTF8StringEncoding].length;
    
    // 4, new totalLen
    int32_t newTotalLen = oldTotalLen - oldValueLen + newValueLen;
    
    //6, 建 新 data
    NSMutableData *newData = [[NSMutableData alloc] init];
    // append count
    NSData *data_count = [bytes subdataWithRange:NSMakeRange(0, 1)];
    [newData appendData:data_count];
    
    // append totalLen
    [newData appendData:[NSData dataWithBytes:&newTotalLen length:sizeof(int32_t)]];
    // append len1 len2 ...
    
    for (int i = 0; i < count; i++) {
        int32_t len ;

        if (i == indexForKey) {
            len = newValueLen;
        }else {
            NSRange range = {5+i*4,4};
            [bytes getBytes:&len range:range];
        }
       
        [newData appendData:[NSData dataWithBytes:&len length:sizeof(int32_t)]];
    }
    
    // append data1 data2
    int32_t offset = (count + 1)*4;
    for (int i = 0; i < count; i++) {
        int32_t len ;
        NSRange range = {5*8+i*32,32};
        [bytes getBytes:&len range:range];
        
        NSData *data;
        if (i == indexForKey) {
            data = [value dataUsingEncoding:NSUTF8StringEncoding];
        }else {
            NSRange range = {offset, len};
            data = [bytes subdataWithRange:range];
        }
       
        [newData appendData:data];
    }
    // new data end
    
    _offset = [[DBData share] addRecord:newData];
}

- (NSString *)getStringValueByKey:(NSString *)key{
    if (key.length <= 0) {
        return nil;
    }
    
    int8_t indexForKey = [[Groups share] getKeyIndex:key groupName:_groupName];
    
    // 1,获取二进制
    NSMutableData *bytes = [[DBData share] getBytesWidthOffset:_offset length:5];
    int32_t oldTotalLen;
    [bytes getBytes:&oldTotalLen range:NSMakeRange(1, 4)];
    NSMutableData *totalBytes = [[DBData share] getBytesWidthOffset:_offset length:oldTotalLen];
    
    int8_t count;
    [bytes getBytes:&count length:sizeof(int8_t)];
    
    NSData *data;
    int32_t offset = 1+(count+1)*4;
    for (int i = 0; i < count; i++) {
        int32_t len ;
        NSRange range = {5+i*4,4};
        [totalBytes getBytes:&len range:range];
        
        if (i == indexForKey) {
            NSRange range = {offset, len};
            data = [totalBytes subdataWithRange:range];
            break;
        }
    }

    return [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

@end
