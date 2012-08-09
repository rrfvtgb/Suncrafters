#ifndef XMLMGR_H
#define XMLMGR_H

#include <fstream>
#include <string>

#include "tinyxml.h"

class XmlMgr
{
    public:
        XmlMgr();
        virtual ~XmlMgr();

        void loadFile(std::string filename);
        TiXmlElement* getDocumentFirstChildElement();

        TiXmlDocument* mDocument;
        TiXmlHandle* mHdl;

        std::ofstream flux; //File error
    protected:
    private:
};

#endif // XMLMGR_H
