#pragma once

#include "wx/panel.h"
#include "wx/textctrl.h"
#include "wx/stattext.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/valnum.h"

#include <vector>

#include "MainFrame.h"

#ifndef INPUTPANELS_H_
#define INPUTPANELS_H_

using std::vector;

class InputPanels : public wxPanel {
private:
    MainFrame* parent = nullptr;

    double m_p = 0.0;
    double m_r = 0.0;
    double m_c = 0.0;

    wxTextCtrl* price = nullptr;
    wxTextCtrl* received = nullptr;
    wxTextCtrl* change = nullptr;

    wxStaticText* priceLabel = nullptr;
    wxStaticText* receivedLabel = nullptr;
    wxStaticText* changeLabel = nullptr;

    wxButton* calc = nullptr;
    wxButton* pay = nullptr;

    wxStaticText* quant1 = nullptr, * quant2 = nullptr, * quant3 = nullptr,
        * quant4 = nullptr, * quant5 = nullptr, * quantTotal = nullptr;

    wxBoxSizer* mainSizer = nullptr;

    bool isDefault = true;

    unsigned int changeCoins[5]{ 0 };
       
public:
    InputPanels(wxWindow* parent);

    void updateChange(wxCommandEvent& event);

    void calculateChange(wxCommandEvent& event);
    void payChange(wxCommandEvent& event);

    void setDefault();

    DECLARE_EVENT_TABLE()
};

enum {
    BUTTON_Calc,
    BUTTON_Pay,

    TEXT_Price,
    TEXT_Received
};

#endif
