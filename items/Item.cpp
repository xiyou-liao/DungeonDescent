#include "Item.h"

using namespace std;

Item::Item(const string& name, const char* singleTextureFilepath) :
    mName(name), mSingleTextureFilepath(singleTextureFilepath) {}

Status Item::getStatus() const {
    return mStatus;
}

Item::~Item() {}

