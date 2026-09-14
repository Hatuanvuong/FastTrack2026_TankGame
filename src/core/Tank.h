#pragma once

enum class PlayerId
{
    Player1,
    Player2
};

struct Tank
{
    PlayerId owner;

    float x;
    float y;

    float width;
    float height;

    int hp;
};