#import "Baby.h"
@implementation Baby
- (void)cry
{
    NSLog(@"%d岁的baby哭了", _age);
    
    // 通知保姆（护士）
    [_baomu babyCry:self];
}
- (void)sleep
{
    NSLog(@"%d岁的baby想睡觉", _age);
    
    // 通知保姆
    [_baomu babySleep:self];
}
- (void)hungry
{
    NSLog(@"%d岁的baby想吃东西", _age);
    
    // 通知保姆
    [_baomu babyHungry:self];
}
@end