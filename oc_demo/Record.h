//
//  Record.h
//  oc_demo
//
//  Created by zhangxinwei on 15/11/24.
//  Copyright © 2015年 zhangxinwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Record : NSObject
@property (nonatomic) int32_t groupId;
@property (nonatomic, copy) NSString *groupName;

@property (nonatomic) int8_t count;
@property (nonatomic) int32_t totalLen;

@property (nonatomic) int64_t publicId;

- (instancetype)initWithGroupName:(NSString *)groupName;
- (instancetype)initWithGroupName:(NSString *)groupName index:(int64_t)index;

- (void)addK:(NSString *)key V:(NSString *)value;
- (void)setK:(NSString *)key V:(NSString *)value;
- (NSString *)getStringValueByKey:(NSString *)publicId;

- (NSDictionary *)selectByPublicId:(int64_t)publicId;
- (NSDictionary *)selectByKV:(NSDictionary *)dict;
- (id)selectValueByKey:(NSString *)key withPublicId:(int64_t)publicId;
- (int32_t)insert:(NSDictionary *)dict;
- (void)update:(NSDictionary *)dict withPublicId:(int64_t)publicId;
- (void)append:(NSDictionary *)dict withPublicId:(int64_t)publicId;

- (instancetype)insert:(NSDictionary *)dict withGroupName:(NSString *)groupName;

// publicId for 外  offset for 内
@end
