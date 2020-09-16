#include "MainFrame.h"

#include "wx/dirdlg.h"
#include "wx/msgdlg.h"
#include "wx/menu.h"

#include "Container.h"
#include "InputPanels.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)

EVT_CLOSE(MainFrame::onClose)
EVT_MENU(MENU_Save, MainFrame::save)
EVT_MENU(MENU_SaveAs, MainFrame::saveAs)
EVT_MENU(MENU_Open, MainFrame::open)

END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent, const string& title, const wxPoint& pos, const wxSize& size) :
    wxFrame(parent, -1, title, pos, size) {

    mainPanel = new wxPanel(this);
    mainPanel->SetBackgroundColour(wxColour(250, 250, 250));

    values = new InputPanels(mainPanel);

    current = new wxStaticText(mainPanel, -1, "R$0,00", wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED);
    current->SetForegroundColour(wxColour(255, 255, 255));
    current->SetBackgroundColour(wxColour(40, 40, 40));
    current->SetFont(wxFont(wxFontInfo(40)));

    container = new Container(mainPanel);

    log = new wxListView(mainPanel, -1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_HRULES | wxBORDER_RAISED);
    log->InsertColumn(0, "Log", wxLIST_FORMAT_LEFT, 250);
    log->InsertColumn(1, "Hor\u00E1rio");
    log->InsertColumn(2, "Data");

    wxBoxSizer* siz = new wxBoxSizer(wxHORIZONTAL);
    siz->Add(values, wxSizerFlags(0));
    siz->AddStretchSpacer(2);
    siz->Add(current, wxSizerFlags(0));

    wxBoxSizer* siz2 = new wxBoxSizer(wxHORIZONTAL);
    siz2->Add(log, wxSizerFlags(2).Expand().Border(wxRIGHT, 10));
    siz2->Add(container, wxSizerFlags(3).Expand());

    ver = new wxBoxSizer(wxVERTICAL);
    ver->Add(siz, wxSizerFlags(0).Expand());
    ver->AddStretchSpacer(1);
    ver->Add(siz2, wxSizerFlags(3).Expand());

    mainPanel->SetSizer(ver);

    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();

    fileMenu->Append(MENU_Save, "Salvar", "");
    fileMenu->Append(MENU_SaveAs, "Salvar como...");
    fileMenu->Append(MENU_Open, "Abrir");

    menuBar->Append(fileMenu, "Arquivo");

    SetMenuBar(menuBar);
    SetIcon(wxIcon("troco"));
    Maximize();

    getLast();
}

void MainFrame::updateCurrent(string cur) {
    current->SetLabel("R$" + cur);
    ver->Layout();
}

vector<int> MainFrame::getCoins() {
    return container->getCoins();
}

void MainFrame::fillContainer(unsigned int coins[5]) {
    container->doFillContainer(coins);
}

bool MainFrame::depleteContainer(unsigned int coins[5]) {
    return container->doDepleteContainer(coins);
}

void MainFrame::setDefaultChange() {
    values->setDefault();
}

void MainFrame::subtractChange(unsigned int changeCoins[5]) {
    container->doDepleteContainer(changeCoins, "Pagamento realizado");
}

void MainFrame::disableAll() {
    container->disableBtns();
    values->Enable(false);
}

void MainFrame::enableAll() {
    container->enableBtns();
    values->Enable(true);
}

void MainFrame::addLog(string ocur, string time, string date) {
    log->InsertItem(curLog, ocur);
    log->SetItem(curLog, 1, time);
    log->SetItem(curLog++, 2, date);
}

void MainFrame::save(wxCommandEvent& event) {
    if (currentPath == "") {
        saveAs(event);
    } else {
        vector<int> coins = container->getCoins();

        std::ofstream valueFile;
        valueFile.open(currentPath + "\\Troco.bin", std::ios::binary);

        if (valueFile.is_open()) {
            for (int i = 4; i > -1; i--)
                valueFile.write((char*)&coins[i], sizeof(unsigned int));

            valueFile.close();
        }

        std::ofstream logFile;
        logFile.open(currentPath + "\\Log.txt");

        if (logFile.is_open()) {
            for (int i = 0; i < log->GetItemCount(); i++) {
                string logString = log->GetItemText(i, 0);
                string timeString = log->GetItemText(i, 1);
                string dateString = log->GetItemText(i, 2);

                logFile << logString << "-" << timeString << "-" << dateString << std::endl;
            }

            logFile.close();
        }

        setLast();
        isSaved = true;
    }
}

void MainFrame::saveAs(wxCommandEvent& event) {
    wxDirDialog* choose = new wxDirDialog(this, "Escolha um local para salvar as informa\u00E7\u00F5es do programa");

    if (choose->ShowModal() == wxID_OK) {
        currentPath = choose->GetPath();
        save(event);
    }

    delete choose;

    event.Skip();
}

void MainFrame::open(wxCommandEvent& event) {
    wxDirDialog* open = new wxDirDialog(this, "Escolha a pasta para abrir");

    if (open->ShowModal() == wxID_OK) {
        currentPath = open->GetPath();
        load();
    }

    delete open;

    event.Skip();
}

void MainFrame::load() {
    isSaved = true;

    std::ifstream valuesFile;
    valuesFile.open(currentPath + "\\Troco.bin", std::ios::binary);

    if (valuesFile.is_open()) {
        unsigned int coins[5];

        for (int i = 0; i < 5; i++)
            valuesFile.read((char*)&coins[i], sizeof(unsigned int));

        container->doFillContainer(coins, false);
        valuesFile.close();
    } else {
        isSaved = false;
    }

    std::ifstream logFile;
    logFile.open(currentPath + "\\Log.txt");

    if (logFile.is_open()) {
        string logString;
        string timeString;
        string dateString;

        while (!logFile.eof()) {
            std::getline(logFile, logString, '-');
            std::getline(logFile, timeString, '-');
            std::getline(logFile, dateString);
            logFile >> std::ws;

            log->InsertItem(curLog, logString);
            log->SetItem(curLog, 1, timeString);
            log->SetItem(curLog++, 2, dateString);
        }
    } else {
        isSaved = false;
        currentPath = "";
    }
}

void MainFrame::setLast() {
    std::ofstream out;
    out.open("LocalTroco.txt");

    if (out.is_open()) {
        out << currentPath + "-";

        out.close();
    }
}

void MainFrame::getLast() {
    std::ifstream in;
    in.open("LocalTroco.txt");

    if (in.is_open()) {
        std::getline(in, currentPath, '-');
        in.close();
    }

    if (currentPath != "")
        load();
}

void MainFrame::onClose(wxCloseEvent& event) {
    if (currentPath == "") {
        wxMessageDialog* saveBefore = new wxMessageDialog(this,
            "Voc\u00EA ainda n\u00E3o salvou o programa nenhuma vez. Se n\u00E3o salvar antes de sair, perder\u00E1 todo o progresso. Deseja salvar antes de sair?",
            "Salve antes de fechar", wxYES_NO | wxCANCEL | wxYES_DEFAULT | wxICON_WARNING);

        switch (saveBefore->ShowModal()) {
        case wxID_YES:
            saveAs(wxCommandEvent());
            delete saveBefore;

            if (!isSaved)
                return;

            break;

        case wxID_NO:
            delete saveBefore;
            break;

        case wxID_CANCEL:
            delete saveBefore;
            return;
            break;
        }

        Destroy();

    } else {
        save(wxCommandEvent());
        Destroy();
    }

    event.Skip();
}
