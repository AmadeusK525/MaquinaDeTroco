#pragma once

#include "wx/panel.h"
#include "wx/button.h"

#include <vector>

#include "MainFrame.h"

class Filler;

#ifndef CONTAINER_H_
#define CONTAINER_H_

using std::vector;

class Container : public wxPanel {
private:
    MainFrame* parent = nullptr;

    wxPanel* top = nullptr;

    wxStaticText* fivePanel = nullptr,
        * tenPanel = nullptr,
        * twentyFivePanel = nullptr,
        * fiftyPanel = nullptr,
        * onePanel = nullptr;

    wxStaticText* fiveCount = nullptr,
        * tenCount = nullptr,
        * twentyFiveCount = nullptr,
        * fiftyCount = nullptr,
        * oneCount = nullptr;

    wxButton* fill = nullptr;
    wxButton* deplete = nullptr;

    wxBoxSizer* ver = nullptr;

    unsigned int five = 0;
    unsigned int ten = 0;
    unsigned int twentyFive = 0;
    unsigned int fifty = 0;
    unsigned int one = 0;

public:
    Container(wxWindow* parent);

    double getCount();
    vector<int> getCoins();

    void updateValues();
    void doFillContainer(unsigned int coins[5], bool showDialog = true);
    bool doDepleteContainer(unsigned int coins[5], string title = "Moedas retiradas");

    void fillContainer(wxCommandEvent& event);
    void depleteContainer(wxCommandEvent& event);
    void disableBtns();
    void enableBtns();

    DECLARE_EVENT_TABLE()
};

enum {
    BUTTON_Fill,
    BUTTON_Deplete
};

#endif
