#import <Foundation/Foundation.h>
@class Baby;
@interface Nurse : NSObject
- (void)babyCry:(Baby *)baby;
- (void)babySleep:(Baby *)baby;
- (void)babyHungry:(Baby *)baby;
@end