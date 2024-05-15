#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace seneca {
    class Menu {
        char* m_text; 
        int m_noOfSel; 
    public:
        Menu(const char* MenuContent = "", int NoOfSelections = 0);
        virtual ~Menu();
        int& operator>>(int& Selection); 
     
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;
    };
}

#endif 