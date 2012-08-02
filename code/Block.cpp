#include "Block.h"


Block::Block(){
    this->mTexture = rand() % 5 + 1;
}
Block::~Block(){}

bool Block::isNotAir(){
    return (this->mTexture == 0) ? false : true;
}
