#ifndef _WIATINGWINDOW_H_
#define _WIATINGWINDOW_H_

#include <Singleton.h>

class WaitingWindow final : public Singleton<WaitingWindow>
{
public:
    virtual ~WaitingWindow() = default;

    void wait();
};

#endif //_WIATINGWINDOW_H_
