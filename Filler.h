#pragma once

#include "wx/frame.h"
#include "wx/spinctrl.h"
#include "wx/stattext.h"
#include "wx/gbsizer.h"
#include "wx/button.h"

//#include <string>

#include "MainFrame.h"

#ifndef FILLER_H_
#define FILLER_H_

class Filler : public wxFrame {
private:
    MainFrame* parent = nullptr;

    wxSpinCtrl* one = nullptr, * fifty = nullptr, * tf = nullptr, * ten = nullptr, * five = nullptr;
    wxStaticText* oneLabel = nullptr, * fiftyLabel = nullptr, * tfLabel = nullptr,
        * tenLabel = nullptr, * fiveLabel = nullptr, * totalLabel = nullptr;

    wxStaticText* quant1 = nullptr, * quant2 = nullptr, * quant3 = nullptr,
        * quant4 = nullptr, * quant5 = nullptr, * quantTotal = nullptr;

    wxButton* okBtn = nullptr;
    wxButton* cancelBtn = nullptr;

    wxGridBagSizer* gridSizer = nullptr;
    
public:
    Filler(wxWindow* parent, string name, bool fill = true);

    void updateValues(wxSpinEvent& event);
    string calcString(double value);

    void fillOkPressed(wxCommandEvent& event);
    void depleteOkPressed(wxCommandEvent& event);
    void cancelPressed(wxCommandEvent& event);

    void onClose(wxCloseEvent& event);

    DECLARE_EVENT_TABLE()
};

enum {
    BUTTON_FillOk,
    BUTTON_DepleteOk,

    BUTTON_Cancel
};

#endif FILLER_H_
