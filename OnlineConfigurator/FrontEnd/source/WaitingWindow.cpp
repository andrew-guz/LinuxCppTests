#include "WaitingWindow.h"

#include <chrono>

#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WProgressBar.h>

using namespace Wt;

void WaitingWindow::show(const std::string& text)
{
    _dialog = WApplication::instance()->root()->addChild(std::make_unique<WDialog>(u8"Подождите пожалуйста"));
    if (text.size())
    {
        _dialog->contents()->addWidget(std::make_unique<WText>(text));
        _dialog->contents()->addWidget(std::make_unique<WBreak>());
    }
    auto progressBar = _dialog->contents()->addWidget(std::make_unique<WProgressBar>());
    progressBar->setFormat("");
    progressBar->setRange(0.0, 10.0);
    progressBar->setValue(0.0);

    _timer = _dialog->contents()->addChild(std::make_unique<WTimer>());
    _timer->setInterval(std::chrono::milliseconds(100));
    _timer->timeout().connect([=](){
        if (progressBar->value() >= progressBar->maximum())
            progressBar->setValue(progressBar->minimum());
        else
            progressBar->setValue(progressBar->value() + 1.0);
    });
    _timer->start();

    _dialog->show();
}

void WaitingWindow::close()
{
    _timer->stop();
    _timer = nullptr;
    WApplication::instance()->removeChild(_dialog);
    _dialog = nullptr;
}
