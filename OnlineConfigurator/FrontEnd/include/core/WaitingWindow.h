#ifndef _WIATINGWINDOW_H_
#define _WIATINGWINDOW_H_

#include <string>

#include <Wt/WDialog.h>
#include <Wt/WTimer.h>

#include <Singleton.h>

class WaitingWindow final : public Singleton<WaitingWindow>
{
public:
    virtual ~WaitingWindow() = default;

    void show(const std::string& text = {});

    void hide();

private:
    Wt::WDialog*    _dialog = nullptr;
    Wt::WTimer*     _timer = nullptr;
    int             _counter = 0;
};

#endif //_WIATINGWINDOW_H_
