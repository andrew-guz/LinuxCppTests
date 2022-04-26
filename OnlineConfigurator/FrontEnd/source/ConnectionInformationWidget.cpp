#include "ConnectionInformationWidget.h"

#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include "WaitingWindow.h"

using namespace Wt;

ConnectionInformationWidget::ConnectionInformationWidget() :
    WGroupBox()
{
    setTitle(u8"Доступ к контроллеру:");

    resize(500, 200);

    _gridLayout = (WGridLayout*)setLayout(std::make_unique<WGridLayout>());

    _gridLayout->addWidget(std::make_unique<WText>(u8"Основной адрес:"), 0, 0);
    _mainAddress = _gridLayout->addWidget(std::make_unique<WLineEdit>(), 0, 1);
    _gridLayout->addWidget(std::make_unique<WText>(u8"Дополнительный адрес:"), 1, 0);
    _additionalAddress = _gridLayout->addWidget(std::make_unique<WLineEdit>(), 1, 1);
    _gridLayout->addWidget(std::make_unique<WText>(u8"Пароль:"), 2, 0);
    _password = _gridLayout->addWidget(std::make_unique<WLineEdit>(), 2, 1);
    _password->setEchoMode(EchoMode::Password);
}

ConnectionInformationWidget::~ConnectionInformationWidget()
{

}
