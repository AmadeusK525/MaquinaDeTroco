#include "MyApp.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    locale.Init(wxLANGUAGE_PORTUGUESE_BRAZILIAN);
    wxInitAllImageHandlers();

    frame = new MainFrame(nullptr, "M\u00E1quina de troco");
    frame->Show();

    return true;
}
