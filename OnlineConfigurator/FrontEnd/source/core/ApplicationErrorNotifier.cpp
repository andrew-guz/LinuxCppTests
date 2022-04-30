#include "ApplicationErrorNotifier.h"

#include "WtGlobal.h"

using namespace Wt;

void ApplicationErrorNotifier::notify(const std::string& errorMessage)
{
    WMessageBox::show(u8"Ошибка", errorMessage, StandardButton::Ok);
    wApp->quit("");
}
