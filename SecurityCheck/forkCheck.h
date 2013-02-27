//
//  forkCheck.h
//  SecurityCheck
//
//  Created by ct on 2/26/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#ifndef SecurityCheck_forkCheck_h
#define SecurityCheck_forkCheck_h

#define checkFork(forkCb) {                                                    \
                                                                               \
    pid_t child = fork();                                                      \
                                                                               \
    if (child == 0) { exit(0); }                                               \
    if (child > 0)  { forkCb();}                                               \
}

#endif
