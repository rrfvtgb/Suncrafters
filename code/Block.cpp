#include "Block.h"

#include <string>
#include <iostream>
#include <fstream>

Block::Block(){
    this->mTexture = 5;
}
Block::~Block(){}

bool Block::isVisible(){
    return (this->mTexture == 0) ? true : false;
}
