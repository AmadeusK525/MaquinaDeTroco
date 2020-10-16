#include "Filler.h"

#include "wx/panel.h"

BEGIN_EVENT_TABLE(Filler, wxFrame)

EVT_SPINCTRL(100, Filler::updateValues)
EVT_SPINCTRL(50, Filler::updateValues)
EVT_SPINCTRL(25, Filler::updateValues)
EVT_SPINCTRL(10, Filler::updateValues)
EVT_SPINCTRL(5, Filler::updateValues)

EVT_BUTTON(BUTTON_FillOk, Filler::fillOkPressed)
EVT_BUTTON(BUTTON_DepleteOk, Filler::depleteOkPressed)
EVT_BUTTON(BUTTON_Cancel, Filler::cancelPressed)

EVT_CLOSE(Filler::onClose)

END_EVENT_TABLE()

Filler::Filler(wxWindow* parent, string name, bool fill) :
    wxFrame(parent, -1, name, wxDefaultPosition, wxSize(800, 400), wxFRAME_FLOAT_ON_PARENT | wxDEFAULT_FRAME_STYLE) {
    this->parent = dynamic_cast<MainFrame*>(parent);

    wxPanel* pan = new wxPanel(this);
    pan->SetBackgroundColour(wxColour(200, 200, 200));

    five = new wxSpinCtrl(pan, 5, "0");
    ten = new wxSpinCtrl(pan, 10, "0");
    tf = new wxSpinCtrl(pan, 25, "0");
    fifty = new wxSpinCtrl(pan, 50, "0");
    one = new wxSpinCtrl(pan, 100, "0");

    one->SetFont(wxFontInfo(20));
    fifty->SetFont(wxFontInfo(20));
    tf->SetFont(wxFontInfo(20));
    ten->SetFont(wxFontInfo(20));
    five->SetFont(wxFontInfo(20));

    oneLabel = new wxStaticText(pan, -1, "R$1,00", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    fiftyLabel = new wxStaticText(pan, -1, "R$0,50", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    tfLabel = new wxStaticText(pan, -1, "R$0,25", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    tenLabel = new wxStaticText(pan, -1, "R$0,10", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    fiveLabel = new wxStaticText(pan, -1, "R$0,05", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    totalLabel = new wxStaticText(pan, -1, " Total:", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);

    oneLabel->SetFont(wxFontInfo(20).Bold());
    oneLabel->SetBackgroundColour(wxColour(240, 205, 0));
    oneLabel->SetForegroundColour(wxColour(48, 48, 48));
    fiftyLabel->SetFont(wxFontInfo(20).Bold());
    fiftyLabel->SetBackgroundColour(wxColour(200, 200, 200));
    fiftyLabel->SetForegroundColour(wxColour(48, 48, 48));
    tfLabel->SetFont(wxFontInfo(20).Bold());
    tfLabel->SetBackgroundColour(wxColour(220, 170, 0));
    tfLabel->SetForegroundColour(wxColour(48, 48, 48));
    tenLabel->SetFont(wxFontInfo(20).Bold());
    tenLabel->SetBackgroundColour(wxColour(230, 180, 0));
    tenLabel->SetForegroundColour(wxColour(48, 48, 48));
    fiveLabel->SetFont(wxFontInfo(20).Bold());
    fiveLabel->SetBackgroundColour(wxColour(164, 103, 45));
    fiveLabel->SetForegroundColour(wxColour(0, 0, 0));
    totalLabel->SetFont(wxFontInfo(28).Bold());
    totalLabel->SetBackgroundColour(wxColour(30, 30, 30));
    totalLabel->SetForegroundColour(wxColour(250, 250, 250));

    quant1 = new wxStaticText(pan, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    quant2 = new wxStaticText(pan, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    quant3 = new wxStaticText(pan, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    quant4 = new wxStaticText(pan, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    quant5 = new wxStaticText(pan, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    quantTotal = new wxStaticText(pan, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);

    quant1->SetFont(wxFontInfo(20));
    quant2->SetFont(wxFontInfo(20));
    quant3->SetFont(wxFontInfo(20));
    quant4->SetFont(wxFontInfo(20));
    quant5->SetFont(wxFontInfo(20));
    quantTotal->SetFont(wxFontInfo(28));
    quant1->SetBackgroundColour(wxColour(250, 250, 250));
    quant2->SetBackgroundColour(wxColour(250, 250, 250));
    quant3->SetBackgroundColour(wxColour(250, 250, 250));
    quant4->SetBackgroundColour(wxColour(250, 250, 250));
    quant5->SetBackgroundColour(wxColour(250, 250, 250));
    quantTotal->SetBackgroundColour(wxColour(250, 250, 250));

    gridSizer = new wxGridBagSizer(5, 35);
    
    gridSizer->Add(fiveLabel, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxTOP | wxLEFT, 10);
    gridSizer->Add(tenLabel, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxTOP, 10);
    gridSizer->Add(tfLabel, wxGBPosition(0, 2), wxGBSpan(1, 1), wxEXPAND | wxTOP, 10);
    gridSizer->Add(fiftyLabel, wxGBPosition(0, 3), wxGBSpan(1, 1), wxEXPAND | wxTOP, 10);
    gridSizer->Add(oneLabel, wxGBPosition(0, 4), wxGBSpan(1, 1), wxEXPAND | wxTOP | wxRIGHT, 10);

    gridSizer->Add(five, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND | wxLEFT, 10);
    gridSizer->Add(ten, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND);
    gridSizer->Add(tf, wxGBPosition(1, 2), wxGBSpan(1, 1), wxEXPAND);
    gridSizer->Add(fifty, wxGBPosition(1, 3), wxGBSpan(1, 1), wxEXPAND);
    gridSizer->Add(one, wxGBPosition(1, 4), wxGBSpan(1, 1), wxEXPAND | wxRIGHT, 10);

    gridSizer->Add(quant5, wxGBPosition(2, 0), wxGBSpan(1, 1), wxEXPAND | wxLEFT, 10);
    gridSizer->Add(quant4, wxGBPosition(2, 1), wxGBSpan(1, 1), wxEXPAND);
    gridSizer->Add(quant3, wxGBPosition(2, 2), wxGBSpan(1, 1), wxEXPAND);
    gridSizer->Add(quant2, wxGBPosition(2, 3), wxGBSpan(1, 1), wxEXPAND);
    gridSizer->Add(quant1, wxGBPosition(2, 4), wxGBSpan(1, 1), wxEXPAND | wxRIGHT, 10);

    gridSizer->Add(totalLabel, wxGBPosition(3, 2), wxGBSpan(1, 1), wxEXPAND | wxTOP, 20);
    gridSizer->Add(quantTotal, wxGBPosition(4, 2), wxGBSpan(1, 1), wxEXPAND | wxBOTTOM, 5);

    cancelBtn = new wxButton(pan, BUTTON_Cancel, "Cancel");
    okBtn = new wxButton(pan, BUTTON_FillOk, "Abastecer");

    if (!fill) {
        okBtn->SetId(BUTTON_DepleteOk);
        okBtn->SetLabel("Retirar");
    }
    
    okBtn->SetBackgroundColour(wxColour(245, 245, 245));
    cancelBtn->SetBackgroundColour(wxColour(245, 245, 245));

    gridSizer->Add(cancelBtn, wxGBPosition(5, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 5);
    gridSizer->Add(okBtn, wxGBPosition(5, 3), wxGBSpan(1, 2), wxEXPAND | wxALL, 5);

    gridSizer->AddGrowableCol(0, 1);
    gridSizer->AddGrowableCol(1, 1);
    gridSizer->AddGrowableCol(2, 1);
    gridSizer->AddGrowableCol(3, 1);
    gridSizer->AddGrowableCol(4, 1);

    gridSizer->AddGrowableRow(0, 1);
    gridSizer->AddGrowableRow(1, 1);
    gridSizer->AddGrowableRow(2, 1);
    gridSizer->AddGrowableRow(3, 1);
    gridSizer->AddGrowableRow(4, 1);
    gridSizer->AddGrowableRow(5, 1);


    pan->SetSizer(gridSizer);

    pan->Layout();

    SetIcon(wxIcon("troco"));
}

void Filler::updateValues(wxSpinEvent& event) {
    int id = event.GetId();
    int quant = event.GetPosition();
    double value;

    switch (id) {
    case 100:
        quant1->SetLabel("R$" + std::to_string(quant) + ",00");
        break;

    case 50:
        value = quant * 0.5;

        quant2->SetLabel("R$" + calcString(value));
        break;

    case 25:
        value = quant * 0.25;

        quant3->SetLabel("R$" + calcString(value));
        break;

    case 10:
        value = quant * 0.1;

        quant4->SetLabel("R$" + calcString(value));
        break;

    case 5:
        value = quant * 0.05;

        quant5->SetLabel("R$" + calcString(value));
        break;
    }

    value = 0;

    value += (double)one->GetValue();
    value += (double)fifty->GetValue() * 0.5;
    value += (double)tf->GetValue() * 0.25;
    value += (double)ten->GetValue() * 0.10;
    value += (double)five->GetValue() * 0.05;

    quantTotal->SetLabel("R$" + calcString(value));

    gridSizer->Layout();

    event.Skip();
}

string Filler::calcString(double value) {
    string temp = std::to_string(value);

    return temp.erase(temp.size() - 4, string::npos);
}

void Filler::fillOkPressed(wxCommandEvent& event) {
    Enable(false);

    unsigned int coins[5];

    coins[0] = five->GetValue();
    coins[1] = ten->GetValue();
    coins[2] = tf->GetValue();
    coins[3] = fifty->GetValue();
    coins[4] = one->GetValue();

    parent->fillContainer(coins);

    wxDateTime dt = wxDateTime::Now();
    string log = "Adicionado(s) " + quantTotal->GetLabel() + " ao caixa.";
    parent->addLog(log, (string)dt.FormatTime(), (string)dt.FormatDate());

    Close();
    event.Skip();
}

void Filler::depleteOkPressed(wxCommandEvent& event) {
    Enable(false);

    unsigned int coins[5];

    coins[0] = five->GetValue();
    coins[1] = ten->GetValue();
    coins[2] = tf->GetValue();
    coins[3] = fifty->GetValue();
    coins[4] = one->GetValue();

    if (parent->depleteContainer(coins))
        Close();
    else
        Enable(true);

    wxDateTime dt = wxDateTime::Now();
    string log = "Retirado(s) " + quantTotal->GetLabel() + " do caixa.";
    parent->addLog(log, (string)dt.FormatTime(), (string)dt.FormatDate());

    event.Skip();
}

void Filler::cancelPressed(wxCommandEvent& event) {
    Close();
    event.Skip();
}

void Filler::onClose(wxCloseEvent& event) {
    parent->enableAll();
    Destroy();

    event.Skip();
}

