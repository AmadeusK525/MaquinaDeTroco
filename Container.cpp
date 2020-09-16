#include "Container.h"

#include "wx/gbsizer.h"
#include "wx/dcclient.h"
#include "wx/msgdlg.h"

#include "Filler.h"

BEGIN_EVENT_TABLE(Container, wxPanel)

EVT_BUTTON(BUTTON_Fill, Container::fillContainer)
EVT_BUTTON(BUTTON_Deplete, Container::depleteContainer)

END_EVENT_TABLE()

Container::Container(wxWindow* parent) : wxPanel(parent, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN) {
    top = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    top->SetBackgroundColour(wxColour(150, 150, 150));

    SetBackgroundColour(wxColour(230, 230, 230));

    this->parent = dynamic_cast<MainFrame*>(parent->GetParent());

    fivePanel = new wxStaticText(top, -1, "0", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    tenPanel = new wxStaticText(top, -1, "0", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    twentyFivePanel = new wxStaticText(top, -1, "0", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    fiftyPanel = new wxStaticText(top, -1, "0", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    onePanel = new wxStaticText(top, -1, "0", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);

    wxStaticText* fpLabel = new wxStaticText(top, -1, "R$0,05", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    wxStaticText* tpLabel = new wxStaticText(top, -1, "R$0,10", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    wxStaticText* tfpLabel = new wxStaticText(top, -1, "R$0,25", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    wxStaticText* fiftyPLabel = new wxStaticText(top, -1, "R$0,50", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    wxStaticText* opLabel = new wxStaticText(top, -1, "R$1,00", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);

    fivePanel->SetFont(wxFontInfo(50).Bold());
    fivePanel->SetBackgroundColour(wxColour(230, 230, 230));
    fpLabel->SetFont(wxFontInfo(20).Bold());
    fpLabel->SetBackgroundColour(wxColour(164, 103, 45));

    tenPanel->SetFont(wxFontInfo(50).Bold());
    tenPanel->SetBackgroundColour(wxColour(230, 230, 230));
    tpLabel->SetFont(wxFontInfo(20).Bold());
    tpLabel->SetBackgroundColour(wxColour(230, 180, 0));

    twentyFivePanel->SetFont(wxFontInfo(50).Bold());
    twentyFivePanel->SetBackgroundColour(wxColour(230, 230, 230));
    tfpLabel->SetFont(wxFontInfo(20).Bold());
    tfpLabel->SetBackgroundColour(wxColour(220, 170, 0));

    fiftyPanel->SetFont(wxFontInfo(50).Bold());
    fiftyPanel->SetBackgroundColour(wxColour(230, 230, 230));
    fiftyPLabel->SetFont(wxFontInfo(20).Bold());
    fiftyPLabel->SetBackgroundColour(wxColour(200, 200, 200));

    onePanel->SetFont(wxFontInfo(50).Bold());
    onePanel->SetBackgroundColour(wxColour(230, 230, 230));
    opLabel->SetFont(wxFontInfo(20).Bold());
    opLabel->SetBackgroundColour(wxColour(240, 205, 0));

    fiveCount = new wxStaticText(top, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    tenCount = new wxStaticText(top, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    twentyFiveCount = new wxStaticText(top, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    fiftyCount = new wxStaticText(top, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    oneCount = new wxStaticText(top, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);

    fiveCount->SetFont(wxFontInfo(18));
    tenCount->SetFont(wxFontInfo(18));
    twentyFiveCount->SetFont(wxFontInfo(18));
    fiftyCount->SetFont(wxFontInfo(18));
    oneCount->SetFont(wxFontInfo(18));

    fiveCount->SetBackgroundColour(wxColour(255, 255, 255));
    tenCount->SetBackgroundColour(wxColour(255, 255, 255));
    twentyFiveCount->SetBackgroundColour(wxColour(255, 255, 255));
    fiftyCount->SetBackgroundColour(wxColour(255, 255, 255));
    oneCount->SetBackgroundColour(wxColour(255, 255, 255));

    wxGridBagSizer* gridSizer = new wxGridBagSizer(0, 10);

    gridSizer->Add(fpLabel, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND | wxLEFT | wxTOP, 3);
    gridSizer->Add(tpLabel, wxGBPosition(0, 1), wxDefaultSpan, wxEXPAND | wxTOP, 3);
    gridSizer->Add(tfpLabel, wxGBPosition(0, 2), wxDefaultSpan, wxEXPAND | wxTOP, 3);
    gridSizer->Add(fiftyPLabel, wxGBPosition(0, 3), wxDefaultSpan, wxEXPAND | wxTOP, 3);
    gridSizer->Add(opLabel, wxGBPosition(0, 4), wxDefaultSpan, wxEXPAND | wxRIGHT | wxTOP, 3);

    gridSizer->Add(fivePanel, wxGBPosition(1, 0), wxDefaultSpan, wxEXPAND | wxLEFT | wxBOTTOM, 3);
    gridSizer->Add(tenPanel, wxGBPosition(1, 1), wxDefaultSpan, wxEXPAND | wxBOTTOM, 3);
    gridSizer->Add(twentyFivePanel, wxGBPosition(1, 2), wxDefaultSpan, wxEXPAND | wxBOTTOM, 3);
    gridSizer->Add(fiftyPanel, wxGBPosition(1, 3), wxDefaultSpan, wxEXPAND | wxBOTTOM, 3);
    gridSizer->Add(onePanel, wxGBPosition(1, 4), wxDefaultSpan, wxEXPAND | wxRIGHT | wxBOTTOM, 3);

    gridSizer->Add(fiveCount, wxGBPosition(2, 0), wxDefaultSpan, wxEXPAND | wxLEFT | wxBOTTOM, 3);
    gridSizer->Add(tenCount, wxGBPosition(2, 1), wxDefaultSpan, wxEXPAND | wxBOTTOM, 3);
    gridSizer->Add(twentyFiveCount, wxGBPosition(2, 2), wxDefaultSpan, wxEXPAND | wxBOTTOM, 3);
    gridSizer->Add(fiftyCount, wxGBPosition(2, 3), wxDefaultSpan, wxEXPAND | wxBOTTOM, 3);
    gridSizer->Add(oneCount, wxGBPosition(2, 4), wxDefaultSpan, wxEXPAND | wxRIGHT | wxBOTTOM, 3);

    gridSizer->AddGrowableCol(0, 1);
    gridSizer->AddGrowableCol(1, 1);
    gridSizer->AddGrowableCol(2, 1);
    gridSizer->AddGrowableCol(3, 1);
    gridSizer->AddGrowableCol(4, 1);

    gridSizer->AddGrowableRow(1, 1);

    top->SetSizer(gridSizer);

    fill = new wxButton(this, BUTTON_Fill, "Abastecimento");
    deplete = new wxButton(this, BUTTON_Deplete, "Sangria");

    fill->SetBackgroundColour(wxColour(250, 250, 250));
    deplete->SetBackgroundColour(wxColour(250, 250, 250));

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(fill, wxSizerFlags(1).Expand());
    btnSizer->AddStretchSpacer(2);
    btnSizer->Add(deplete, wxSizerFlags(1).Expand());

    wxStaticText* contents = new wxStaticText(this, -1, "Moedas no caixa", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    contents->SetFont(wxFontInfo(20).Bold());
    contents->SetBackgroundColour(wxColour(30, 30, 30));
    contents->SetForegroundColour(wxColour(255, 255, 255));

    ver = new wxBoxSizer(wxVERTICAL);
    ver->Add(contents, wxSizerFlags(0).Left().Border(wxLEFT | wxTOP, 5));
    ver->Add(btnSizer, wxSizerFlags(1).Expand().Border(wxALL, 5));
    ver->Add(top, wxSizerFlags(4).Expand());

    SetSizer(ver);
}

double Container::getCount() {
    double count = 0;

    count += one * 1;
    count += (double)fifty * 0.5;
    count += (double)twentyFive * 0.25;
    count += (double)ten * 0.1;
    count += (double)five * 0.05;

    count = (int)((count * 100) + 0.7);

    return (double)count / 100.0;
}

vector<int> Container::getCoins() {
    vector<int> coins;

    coins.push_back(one);
    coins.push_back(fifty);
    coins.push_back(twentyFive);
    coins.push_back(ten);
    coins.push_back(five);

    return coins;
}

void Container::updateValues() {
    fivePanel->SetLabel(std::to_string(five));
    tenPanel->SetLabel(std::to_string(ten));
    twentyFivePanel->SetLabel(std::to_string(twentyFive));
    fiftyPanel->SetLabel(std::to_string(fifty));
    onePanel->SetLabel(std::to_string(one));

    string countS;

    countS = std::to_string((double)five * 0.05);
    countS.erase(countS.size() - 4, string::npos);
    fiveCount->SetLabel("R$" + countS);

    countS = std::to_string((double)ten * 0.10);
    countS.erase(countS.size() - 4, string::npos);
    tenCount->SetLabel("R$" + countS);

    countS = std::to_string((double)twentyFive * 0.25);
    countS.erase(countS.size() - 4, string::npos);
    twentyFiveCount->SetLabel("R$" + countS);

    countS = std::to_string((double)fifty * 0.50);
    countS.erase(countS.size() - 4, string::npos);
    fiftyCount->SetLabel("R$" + countS);

    countS = std::to_string((double)one);
    countS.erase(countS.size() - 4, string::npos);
    oneCount->SetLabel("R$" + countS);
}

void Container::doFillContainer(unsigned int coins[5], bool showDialog) {
    parent->setDefaultChange();

    five += coins[0];
    ten += coins[1];
    twentyFive += coins[2];
    fifty += coins[3];
    one += coins[4];

    double cur = getCount();
    string curString = std::to_string(cur);
    curString.erase(curString.size() - 4, string::npos);
    parent->updateCurrent(curString);

    updateValues();

    parent->setDefaultChange();
    ver->Layout();

    wxMessageDialog* message = new wxMessageDialog(this,
        "Foram adicionadas:\n\n" +
        std::to_string(coins[0]) + " moeda(s) de R$0,05\n" +
        std::to_string(coins[1]) + " moeda(s) de R$0,10\n" +
        std::to_string(coins[2]) + " moeda(s) de R$0,25\n" +
        std::to_string(coins[3]) + " moeda(s) de R$0,50\n" +
        std::to_string(coins[4]) + " moeda(s) de R$1,00", "Moedas adicionadas", wxOK | wxOK_DEFAULT | wxICON_INFORMATION);


    if (showDialog)
        message->ShowModal();

    delete message;
}

bool Container::doDepleteContainer(unsigned int coins[5], string title) {
    wxMessageDialog* message = new wxMessageDialog(this,
        "Foram retiradas:\n\n" +
        std::to_string(coins[0]) + " moeda(s) de R$0,05\n" +
        std::to_string(coins[1]) + " moeda(s) de R$0,10\n" +
        std::to_string(coins[2]) + " moeda(s) de R$0,25\n" +
        std::to_string(coins[3]) + " moeda(s) de R$0,50\n" +
        std::to_string(coins[4]) + " moeda(s) de R$1,00", title, wxOK | wxOK_DEFAULT | wxICON_INFORMATION);

    string missing("Voc\u00EA est\u00E1 tentando retirar mais moedas do que o poss\u00EDvel em:\n");
    bool canDo = true;

    if (coins[0] > five) {
        missing += ("\n" + std::to_string(coins[0] - five) + " moeda(s) de R$0.05");
        canDo = false;
    }

    if (coins[1] > ten) {
        missing += ("\n" + std::to_string(coins[1] - ten) + " moeda(s) de R$0.10");
        canDo = false;
    }

    if (coins[2] > twentyFive) {
        missing += ("\n" + std::to_string(coins[2] - twentyFive) + " moeda(s) de R$0.25");
        canDo = false;
    }

    if (coins[3] > fifty) {
        missing += ("\n" + std::to_string(coins[3] - fifty) + " moeda(s) de R$0.50");
        canDo = false;
    }

    if (coins[4] > one) {
        missing += ("\n" + std::to_string(coins[4] - one) + " moeda(s) de R$1.00");
        canDo = false;
    }

    if (canDo) {
        five -= coins[0];
        ten -= coins[1];
        twentyFive -= coins[2];
        fifty -= coins[3];
        one -= coins[4];

        updateValues();

        float cur = getCount();
        string curString = std::to_string(cur);
        curString.erase(curString.size() - 4, string::npos);
        parent->updateCurrent(curString);

        parent->setDefaultChange();
        ver->Layout();

        message->ShowModal();
        delete message;

        return true;
    }

    message->SetMessage(missing);
    message->SetName("N\u00E3o h\u00E1 moedas suficientes");

    message->ShowModal();
    delete message;

    return false;
}

void Container::fillContainer(wxCommandEvent& event) {
    Filler* filler = new Filler(parent, "Abastecer caixa", true);
    filler->CenterOnScreen();
    filler->Show();

    parent->disableAll();

    event.Skip();
}

void Container::depleteContainer(wxCommandEvent& event) {
    Filler* filler = new Filler(parent, "Retirar moedas", false);
    filler->CenterOnScreen();
    filler->Show();

    parent->disableAll();

    event.Skip();
}

void Container::disableBtns() {
    fill->Enable(false);
    deplete->Enable(false);
}

void Container::enableBtns() {
    fill->Enable(true);
    deplete->Enable(true);
}
