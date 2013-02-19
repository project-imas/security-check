//
//  debugCheckTemplate.h
//  SecurityCheck
//
//  Created by ct on 2/14/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "debugCheck.h"

@interface debugCheckTemplate : NSObject {

//--------------------------------
// debugCheck timer
//--------------------------------
dispatch_queue_t  _queue;
dispatch_source_t _timer;

}

@end
