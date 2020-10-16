#include "InputPanels.h"

#include <string>

#include "wx/msgdlg.h"
#include "wx/datetime.h"

BEGIN_EVENT_TABLE(InputPanels, wxPanel)

EVT_TEXT(TEXT_Price, InputPanels::updateChange)
EVT_TEXT(TEXT_Received, InputPanels::updateChange)

EVT_BUTTON(BUTTON_Calc, InputPanels::calculateChange)
EVT_BUTTON(BUTTON_Pay, InputPanels::payChange)

END_EVENT_TABLE()

InputPanels::InputPanels(wxWindow* parent) :
    wxPanel(parent, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED) {
    this->parent = dynamic_cast<MainFrame*>(parent->GetParent());

    SetBackgroundColour(wxColour(160, 160, 160));

    wxLocale loc;
    loc.Init(wxLANGUAGE_PORTUGUESE_BRAZILIAN);

    wxFloatingPointValidator<double> pVal(2, &m_p, wxNUM_VAL_THOUSANDS_SEPARATOR | wxNUM_VAL_ZERO_AS_BLANK);
    wxFloatingPointValidator<double> rVal(2, &m_r, wxNUM_VAL_THOUSANDS_SEPARATOR | wxNUM_VAL_ZERO_AS_BLANK);
    wxFloatingPointValidator<double> cVal(2, &m_c, wxNUM_VAL_THOUSANDS_SEPARATOR | wxNUM_VAL_ZERO_AS_BLANK);

    pVal.SetRange(0, 9999999);
    rVal.SetRange(0, 9999999);
    cVal.SetRange(0, 9999999);

    price = new wxTextCtrl(this, TEXT_Price, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE, pVal);;
    received = new wxTextCtrl(this, TEXT_Received, "", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE, rVal);
    change = new wxTextCtrl(this, -1, "0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE | wxTE_READONLY, cVal);
    change->SetBackgroundColour(wxColour(255, 255, 255));

    wxStaticText* changeRS = new wxStaticText(this, -1, "R$", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    changeRS->SetBackgroundColour(wxColour(255, 255, 255));
    changeRS->SetFont(wxFontInfo(26));

    price->SetFont(wxFontInfo(20));
    received->SetFont(wxFontInfo(20));
    change->SetFont(wxFontInfo(26));

    priceLabel = new wxStaticText(this, -1, "Pre\u00E7o: R$", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    receivedLabel = new wxStaticText(this, -1, "Recebido: R$", wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    changeLabel = new wxStaticText(this, -1, "Troco", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);

    priceLabel->SetFont(wxFontInfo(20));
    priceLabel->SetBackgroundColour(wxColour(235, 235, 235));
    receivedLabel->SetFont(wxFontInfo(20));
    receivedLabel->SetBackgroundColour(wxColour(235, 235, 235));
    changeLabel->SetFont(wxFontInfo(26));
    changeLabel->SetBackgroundColour(wxColour(15, 15, 15));
    changeLabel->SetForegroundColour(wxColour(245, 245, 245));

    wxBoxSizer* priceSiz = new wxBoxSizer(wxHORIZONTAL);
    priceSiz->Add(priceLabel, wxSizerFlags(0).Expand());
    priceSiz->Add(price, wxSizerFlags(1));

    wxBoxSizer* receivedSiz = new wxBoxSizer(wxHORIZONTAL);
    receivedSiz->Add(receivedLabel, wxSizerFlags(1).Expand());
    receivedSiz->Add(received, wxSizerFlags(1));

    wxBoxSizer* changeSiz = new wxBoxSizer(wxHORIZONTAL);
    changeSiz->Add(changeRS, wxSizerFlags(0).Expand());
    changeSiz->Add(change, wxSizerFlags(1));

    wxBoxSizer* leftVer = new wxBoxSizer(wxVERTICAL);
    leftVer->Add(priceSiz, wxSizerFlags(0).Expand().Border(wxALL, 5));
    leftVer->Add(receivedSiz, wxSizerFlags(0).Expand().Border(wxALL, 5));
    leftVer->AddStretchSpacer(1);
    leftVer->Add(changeLabel, wxSizerFlags(0).CenterHorizontal());
    leftVer->Add(changeSiz, wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT | wxBOTTOM, 5));

    wxPanel* rightPan = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    rightPan->SetBackgroundColour(wxColour(245, 245, 245));

    calc = new wxButton(rightPan, BUTTON_Calc, "Calcular", wxDefaultPosition, wxSize(200, 40));
    pay = new wxButton(rightPan, BUTTON_Pay, "Pagar", wxDefaultPosition, wxSize(200, 40));

    pay->Enable(false);

    quant1 = new wxStaticText(rightPan, -1, "0 x R$0,05", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    quant2 = new wxStaticText(rightPan, -1, "0 x R$0,10", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    quant3 = new wxStaticText(rightPan, -1, "0 x R$0,25", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    quant4 = new wxStaticText(rightPan, -1, "0 x R$0,50", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    quant5 = new wxStaticText(rightPan, -1, "0 x R$1,00", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);

    quant1->SetBackgroundColour(wxColour(164, 103, 45));
    quant2->SetBackgroundColour(wxColour(230, 180, 0));
    quant3->SetBackgroundColour(wxColour(220, 170, 0));
    quant4->SetBackgroundColour(wxColour(200, 200, 200));
    quant5->SetBackgroundColour(wxColour(240, 205, 0));

    quant1->SetFont(wxFontInfo(19).Bold());
    quant2->SetFont(wxFontInfo(19).Bold());
    quant3->SetFont(wxFontInfo(19).Bold());
    quant4->SetFont(wxFontInfo(19).Bold());
    quant5->SetFont(wxFontInfo(19).Bold());

    wxBoxSizer* coinsSizer = new wxBoxSizer(wxHORIZONTAL);
    coinsSizer->Add(quant1, wxSizerFlags(1).Border(wxRIGHT, 10));
    coinsSizer->Add(quant2, wxSizerFlags(1).Border(wxRIGHT, 10));
    coinsSizer->Add(quant3, wxSizerFlags(1).Border(wxRIGHT, 10));
    coinsSizer->Add(quant4, wxSizerFlags(1).Border(wxRIGHT, 10));
    coinsSizer->Add(quant5, wxSizerFlags(1));

    wxStaticText* label = new wxStaticText(rightPan, -1, "C\u00E1lculo do troco", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    label->SetFont(wxFontInfo(20).Bold());
    label->SetBackgroundColour(wxColour(30, 30, 30));
    label->SetForegroundColour(wxColour(255, 255, 255));

    wxBoxSizer* rightHor = new wxBoxSizer(wxHORIZONTAL);
    rightHor->Add(calc, wxSizerFlags(0).Expand());
    rightHor->AddStretchSpacer(1);
    rightHor->Add(label, wxSizerFlags(0).Expand());

    wxBoxSizer* rightVer = new wxBoxSizer(wxVERTICAL);
    rightVer->Add(rightHor, wxSizerFlags(0).Expand().Border(wxALL, 5));
    rightVer->AddStretchSpacer(1);
    rightVer->Add(coinsSizer, wxSizerFlags(1).Border(wxALL, 5));
    rightVer->AddStretchSpacer(1);
    rightVer->Add(pay, wxSizerFlags(0).Right().Border(wxALL, 5));

    rightPan->SetSizer(rightVer);

    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(leftVer, wxSizerFlags(0).Expand());
    mainSizer->Add(rightPan, wxSizerFlags(0).Expand());

    SetSizer(mainSizer);
}

void InputPanels::updateChange(wxCommandEvent& event) {
    price->GetValidator()->TransferFromWindow();
    received->GetValidator()->TransferFromWindow();

    m_c = m_r - m_p;

    if (m_c < 0) {
        change->SetValue("-/-");
        m_c = 0;
    } else if (m_c == 0)
        change->SetValue("0,00");
    else 
        change->GetValidator()->TransferToWindow();

    if (!isDefault)
        setDefault();

    event.Skip();
}

void InputPanels::calculateChange(wxCommandEvent& event) {

    if (m_c <= 0) {
        setDefault();
    } else {
        setDefault();

        vector<int> coins = parent->getCoins();

        //Transofrmando os valores de double para int para evitar as aleatoriedades
        //que podem surgir com doubles pelos valores após 16 casas decimais
        int c = (int)(m_c * 100 + 0.5);

        while (c >= 98) {
            if (changeCoins[0] == coins[0]) {
                break;
            }

            changeCoins[0]++;
            c -= 100;
        }

        while (c >= 48) {
            if (changeCoins[1] == coins[1])
                break;

            changeCoins[1]++;
            c -= 50;
        }

        while (c >= 23) {
            if (changeCoins[2] == coins[2])
                break;

            changeCoins[2]++;
            c -= 25;
        }

        while (c >= 8) {
            if (changeCoins[3] == coins[3])
                break;

            changeCoins[3]++;
            c -= 10;
        }

        while (c >= 4) {
            if (changeCoins[4] == coins[4])
                break;

            changeCoins[4]++;
            c -= 5;
        }


        if (c >= 3) {
            if (coins[0] - changeCoins[0] > 0 || coins[1] - changeCoins[1] > 0 ||
                coins[2] - changeCoins[2] > 0 || coins[3] - changeCoins[3] > 0 ||
                coins[4] - changeCoins[4] > 0) {

                c += (changeCoins[4] * 5);
                changeCoins[4] = 0;

                for (int i = 0; i < coins[3] - changeCoins[3]; i++) {
                    if (c <= 3)
                        break;

                    changeCoins[3]++;
                    c -= 10;
                }

                for (int i = 0; i < coins[2] - changeCoins[2]; i++) {
                    if (c <= 3)
                        break;

                    changeCoins[2]++;
                    c -= 25;
                }

                for (int i = 0; i < coins[1] - changeCoins[1]; i++) {
                    if (c <= 3)
                        break;

                    changeCoins[1]++;
                    c -= 50;
                }

                for (int i = 0; i < coins[0] - changeCoins[0]; i++) {
                    if (c <= 3)
                        break;

                    changeCoins[0]++;
                    c -= 100;
                }

                for (int i = 0; i < coins[4] - changeCoins[4]; i++) {
                    if (c <= 3)
                        break;

                    changeCoins[4]++;
                    c -= 5;
                }
            } else {
                wxMessageDialog* message = new wxMessageDialog(this,
                    "Favor abastecer o caixa.\n\nVoc\u00EA n\u00E3o possui dinheiro o suficiente para pagar o troco requisitado.", "Faltam moedas");
                message->ShowModal();
                delete message;

                return;
            }
        }

        if (c < 0 && c >= -4) {
            string over = std::to_string((double)-c / 100);
            over.erase(over.size() - 4, string::npos);
            wxMessageDialog* message = new wxMessageDialog(this,
                "Aten\u00E7\u00E3o\n\nSe voc\u00EA pagar esse troco, devolver\u00E1 R$" + over +
                " a mais do que o necess\u00E1rio.",
                "Devolu\u00E7\u00E3o extra");
            message->ShowModal();
            delete message;

        } else if (c < -4) {
            wxMessageDialog* message = new wxMessageDialog(this,
                "Favor abastecer o caixa\n\nN\u00E3o \u00E9 poss\u00EDvel pagar o troco com as moedas atuais sem perder dinheiro.",
                " ");
            message->ShowModal();
            delete message;

            setDefault();

        }

        if (changeCoins[0] > 0 || changeCoins[1] > 0 || changeCoins[2] > 0 ||
            changeCoins[3] > 0 || changeCoins[4] > 0) {
            quant1->SetLabel(std::to_string(changeCoins[4]) + " x R$0.05");
            quant2->SetLabel(std::to_string(changeCoins[3]) + " x R$0.10");
            quant3->SetLabel(std::to_string(changeCoins[2]) + " x R$0.25");
            quant4->SetLabel(std::to_string(changeCoins[1]) + " x R$0.50");
            quant5->SetLabel(std::to_string(changeCoins[0]) + " x R$1.00");

            isDefault = false;
            pay->Enable(true);
        }
    }

    event.Skip();
}

void InputPanels::payChange(wxCommandEvent& event) {
    unsigned int coins[5];

    coins[0] = changeCoins[4];
    coins[1] = changeCoins[3];
    coins[2] = changeCoins[2];
    coins[3] = changeCoins[1];
    coins[4] = changeCoins[0];

    parent->subtractChange(coins);

    string changeString = std::to_string(m_c);
    changeString.erase(changeString.size() - 4, string::npos);

    wxDateTime dt = wxDateTime::Now();

    string log = "Pago troco de R$" + changeString + ".";
    parent->addLog(log, (string)dt.FormatTime(), (string)dt.FormatDate());

    setDefault();

    price->Clear();
    received->Clear();
    change->SetValue("0,00");

    event.Skip();
}

void InputPanels::setDefault() {
    quant1->SetLabel("0 x R$0,05");
    quant2->SetLabel("0 x R$0,10");
    quant3->SetLabel("0 x R$0,25");
    quant4->SetLabel("0 x R$0,50");
    quant5->SetLabel("0 x R$1,00");

    for (int i = 0; i < 5; i++)
        changeCoins[i] = 0;

    isDefault = true;
    pay->Enable(false);
}
