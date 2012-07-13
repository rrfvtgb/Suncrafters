#ifndef MAIN_H
#define MAIN_H

#include "BaseApplication.h"

class Main : public BaseApplication
{
    public:
        Main();
        virtual ~Main();
    protected:
        virtual void createScene(void);
    private:
};

#endif // MAIN_H
