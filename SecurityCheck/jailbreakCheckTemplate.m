//
//  jailbreakCheckTemplate.m
//  SecurityCheck
//
//  Created by ct on 2/26/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#import "jailbreakCheckTemplate.h"

@interface jailbreakCheckTemplate ()

//--------------------------------
// Callback block from checks
//--------------------------------
typedef void (^cbBlock) (void);

@end

@implementation jailbreakCheckTemplate

-(id) init {
    
    self = [super init];
    
    if (nil != self) {
        
        //-----------------------------------
        // call weHaveAProblem
        //-----------------------------------
        cbBlock chkCallback  = ^{
            
            __weak id weakSelf = self;
            
            if (weakSelf) [weakSelf weHaveAProblem];
        };

        //-----------------------------------
        // jailbreak detection
        //-----------------------------------
        checkFork(chkCallback);
        checkFiles(chkCallback);
        checkLinks(chkCallback);
    }
    
    return self;
}

//--------------------------------------------------------------------
// if the device is jailbroken then this method will be called
//--------------------------------------------------------------------
- (void) weHaveAProblem {
    
    printf("We have a problem - jailbroken!");
    
}

@end
