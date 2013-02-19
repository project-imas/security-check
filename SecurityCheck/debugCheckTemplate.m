//
//  debugCheckTemplate.m
//  SecurityCheck
//
//  This is an example of how to implementing the debugCheck
//
//  Created by ct on 2/14/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#import "debugCheckTemplate.h"

@interface debugCheckTemplate ()

//--------------------------------
// Callback block from debugCheck
//--------------------------------
typedef void (^cbBlock) (void);

@end

@implementation debugCheckTemplate

-(id) init {
    
    self = [super init];
    
    if (nil != self) {
        
        
        //--------------------------------
        // do not allow debuggers
        //--------------------------------
        dbgStop;
        
        //---------------------------------------------------------------------
        // check for the presence of a debugger
        // call weHaveAProblem if there is one
        //---------------------------------------
        cbBlock dbChkCallback  = ^{
            
            __weak id weakSelf = self;
            
            if (weakSelf) [weakSelf weHaveAProblem];
            
        };
        
        _queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        _timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER
                                        , 0
                                        , 0
                                        ,_queue);
        
        dispatch_source_set_timer(_timer
                                  ,dispatch_time(DISPATCH_TIME_NOW, 0)
                                  ,1.0 * NSEC_PER_SEC
                                  ,0.0 * NSEC_PER_SEC);
        
        dispatch_source_set_event_handler(_timer, ^{dbgCheck(dbChkCallback);});
        
        dispatch_resume(_timer);
        
        //---------------------------------------------------------------------
    }
    
    return self;
}

//--------------------------------------------------------------------
// if a debugger is attched to the app then this method will be called
//--------------------------------------------------------------------
- (void) weHaveAProblem {
    
    printf("Houston we have a problem - debugger attached!");
    
}
@end
