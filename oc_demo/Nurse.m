#import "Nurse.h"
#import "Baby.h"
@implementation Nurse
- (void)babyCry:(Baby *)baby
{
    NSLog(@"护士正在安慰%d岁的baby", baby.age);
}
- (void)babyHungry:(Baby *)baby
{
    NSLog(@"护士喂%d岁的baby吃东西", baby.age);
}
- (void)babySleep:(Baby *)baby
{
    NSLog(@"护士哄%d岁的baby去睡觉", baby.age);
}
@end