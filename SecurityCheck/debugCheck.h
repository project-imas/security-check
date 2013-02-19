//
//  debugCheck.h
//
//  Created by ct on 1/30/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#ifndef debugMe_dbgChk_h
#define debugMe_dbgChk_h

#import <sys/sysctl.h>

#define debugCheckNameSz 17

#define dbgGetPid(pid) {                                                      \
    int                      err = 0;                                         \
    struct kinfo_proc *proc_list = NULL;                                      \
    size_t                length = 0;                                         \
    static const int sysName[]   = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 }; \
                                                                              \
    err = sysctl( (int *)sysName                                              \
                , (sizeof(sysName) / sizeof(*sysName)) - 1                    \
                , NULL                                                        \
                , &length                                                     \
                , NULL                                                        \
                , 0);                                                         \
                                                                              \
    if (!err) {                                                               \
                                                                              \
        proc_list = malloc(length);                                           \
                                                                              \
        if (proc_list) {                                                      \
                                                                              \
            err = sysctl( (int *)sysName                                      \
                        , (sizeof(sysName) / sizeof(*sysName)) - 1            \
                        , proc_list                                           \
                        , &length                                             \
                        , NULL                                                \
                        , 0);                                                 \
        }                                                                     \
    }                                                                         \
                                                                              \
    if (!err && proc_list) {                                                  \
                                                                              \
        int proc_count = length / sizeof(struct kinfo_proc);                  \
                                                                              \
        char buf[debugCheckNameSz];                                           \
                                                                              \
        NSString * appName = [[NSBundle mainBundle]                           \
        objectForInfoDictionaryKey:@"CFBundleName"];                          \
                                                                              \
        NSString * procName;                                                  \
                                                                              \
        for (int i = 0; i < proc_count; i++) {                                \
                                                                              \
            pid_t procPid = proc_list[i].kp_proc.p_pid;                       \
                                                                              \
            strlcpy(buf, proc_list[i].kp_proc.p_comm, debugCheckNameSz);      \
                                                                              \
            procName = [NSString stringWithFormat:@"%s",buf];                 \
                                                                              \
            if ( [appName isEqual:procName] ) {                               \
                                                                              \
                *pid = procPid;                                               \
                                                                              \
                break;                                                        \
            }                                                                 \
        }                                                                     \
    }                                                                         \
                                                                              \
    if (proc_list) free(proc_list);                                           \
}                                                                             

#define DBGCHK_P_TRACED 0x00000800	/* Debugged process being traced */

#define dbgCheck(cb){                            \
    pid_t pid = 0;                               \
                                                 \
    dbgGetPid(&pid);                             \
                                                 \
    size_t sz = sizeof(struct kinfo_proc);       \
                                                 \
    struct kinfo_proc info;                      \
                                                 \
    memset(&info, 0, sz);                        \
                                                 \
    int    name[4];                              \
                                                 \
    name [0] = CTL_KERN;                         \
    name [1] = KERN_PROC;                        \
    name [2] = KERN_PROC_PID;                    \
    name [3] = pid;                              \
                                                 \
    if (sysctl(name,4,&info,&sz,NULL,0) != 0)    \
        exit(EXIT_FAILURE);                      \
                                                 \
    if (info.kp_proc.p_flag & DBGCHK_P_TRACED)   \
        cb();                                    \
                                                 \
}                                                


// check <sys/ptrace.h> for PT_DENY_ATTACH == 31

extern int ptrace(int request, pid_t pid, caddr_t addr, int data);

#define dbgStop ptrace(31,0,0,0);

#endif
