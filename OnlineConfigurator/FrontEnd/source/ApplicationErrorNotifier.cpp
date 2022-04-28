#include "ApplicationErrorNotifier.h"

#include <Wt/WMessageBox.h>
#include <Wt/WApplication.h>

using namespace Wt;

void ApplicationErrorNotifier::notify(const std::string& errorMessage)
{
    WMessageBox::show(u8"Ошибка", errorMessage, StandardButton::Ok);
    WApplication::instance()->quit("");
}
