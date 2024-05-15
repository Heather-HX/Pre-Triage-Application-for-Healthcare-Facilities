#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <cstring>
#include <iostream>

using namespace std;

namespace seneca {
    Menu::Menu(const char* MenuContent, int NoOfSelections) : m_noOfSel(NoOfSelections) {
        if (MenuContent) {
            m_text = new char[strlen(MenuContent) + 1];
            strcpy(m_text, MenuContent);
        }
        else {
            m_text = nullptr;
        }
    }

    Menu::~Menu() {
        delete[] m_text;
    }

    int& Menu::operator>>(int& Selection) {
        cout << m_text;
   
        cin >> Selection;
        return Selection;
    }
}