//#import <Foundation/Foundation.h>
////#import "Baby.h"
////#import "Student.h"
////#import "Dog.h"
//#import "Groups.h"
//#import "Record.h"
//#import "test.h"
//#import "IDMap.h"
//<<<<<<< HEAD
////#import "SimpleClientSocket.h"
////#import "SimpleServerSocket.h"
//=======
//#import "SimpleClientSocket.h"
//#import "SimpleServerSocket.h"
//>>>>>>> 93111ae4fd540c7e13021592a0586d930243a041
//
//#import "SimpleHttpRequest.h"
//#import "ZHttpServer.h"
//#include "ZDict.h"
//#include "CString.h"
//
//int function(void) {
//    static int i, state = 0;
//    switch (state) {
//        case 0: goto LABEL0;
//        case 1: goto LABEL1;
//    }
//    
//    LABEL0: /* start of function */
//    for (i = 0; i < 10; i++) {
//        state = 1;
//        printf("%d\n", i);
//        return i;
//        
//        LABEL1:;
//    }
////
////    return 0;
//    
//    //
////    int count = 11110;
////    char to[1];
////    char* from;
////    
////    switch (count % 8) {
////        case 0:
////            do {
////                    *to = *from++;
////                case 7: *to = *from++;
////                case 6: *to = *from++;
////                case 5: *to = *from++;
////                case 4: *to = *from++;
////                case 3: *to = *from++;
////                case 2: *to = *from++;
////                case 1: *to = *from++;
////        } while ((count -= 8) > 0);
////    }
//    
//    
//    return 0;
//}
//
//
//char* homeHandle(ZHttpServer* self) {
//    ZDict* dict = self->dictPath;
//    char* path = self->path;
//    char* msg = "<html><body>hello world</body></html>";
//
//    if (csIsEqual("/", path) || csIsEqual("/home", path)) {
//        
//        return msg;
//    }
//    
//    return NULL;
//}
//
//
//char* postListHandle(ZHttpServer* self) {
//    ZDict* dict = self->dictPath;
//    char* path = self->path;
//    char* msg = "<html><body>hello world</body></html>";
//
//    if (csIsEqual("/postList", path)) {
//        
//        return msg;
//    }
//    
//    return NULL;
//}
//
//char* loginHandle(ZHttpServer* self) {
//    ZDict* dict = self->dictPath;
//    char* path = self->path;
//    char* msg = "<html><body>hello world</body></html>";
//    
//    if (csIsEqual("/login", path)) {
//        
//        return msg;
//    }
//    
//    return NULL;
//}
//
//int main_main(int argc, const char * argv[])
//{
//    ZDict* pathHandle = zdictInit();
//    zdictSet(pathHandle, "/", homeHandle);
//    zdictSet(pathHandle, "/home", homeHandle);
//    zdictSet(pathHandle, "/postList", postListHandle);
//    zdictSet(pathHandle, "/login", loginHandle);
//    
//    ZHttpServer* server = zhttpServerInit(8000);
//    
//    zhttpServerAccept(server, pathHandle);
//
//
//    
////
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
////    function();
//
//    
////    Record *r = [[Record alloc] initWithGroupName:@"g"];
////    
////    
////    [IDMap share];
////    
////    NSDate *date = [[NSDate alloc] init];
////    long ds = [date timeIntervalSinceNow];
////    
////    for (int i = 0; i < 10000; i++) {
////        int32_t rid = [r insert:@{@"userName":@"zhangxinwei", @"age":@"26", @"mobile":@"15210743874"}];
//////        NSLog(@"rid %d dbsize %lld", rid, [IDMap share].fileLen);
////    }
////    
////    
////    
////    long de = [date timeIntervalSinceNow];
////    
////    NSLog(@"%ld", de - ds);
////    NSLog(@"dbsize %lld",[IDMap share].fileLen);
////
//////    NSLog(@"%@", [r selectByPublicId:47]);
//////    test * t= [[test alloc] init];
//
////    test *t = [[test alloc] init];
////    NSDictionary *d = @{
////                        @"id" : @"4545",
////                        @"title" : @"这是一个相册",
////                        @"desc" : @"这个相册真的是没什么用",
////                        @"count" : @"5",
////                        @"cover" : @"http://p.3761.com/pic/99731393378256.jpg",
////                        @"is_private" : @"true",
////                        @"create_time" : @"2015-11-12"
////                        };
//////    [SimpleHttpRequest postWithParams:d path:@"http://10.8.107.35:8080/asptec/classPhotoAlbum/getClassAlbumPhoto" compeletion:nil];
////    [SimpleHttpRequest postWithParams:nil path:@"http://10.8.107.35:8080/asptec/classPhotoAlbum/getClassAlbumPhoto?class_id=1&id=24&page_size=2&create_time=" compeletion:nil];
//////    [SimpleHttpRequest postWithParams:@{@"wd":@"socket"} path:@"https://www.baidu.com/s" compeletion:nil];
//////    [SimpleHttpRequest postWithParams:nil path:@"http://www.cnblogs.com/pengyingh/articles/2341880.html" compeletion:nil];
//////    [SimpleHttpRequest postWithParams:nil path:@"http://baike.baidu.com/view/1499209.htm" compeletion:nil];
//    
//    
//    
//    return 0;
//}
//
