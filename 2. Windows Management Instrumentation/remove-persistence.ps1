#Removing the existing instances that wmi-persistence.ps1 used.
Get-WmiObject -Namespace "root\subscription" -Query "select * from __EventFilter where Name like '%malware%'" | Remove-WmiObject -Verbose
Get-WmiObject -Namespace "root\subscription" -Query "select * from CommandLineEventConsumer where Name like '%malware%'" | Remove-WmiObject -Verbose
Get-WmiObject -Namespace "root\subscription" -Query "select * from __FilterToConsumerBinding where __Path like '%malware%'" | Remove-WmiObject -Verbose
