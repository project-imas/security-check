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
        
        
        //-------------------------------------------
        // do not allow debuggers
        //-------------------------------------------
        dbgStop;
        
        //-------------------------------------------
        // check for the presence of a debugger
        // call weHaveAProblem if there is one
        //-------------------------------------------
        cbBlock dbChkCallback  = ^{
            
            __weak id weakSelf = self;
            
            if (weakSelf) weHaveAProblem();
            
        };

        dbgCheck(dbChkCallback);
    }
    
    return self;
}



@end

//--------------------------------------------------------------------
// if a debugger is attched to the app then this method will be called
//--------------------------------------------------------------------
void weHaveAProblem() {
    
    printf("We have a problem - debugger attached!");
    
}