//
//  debugCheck.h
//
//  Created by ct on 1/30/13.
//  Copyright (c) 2013 MITRE. All rights reserved.
//

#ifndef debugMe_dbgChk_h
#define debugMe_dbgChk_h

#import <sys/sysctl.h>

#if TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR

//------------------------------------------
// Assembly level interface to sysctl
//------------------------------------------

#define sysCtlSz(nm,cnt,sz)   readSys((int *)nm,cnt,NULL,sz)
#define sysCtl(nm,cnt,lst,sz) readSys((int *)nm,cnt,lst, sz)

#else

//------------------------------------------
// C level interface to sysctl
//------------------------------------------

#define sysCtlSz(nm,cnt,sz)   sysctl((int *)nm,cnt,NULL,sz,NULL,0)
#define sysCtl(nm,cnt,lst,sz) sysctl((int *)nm,cnt,lst, sz,NULL,0)

#endif

int readSys(int *, u_int, void *, size_t *);

#define debugCheckNameSz 17

#define dbgGetPid(pid) {                                                      \
    int                      err = 0;                                         \
    struct kinfo_proc *proc_list = NULL;                                      \
    size_t                length = 0;                                         \
    static const int sysName[]   = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 }; \
                                                                              \
    err = sysCtlSz((int *)sysName, 4, &length);                               \
                                                                              \
    if (!err) {                                                               \
                                                                              \
        proc_list = malloc(length);                                           \
                                                                              \
        if (proc_list) {                                                      \
                                                                              \
            err = sysCtl((int *)sysName, 4, proc_list, &length);              \
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

#define debugCheck(cb) {                                                       \
    pid_t pid = 0;                                                             \
                                                                               \
    dbgGetPid(&pid);                                                           \
                                                                               \
    size_t sz = sizeof(struct kinfo_proc);                                     \
                                                                               \
    struct kinfo_proc info;                                                    \
                                                                               \
    memset(&info, 0, sz);                                                      \
                                                                               \
    int    name[4];                                                            \
                                                                               \
    name [0] = CTL_KERN;                                                       \
    name [1] = KERN_PROC;                                                      \
    name [2] = KERN_PROC_PID;                                                  \
    name [3] = pid;                                                            \
                                                                               \
    if (sysCtl(name,4,&info,&sz) != 0) exit(EXIT_FAILURE);                     \
                                                                               \
    if (info.kp_proc.p_flag & DBGCHK_P_TRACED) {                               \
                                                                               \
        dispatch_source_cancel(_timer);                                        \
                                                                               \
        cb();                                                                  \
                                                                               \
    }                                                                          \
}

#define dbgCheck(cb) {                                                         \
                                                                               \
    dispatch_queue_t  _queue =                                                 \
        dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);         \
                                                                               \
    dispatch_source_t _timer =                                                 \
        dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER                      \
                              , 0                                              \
                              , 0                                              \
                              ,_queue);                                        \
                                                                               \
    dispatch_source_set_timer(_timer                                           \
                              ,dispatch_time(DISPATCH_TIME_NOW, 0)             \
                              ,1.0 * NSEC_PER_SEC                              \
                              ,0.0 * NSEC_PER_SEC);                            \
                                                                               \
    dispatch_source_set_event_handler(_timer, ^{debugCheck(cb)});              \
                                                                               \
    dispatch_resume(_timer);                                                   \
}


// check <sys/ptrace.h> for PT_DENY_ATTACH == 31

extern int ptrace(int request, pid_t pid, caddr_t addr, int data);

#define dbgStop ptrace(31,0,0,0);

#endif
