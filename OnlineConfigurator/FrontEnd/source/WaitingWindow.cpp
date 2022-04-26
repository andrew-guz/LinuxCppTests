#include "WaitingWindow.h"

#include <chrono>

#include <Wt/WApplication.h>
#include <Wt/WDialog.h>
#include <Wt/WText.h>
#include <Wt/WProgressBar.h>
#include <Wt/WTimer.h>

using namespace Wt;

void WaitingWindow::wait()
{
    auto application = WApplication::instance();

    auto dialog = application->root()->addChild(std::make_unique<WDialog>(u8"Подождите пожалуйста"));
    auto progressBar = dialog->contents()->addWidget(std::make_unique<WProgressBar>());
    progressBar->setFormat("");
    progressBar->setRange(0.0, 10.0);
    progressBar->setValue(0.0);

    auto intervalTimer = dialog->contents()->addChild(std::make_unique<WTimer>());
    intervalTimer->setInterval(std::chrono::milliseconds(100));
    intervalTimer->timeout().connect([=](){
        if (progressBar->value() >= progressBar->maximum())
            progressBar->setValue(progressBar->minimum());
        else
            progressBar->setValue(progressBar->value() + 1.0);
    });
    intervalTimer->start();

    dialog->show();
}
