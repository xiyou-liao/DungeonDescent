
#ifndef ITEM_H
#define ITEM_H
#include "../game/Game.h"


class Item {
public:
    Item(const std::string& name, const char* textureFilepath);
    Status getStatus() const;
    virtual ~Item();
    const char* getCombinedTextureFilepath() const;
private:
    std::string mName;
    Status mStatus = ACTIVE;

    const char* mSingleTextureFilepath;
};
#endif //ITEM_H