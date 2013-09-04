# iMAS security-check

## Background

The iMAS secuirty-check security control offers a continuous jailbreak detect and debug attach checking.  With this information, one can programatically decide to shutdown the app or other loss prevention techniques.  The security control makes system calls at the application level, in particular ptrace and getpid  

## Vulnerabilities Addressed
1. Debugger tool use
   - CWE-288: Authentication Bypass Using an Alternate Path or Channel

## Installation

- Add security-check repository as a submodule to your project `git submodule add git@github.com:project-imas/security-check.git vendor/security-check`
- Drag SecurityCheck.xcodeproj into the your project as a subproject
- Add SecurityCheck Framework to target’s build phase - target dependancies (use +)
- Add libSecurityCheck.a to targets's build phase - link binary with libraries
- include #import <SecurityCheck/SecurityCheck.h> in your code at the app delegte level to start
- 
## Usage


```
    //-----------------------------------
    // call back to weHaveAProblem
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
    
    ...
    
    
- (void) weHaveAProblem {
    
    NSLog(@"weHaveAProblem in AppDelegate");
    
    //** cause segfault
    //int *foo = (int*)-1; // make a bad pointer
    //printf("%d\n", *foo);       // causes segfault
    
    //** OR lanuch blank, black colored window that hangs the user
    SViewController *sc = [[SViewController alloc] init];
    _window.rootViewController = sc;
    [_window makeKeyAndVisible];
    
    //** recommend not EXITing as foresics can easily find exit(0) and replace with NOP
    //exit(0);
}

 ```   

Find where the function weHaveAProblem is defined and add code to exit or spin in place etc.
 
## Sample App

The sample application demonstrates the use of the security-check security control.


## License

Copyright 2013 The MITRE Corporation, All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this work except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

[![githalytics.com alpha](https://cruel-carlota.pagodabox.com/ae9356587529582d71b589a583550f60 "githalytics.com")](http://githalytics.com/project-imas/security-check)


