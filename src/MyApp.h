#pragma once

#include "wx/app.h"

#include "MainFrame.h"

#ifndef MYAPP_H_
#define MYAPP_H_

class MyApp : public wxApp {
private:
    MainFrame* frame = nullptr;
    wxLocale locale;

public:
    virtual bool OnInit();
};

#endif
