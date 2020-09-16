#pragma once

#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/listctrl.h"
#include "wx/gbsizer.h"
#include "wx/textctrl.h"
#include "wx/stattext.h"
#include "wx/button.h"

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

class Container;
class InputPanels;

class MainFrame: public wxFrame {
private:
    wxPanel* mainPanel = nullptr;
    InputPanels* values = nullptr;
    Container* container = nullptr;
    wxGridBagSizer* numbersSizer = nullptr;

    wxStaticText* current = nullptr;

    wxListView* log = nullptr;
    short curLog = 0;

    wxBoxSizer* ver = nullptr;

    string currentPath = "";
    bool isSaved = false;

public:
    MainFrame(wxWindow* parent = nullptr,
        const string& title = "",
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);

    void updateCurrent(string cur);

    vector<int> getCoins();

    void fillContainer(unsigned int coins[5]);
    bool depleteContainer(unsigned int coins[5]);

    void setDefaultChange();
    void subtractChange(unsigned int changeCoins[5]);

    void disableAll();
    void enableAll();

    void addLog(string ocur, string time, string date);

    void save(wxCommandEvent& event);
    void saveAs(wxCommandEvent& event);
    void open(wxCommandEvent& event);
    void load();
    void setLast();
    void getLast();

    void onClose(wxCloseEvent& event);

    DECLARE_EVENT_TABLE()
};

enum {
    MENU_Save,
    MENU_SaveAs,
    MENU_Open
};

#endif
