#pragma once

#define constWS 0.05
#define sprintFactor 3 
#define constSS 5

#include "game.h"

using namespace Polycode;

class Game;

class Player {
  public:
    Player(Game* g);
    ~Player();
    void HandleInput(Event *e);
    void Update(Number elapsed);

    PhysicsCharacter *controller;
    ScenePrimitive *player;

    Number walkSpeed, direction, pitch, rotateX, rotateY, strafeSpeed;
    bool sprinting;
    Game *game;

  private:
    Number maxPitch, minPitch, modifyMouse;
};
