//
//  forkCheck.h
//  SecurityCheck
//
//  Created by ct on 2/26/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#ifndef SecurityCheck_forkCheck_h
#define SecurityCheck_forkCheck_h

#define FORK_OUT() raise(SIGKILL); abort(); exit(EXIT_FAILURE);

#define checkFork {                                                            \
                                                                               \
    pid_t child = fork();                                                      \
                                                                               \
    if (child == 0) { exit(0);   }                                             \
    if (child > 0)  { FORK_OUT();}                                             \
}

#endif
