#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hGroup, hStudents, hResult, hRadio1, hRadio2, hRadio3;
int groupId, studentId = -1;
TCHAR buf[10];

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
        { {8.9}, {10.9}, {11.6} },
        { {9.9}, {9.9}, {9.9} }
    }
};

void ResetControls(HWND& hWnd)
{
    SendDlgItemMessage(hWnd, IDC_RADIO1, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hWnd, IDC_RADIO2, BM_SETCHECK, BST_UNCHECKED, 0);
    SendDlgItemMessage(hWnd, IDC_RADIO3, BM_SETCHECK, BST_UNCHECKED, 0);
    SendMessage(hResult, WM_SETTEXT, 0, NULL);
    studentId = -1;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hGroup = GetDlgItem(hWnd, IDC_COMBO1);
        hStudents = GetDlgItem(hWnd, IDC_LIST1);
        hResult = GetDlgItem(hWnd, IDC_EDIT1);
        hRadio1 = GetDlgItem(hWnd, IDC_RADIO1);
        hRadio2 = GetDlgItem(hWnd, IDC_RADIO2);
        hRadio3 = GetDlgItem(hWnd, IDC_RADIO3);

        for (int i = 0; i < 2; i++)
        {
            SendMessage(hGroup, CB_ADDSTRING, i, LPARAM(groups[i]));
        }

        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_COMBO1 && HIWORD(wParam) == CBN_SELCHANGE)
        {
            ResetControls(hWnd);
            SendMessage(hStudents, LB_RESETCONTENT, 0, 0);

            int index = SendMessage(hGroup, CB_GETCURSEL, 0, 0);
            for (int i = 0; i < 2; i++)
            {
                SendMessage(hStudents, LB_ADDSTRING, i, (LPARAM)students[index][i]);
            }
            groupId = index;
        }

        if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE)
        {
            ResetControls(hWnd);

            int index = SendMessage(hStudents, LB_GETCURSEL, 0, 0);
            studentId = index;
        }

        for (int i = 0; i < 3; i++)
        {
            if (wParam == IDC_RADIO1 + i)
            {
                swprintf(buf, 10, TEXT("%.1f"), marks[groupId][studentId][i]);
                SendMessage(hResult, WM_SETTEXT, 0, LPARAM(buf));
            }
        }

        if (studentId != -1)
        {
            EnableWindow(hRadio1, TRUE);
            EnableWindow(hRadio2, TRUE);
            EnableWindow(hRadio3, TRUE);
        }
        else
        {
            EnableWindow(hRadio1, FALSE);
            EnableWindow(hRadio2, FALSE);
            EnableWindow(hRadio3, FALSE);
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