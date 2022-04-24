#ifndef _WIATINGWINDOW_H_
#define _WIATINGWINDOW_H_

#include <Wt/WObject.h>
#include <Wt/WDialog.h>

class WaitingWindow final : public Wt::WObject
{
public:
    WaitingWindow();

    virtual ~WaitingWindow() = default;

public:
    void wait();

protected:
    void dialogClosed(Wt::DialogCode result);

private:
    Wt::WDialog* _dialog = nullptr;
};

#endif //_WIATINGWINDOW_H_
