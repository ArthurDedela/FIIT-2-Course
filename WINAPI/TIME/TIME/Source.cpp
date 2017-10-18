#define UNICODE
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

constexpr wchar_t weekday[7][12] = { L"�����������", L"�����������", L"�������", L"�����", L"�������", L"�������", L"�������" };


int main() {
    LARGE_INTEGER timerFrequency, timerStart, timerStop;

    QueryPerformanceFrequency(&timerFrequency);
    QueryPerformanceCounter(&timerStart);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    WriteConsole(hConsole, L"��������: ������ �����; ������: 8�30-202�-16\n", 45, NULL, NULL);
    WriteConsole(hConsole, L"�������: ������� �� ����� ������ �������� �������� ���. ��������, \"�����������\"\n", 80, NULL, NULL);

    auto t = time(NULL);
    auto tm_time = localtime(&t);
    WriteConsole(hConsole, weekday[tm_time->tm_wday], lstrlenW(weekday[tm_time->tm_wday]), NULL, NULL);
    WriteConsole(hConsole, L"\n", 1, NULL, NULL);  
    
    int decimal, sign;
    char *buffer;
    int precision = 10;

    QueryPerformanceCounter(&timerStop);

    double elapsedTime = (double(timerStop.QuadPart - timerStart.QuadPart) / timerFrequency.QuadPart);

    buffer = _ecvt(elapsedTime, precision, &decimal, &sign);
        
    WriteConsole(hConsole, L"��������� ���������� ��: 0.", 27, NULL, NULL);

    if (decimal < 0) {
        decimal = abs(decimal);   
        while (decimal-- != 0) {
            WriteConsole(hConsole, L"0", 1, NULL, NULL);
        }
    }

    WriteConsoleA(hConsole, buffer, 4, NULL, NULL);
    WriteConsole(hConsole, L" seconds\n", 9, NULL, NULL);

    system("pause");

    return 0;
}