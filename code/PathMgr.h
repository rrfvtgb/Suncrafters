#ifndef PATHMGR_H
#define PATHMGR_H

#include <string>

class PathMgr
{
    public:
        PathMgr();
        virtual ~PathMgr();
        static bool isWindows();
        static bool isLinux();
        static std::string getDataStorageFolder();

    protected:
    private:
};

#endif // PATHMGR_H
