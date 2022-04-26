#include "WaitingWindow.h"

#include <Wt/WApplication.h>
#include <Wt/WDialog.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>

using namespace Wt;

void WaitingWindow::wait()
{
    auto application = WApplication::instance();

    auto dialog = application->root()->addChild(std::make_unique<WDialog>(u8"Подождите пожалуйста"));
    dialog->setClosable(true);
    dialog->setResizable(true);
    dialog->rejectWhenEscapePressed(true);

    dialog->contents()->addWidget(std::make_unique<WText>("Enter your name: "));
    WLineEdit *edit = dialog->contents()->addWidget(std::make_unique<WLineEdit>());
    WPushButton *ok = dialog->footer()->addWidget(std::make_unique<WPushButton>("Ok"));
    ok->setDefault(true);

    edit->setFocus();
    ok->clicked().connect(dialog, &WDialog::accept); 

    dialog->show();   
}
