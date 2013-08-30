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
- include #import <SecurityCheck/SecurityCheck.h> in your code at the app delegte level to start
- 
## Usage


`
    //-----------------------------------
    // jailbreak detection
    //-----------------------------------
    checkFork(chkCallback);
    checkFiles(chkCallback);
    checkLinks(chkCallback);
 `   
 
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


