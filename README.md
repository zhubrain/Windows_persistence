# Windows_persistence
Ways for malwares to gain persistence in Windows.

## 1. Title : Ease of Access - AtBroker.exe  
Programs under register key "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Accessibility\ATs" will be executed by windows binary "AtBroker.exe". After a configuration in register "HKCU\Software\Microsoft\Windows NT\CurrentVersion\Accessibility\Configuration = …", the process will be executed anytime when a user log on, or when a destop change happens(e.g., when uac pops up).
