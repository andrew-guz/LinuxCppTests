#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WText.h>

using namespace Wt;

class HelloApplication : public WApplication
{
public:
    HelloApplication(const WEnvironment& env) :
        WApplication(env)
    {
        auto buttons = root()->addWidget(std::make_unique<WContainerWidget>());

        auto button = buttons->addWidget(std::make_unique<WPushButton>("Familiar"));
        button->clicked().connect(this, &HelloApplication::custom);
    }

    void custom()
    {
        /*WDialog dialog("Personalia");
        dialog.setClosable(true);
        dialog.setResizable(true);
        dialog.rejectWhenEscapePressed(true);

        dialog.contents()->addWidget(std::make_unique<WText>("Enter your name: "));
        WLineEdit *edit = dialog.contents()->addWidget(std::make_unique<WLineEdit>());
        WPushButton *ok = dialog.footer()->addWidget(std::make_unique<WPushButton>("Ok"));
        ok->setDefault(true);

        edit->setFocus();
        ok->clicked().connect(&dialog, &WDialog::accept);

        dialog.exec();*/

        auto dialog = root()->addChild(std::make_unique<WDialog>("Personalia"));
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
};

int main(int argc, char **argv)
{
    return WRun(argc, argv, [](const WEnvironment& env) {
      return std::make_unique<HelloApplication>(env);
    });
}