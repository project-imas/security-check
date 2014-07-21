Pod::Spec.new do |s|
    s.name          = 'SecurityCheck'
    s.version       = '1.0'
    s.license       = 'Apache License 2.0'

    s.summary       = 'Application-level attached debug detect and jailbreak checking'
    s.description   = %[
        The iMAS security-check security control offers a continuous jailbreak detect and debug attach checking. With this information, one can programatically decide to shutdown the app or other loss prevention techniques.
    ]
    s.homepage      = 'https://github.com/project-imas/security-check'
    s.authors       = {
        'MITRE' => 'imas-proj-list@lists.mitre.org'
    }
    
    s.source        = {
        :git => 'https://github.com/project-imas/security-check.git',
        :tag => s.version.to_s
    }
    s.source_files  = 'SecurityCheck/*.{m,h,s}'
    s.exclude_files = 'SecurityCheck/*Template*'

    s.platform = :ios
    s.ios.deployment_target = '6.1'
    s.requires_arc = true
end