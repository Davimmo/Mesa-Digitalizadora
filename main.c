#include <windows.h>
#include <stdio.h>

void sendKeyCombo(WORD modifier1, WORD modifier2, WORD key) {
    INPUT input[6] = {0};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = modifier1;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = modifier2;

    input[2].type = INPUT_KEYBOARD;
    input[2].ki.wVk = key;

    input[3].type = INPUT_KEYBOARD;
    input[3].ki.wVk = key;
    input[3].ki.dwFlags = KEYEVENTF_KEYUP;

    input[4].type = INPUT_KEYBOARD;
    input[4].ki.wVk = modifier2;
    input[4].ki.dwFlags = KEYEVENTF_KEYUP;

    input[5].type = INPUT_KEYBOARD;
    input[5].ki.wVk = modifier1;
    input[5].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(6, input, sizeof(INPUT));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    int toggle = 0;

    RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, '9');

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY && msg.wParam == 1) {

            if (toggle == 0) {
                sendKeyCombo(VK_CONTROL, VK_SHIFT, 'A');
                toggle = 1;
            } else {
                sendKeyCombo(VK_CONTROL, VK_SHIFT, 'D');
                toggle = 0;
            }
        }
    }

    return 0;
}
