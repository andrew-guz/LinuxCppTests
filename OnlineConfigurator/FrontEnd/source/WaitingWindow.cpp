#include "WaitingWindow.h"

#include <Wt/WPushButton.h>

using namespace Wt;

WaitingWindow::WaitingWindow() :
    WObject()
{
    
}

void WaitingWindow::wait()
{
    _dialog = addChild<WDialog>(std::make_unique<WDialog>(u8"Подождите пожалуйста"));
    auto ok = _dialog->contents()->addWidget<WPushButton>(std::make_unique<WPushButton>("Ok"));
    ok->clicked().connect(_dialog, &WDialog::accept);
    _dialog->finished().connect(this, &WaitingWindow::dialogClosed);
    _dialog->show();    
}

void WaitingWindow::dialogClosed(Wt::DialogCode result)
{
    removeChild(_dialog);
    _dialog = nullptr;
}