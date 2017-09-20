﻿#define UNICODE
#include <Windows.h>
#include <iostream>


struct Selection { 
    int row, col; 
};


void drawLine(const HANDLE & hConsole, const WCHAR fill[10], const WCHAR separators[3], const int selectedCol = -1);
void drawTable(const HANDLE & hConsole, const Selection & selectedItem);

const int max_row = 3, max_col = 4;


int main()
{
    return 0;
}



void drawLine(const HANDLE & hConsole, const WCHAR fill[10], const WCHAR separators[3], const int selectedCol) {

    WriteConsole(hConsole, &separators[0], 1, NULL, NULL);
    for (int j = 0; j <= max_col; j++) {
        if (j == selectedCol) {
            SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 7));
            WriteConsole(hConsole, fill, 10, NULL, NULL);
            SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 4));            
        }
        else {
            WriteConsole(hConsole, fill, 10, NULL, NULL);
        }

        if (j < max_col) WriteConsole(hConsole, &separators[1], 1, NULL, NULL);
    }

    WriteConsole(hConsole, &separators[2], 1, NULL, NULL);
    WriteConsole(hConsole, L"\n", 1, NULL, NULL);
}

void drawTable(const HANDLE & hConsole, const Selection & selectedItem) {

    WriteConsole(hConsole, L"Student: Artur Dedela. Group: 8T30-202B-16.\n", 44, NULL, NULL);
    
    drawLine(hConsole, L"══════════", L"╔╦╗");

    for (int i = 0; i <= max_row; i++) {
        drawLine(hConsole, L"   Item   ", L"║║║", (selectedItem.row == i ? selectedItem.col : -1));

        if (i < max_row) drawLine(hConsole, L"══════════", L"╠╬╣");
    }

    drawLine(hConsole, L"══════════", L"╚╩╝");
}