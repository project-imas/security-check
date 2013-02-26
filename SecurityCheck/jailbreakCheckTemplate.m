//
//  jailbreakCheckTemplate.m
//  SecurityCheck
//
//  Created by ct on 2/26/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#import "jailbreakCheckTemplate.h"

@implementation jailbreakCheckTemplate

-(id) init {
    
    self = [super init];
    
    if (nil != self) {
        
        //-----------------------------------
        // jailbreak detection
        //-----------------------------------
        checkFork
        checkFiles
    }
    
    return self;
}
@end
