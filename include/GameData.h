#ifndef GAMEDATA_H
#define GAMEDATA_H

struct GameData {
    bool playerVictory;
    explicit GameData(bool victory = false) : playerVictory(victory) {}
};

#endif
