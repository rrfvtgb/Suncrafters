#include "XmlMgr.h"

XmlMgr::XmlMgr() : mDocument(0), mHdl(0), flux(std::string("report/xmlError.txt").c_str()){}

void XmlMgr::loadFile(std::string filename){
    mDocument = new TiXmlDocument(filename.c_str());
    if(!mDocument->LoadFile()){
        this->flux << "error while loading" << std::endl;
        this->flux << "error #" << mDocument->ErrorId() << " : " << mDocument->ErrorDesc() << std::endl;
        return;
    }
    mHdl = new TiXmlHandle(mDocument);
}

TiXmlElement* XmlMgr::getDocumentFirstChildElement(){
    return mHdl->FirstChildElement().FirstChildElement().ToElement();
}

XmlMgr::~XmlMgr(){
    delete this->mDocument;
    delete this->mHdl;
}
