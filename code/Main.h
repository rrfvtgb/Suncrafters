#ifndef MAIN_H
#define MAIN_H

#include "BaseApplication.h"
#include "PlayerMgr.h"

class Main : public BaseApplication
{
    public:
        Main();
        virtual ~Main();
    protected:
        virtual void createScene(void);
        virtual void createFrameListener(void);
    private:
        PlayerMgr* mPlayer;
};

#endif // MAIN_H
