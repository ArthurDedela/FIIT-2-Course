#include <Windows.h>
#include <ctime>


void showError(HANDLE hConsole, long errCode) {
    TCHAR errMsg[512];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errCode, NULL, errMsg, 512, NULL);

    WriteConsole(hConsole, errMsg, strlen(errMsg), NULL, NULL);
    WriteConsole(hConsole, L"\n", 1, NULL, NULL);
}

int main() {
    HKEY hKey;
    char path[] = "WINAPI";
    DWORD disposition;
    auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    long errCode;

    WriteConsole(hConsole, "Student: Artur Dedela; Group: 8T30-202B-16\n", 44, NULL, NULL);
    WriteConsole(hConsole, "Task: Save time of last launch in registry. On the next launch show time of last launch.\n", 90, NULL, NULL);
    
    if ((errCode = RegOpenKeyEx(HKEY_CURRENT_USER, path, NULL, KEY_WRITE, &hKey)) != ERROR_SUCCESS) {
        showError(hConsole, errCode);
    }
    
    if ((errCode = RegCreateKeyEx(HKEY_CURRENT_USER, path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disposition)) != ERROR_SUCCESS) {
        showError(hConsole, errCode);
        return 1;
    }
    

    switch (disposition)
    {
    case REG_CREATED_NEW_KEY:
    {
        WriteConsole(hConsole, "First launch of the programm.\n", 31, NULL, NULL);

        auto raw_time = time(NULL);
        auto timeinfo = localtime(&raw_time);
        timeinfo->tm_hour %= 12;
        auto sz_time = asctime(timeinfo);

        if ((errCode = RegSetValueEx(hKey, "Last launch", 0, REG_SZ, (BYTE*)sz_time, strlen(sz_time))) != ERROR_SUCCESS) {
            showError(hConsole, errCode);
        }
        break;
    }

    case REG_OPENED_EXISTING_KEY:

        char sz_time[50];
        DWORD len = 50;

        RegGetValue(HKEY_CURRENT_USER, path, "Last launch", RRF_RT_REG_SZ, NULL, (BYTE*)sz_time, &len);

        WriteConsole(hConsole, "Time of last launch: ", 22, NULL, NULL);
        WriteConsole(hConsole, sz_time, len, NULL, NULL);   
        WriteConsole(hConsole, "\n", 1, NULL, NULL);
        
        auto raw_time = time(NULL);
        auto timeinfo = localtime(&raw_time);
        timeinfo->tm_hour %= 12;
        auto tm = asctime(timeinfo);

        if ((errCode != RegSetValueEx(hKey, "Last launch", 0, REG_SZ, (BYTE*)tm, strlen(tm))) != ERROR_SUCCESS) {
            showError(hConsole, errCode);
        }

        break;
    }

    RegCloseKey(hKey);

    system("pause");
    return 0;
}