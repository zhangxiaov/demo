#import <Foundation/Foundation.h>
#import "BabyBaomuXieyi.h"
@interface Baby : NSObject
@property (nonatomic, strong) id<BabyBaomuXieyi> baomu; // 任何人都能做保姆
@property (nonatomic, assign) int age; // 年龄
- (void)hungry; // 饿了
- (void)cry; // 哭了
- (void)sleep; // 想睡觉
@end