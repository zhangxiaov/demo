////
////  test.m
////  oc_demo
////
////  Created by zhangxinwei on 15/11/27.
////  Copyright © 2015年 zhangxinwei. All rights reserved.
////
//
//#import "test.h"
//#import "SimpleClientSocket.h"
//#import "SimpleServerSocket.h"
//
//@implementation test
//- (instancetype)init
//{
//    self = [super init];
//    if (self) {
////        NSString *testpath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] stringByAppendingPathComponent:@"test"];
////        
////        NSFileManager *fm = [NSFileManager defaultManager];
////        if ([fm fileExistsAtPath:testpath]) {
////            
////        }else {
////            [fm createFileAtPath:testpath contents:nil attributes:nil];
////        }
////        
////        NSFileHandle *fh = [NSFileHandle fileHandleForUpdatingAtPath:testpath];
////        [fh seekToFileOffset:1000];
////        [fh writeData:[@"terere" dataUsingEncoding:NSUTF8StringEncoding]];
////        [fh closeFile];
//        
//        
//        _client = [[SimpleClientSocket alloc] initWithHost:@"127.0.0.1" port:@"8000"];
//        _server = [[SimpleServerSocket alloc] initWithPort:@"8000"];
//        NSLog(@"started listening");
//        [_server listen];
//        int count = 10;
//        
//        
//        [NSThread detachNewThreadSelector:@selector(sendWithDelay) toTarget:self withObject:nil];
//        
//        [_client connect];
//
//        
//        NSData *data = [_client getData];
//        NSLog(@"client getdata = %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
//    }
//    return self;
//}
//
//- (void)sendWithDelay {
//    
//    int clientFd = [_server accept];
//    if (clientFd <= 0) {
//        NSLog(@"error client");
//        return;
//    }else {
//        NSLog(@"test");
//    }
//
//    [_server sendData:[@"hello client" dataUsingEncoding:NSUTF8StringEncoding] toClient:clientFd];
//}
//
//
//@end
