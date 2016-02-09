//
//  fileCheck.h
//  SecurityCheck
//
//  Created by ct on 2/26/13.
//  Copyright (c) 2013 The MITRE Corporation. All rights reserved.
//

#ifndef SecurityCheck_FileCheck_h
#define SecurityCheck_FileCheck_h

#import <sys/stat.h>

#define FILENAME_PRIMER 230

#define FILENAME_XOR(_key, _input, _length)                                    \
                                                                               \
    for (size_t _i = 0; _i < _length; _i++) { _input[_i] ^= _key; }            \

/* 
 ------------------------------------------------
 chkFiles
 ------------------------------------------------
 /Applications/Cydia.app
 /Library/MobileSubstrate/MobileSubstrate.dylib
 /var/cache/apt
 /var/lib/apt
 /var/lib/cydia
 /var/log/syslog
 /var/tmp/cydia.log
 /bin/bash
 /bin/sh
 /usr/sbin/sshd
 /usr/libexec/ssh-keysign
 /etc/ssh/sshd_config
 /etc/apt
 
*/

#define checkFiles(fcb) {                                                      \
                                                                               \
    char chkFiles[] = {                                                        \
                                                                               \
     201,167,150,150,138,143,133,135,146,143,137,136,149,201,165,159,130,143   \
    ,135,200,135,150,150,0                                                     \
    ,200,171,142,133,149,134,149,158,200,170,136,133,142,139,130,180,146,133   \
    ,148,147,149,134,147,130,200,170,136,133,142,139,130,180,146,133,148,147   \
    ,149,134,147,130,201,131,158,139,142,133,0                                 \
    ,199,158,137,154,199,139,137,139,128,141,199,137,152,156,0                 \
    ,198,159,136,155,198,133,128,139,198,136,153,157,0                         \
    ,197,156,139,152,197,134,131,136,197,137,147,142,131,139,0                 \
    ,196,157,138,153,196,135,132,140,196,152,146,152,135,132,140,0             \
    ,195,154,141,158,195,152,129,156,195,143,149,136,133,141,194,128,131,139,0 \
    ,194,143,132,131,194,143,140,158,133,0                                     \
    ,193,140,135,128,193,157,134,0                                             \
    ,192,154,156,157,192,156,141,134,129,192,156,156,135,139,0                 \
    ,223,133,131,130,223,156,153,146,149,136,149,147,223,131,131,152,221,155   \
    ,149,137,131,153,151,158,0                                                 \
    ,222,148,133,146,222,130,130,153,222,130,130,153,149,174,146,158,159,151   \
    ,152,150,0                                                                 \
    ,221,151,134,145,221,147,130,134,0                                         \
    ,0                                                                         \
    };                                                                         \
                                                                               \
    struct stat fStat;                                                         \
                                                                               \
    char    *fp = chkFiles;                                                    \
    size_t flen = strlen(fp);                                                  \
    int    fxor = FILENAME_PRIMER;                                             \
    int    fcnt = 0;                                                           \
                                                                               \
    while (flen) {                                                             \
                                                                               \
        fxor    = FILENAME_PRIMER + fcnt;                                      \
                                                                               \
        FILENAME_XOR(fxor, fp, flen);                                          \
                                                                               \
        if (stat(fp, &fStat) == 0) { fcb(); }                                  \
                                                                               \
        fp     += flen + 1;                                                    \
        flen    = strlen(fp);                                                  \
                                                                               \
        fcnt++;                                                                \
    }                                                                          \
}

/*
 ------------------------------------------------
 chkLinks
 ------------------------------------------------
 /Library/Ringtones
 /Library/Wallpaper
 /usr/arm-apple-darwin9
 /usr/include
 /usr/libexec
 /usr/share
 /Applications
 
*/

#define checkLinks(lcb) {                                                      \
                                                                               \
    char chkLinks[] = {                                                        \
                                                                               \
         201,170,143,132,148,135,148,159,201,180,143,136,129,146,137,136,131   \
        ,149,0                                                                 \
        ,200,171,142,133,149,134,149,158,200,176,134,139,139,151,134,151,130   \
        ,149,0                                                                 \
        ,199,157,155,154,199,137,154,133,197,137,152,152,132,141,197,140,137   \
        ,154,159,129,134,209,0                                                 \
        ,198,156,154,155,198,128,135,138,133,156,141,140,0                     \
        ,197,159,153,152,197,134,131,136,143,146,143,137,0                     \
        ,196,158,152,153,196,152,131,138,153,142,0                             \
        ,195,173,156,156,128,133,143,141,152,133,131,130,159,0                 \
        ,0                                                                     \
                                                                               \
    };                                                                         \
                                                                               \
    struct stat lStat;                                                         \
                                                                               \
    char    *lp = chkLinks;                                                    \
    size_t llen = strlen(lp);                                                  \
    int    lxor = FILENAME_PRIMER;                                             \
    int    lcnt = 0;                                                           \
                                                                               \
    while (llen) {                                                             \
                                                                               \
        lxor    = FILENAME_PRIMER + lcnt;                                      \
                                                                               \
        FILENAME_XOR(lxor, lp, llen);                                          \
                                                                               \
        if ( lstat(lp, &lStat) == 0)                                           \
                                                                               \
            if (lStat.st_mode & S_IFLNK) { lcb(); }                            \
                                                                               \
                                                                               \
        lp     += llen + 1;                                                    \
        llen    = strlen(lp);                                                  \
                                                                               \
        lcnt++;                                                                \
    }                                                                          \
}

#endif
