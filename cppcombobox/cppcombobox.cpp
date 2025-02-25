#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hGroup, hStudents, hResult;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

TCHAR groups[2][10] = {
    { TEXT("КН-П-231") },
    { TEXT("КН-Д-231") }
};

TCHAR students[2][2][30] = {
    {
        { TEXT("Єресько Доротея") },
        { TEXT("Шостя Чернин") }
    },

    {
        { TEXT("Цегельський Алевтин") },
        { TEXT("Ярощук Юліан") }
    }
};

double marks[2][2][3] = {
    { 
        { {9.1}, {4.1}, {8.8} },
        { {5.9}, {11.2}, {12.0} }
    },

    { 
        { {8.9}, {10.9}, {16.68} },
        { {9.9}, {9.9}, {9.9} }
    }
};

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hGroup = GetDlgItem(hWnd, IDC_COMBO1);
        hStudents = GetDlgItem(hWnd, IDC_LIST1);
        hResult = GetDlgItem(hWnd, IDC_EDIT1);

        for (int i = 0; i < 2; i++)
        {
            SendMessage(hGroup, CB_ADDSTRING, i, LPARAM(groups[i]));

            for (int j = 0; j < 2; j++)
            {

            }
        }

        return TRUE;
    case WM_COMMAND:


        if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == CBN_SELCHANGE)
        {
            SendMessage(hStudents, LB_RESETCONTENT, 0, 0);
            int index = SendMessage(hGroup, CB_GETCURSEL, 0, 0);
            switch (index)
            {
            case 0:
                for (int i = 0; i < 2; i++)
                {
                    SendMessage(hStudents, LB_SETITEMDATA, index, (LPARAM)students[i]);
                }
                break;
            }
        }

        if (wParam == IDC_BUTTON1)
        {
            EndDialog(hWnd, 0);
        }
        
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}