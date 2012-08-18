#include "PathMgr.h"

#include <fstream>
#include <stdlib.h>
#include <direct.h>

#if !defined( __WIN32__ ) || !defined( _WIN32 )
#include <sys/stat.h>
#include <sys/types.h>
#endif

PathMgr::PathMgr(){}
std::string PathMgr::getDataStorageFolder(){
    std::string pathToStorageData;
    if(PathMgr::isWindows()){
        pathToStorageData = std::string(getenv("APPDATA")) + std::string("\\.Suncrafters\\");
        mkdir(pathToStorageData.c_str());
        return pathToStorageData;
    }else{
        pathToStorageData = std::string(getenv("HOME")) + std::string(".Suncrafters/");
        mkdir(pathToStorageData.c_str());
        return pathToStorageData;
    }
}
bool PathMgr::isLinux(){
    #if defined( __SYMBIAN32__ ) || defined( __WIN32__ ) || defined( _WIN32 ) || defined( __APPLE_CC__)
        return false;
    #else
        return true;
    #endif
}

bool PathMgr::isWindows(){
    #if defined( __WIN32__ ) || defined( _WIN32 )
        return true;
    #else
        return false;
    #endif
}



PathMgr::~PathMgr(){
    //dtor
}
