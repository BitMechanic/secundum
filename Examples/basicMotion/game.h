#pragma once

#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "PolycodeUI.h"
#include <iostream>

#include "player.h"

using namespace Polycode;

class Game : public EventHandler {
public:
  Game(PolycodeView *view);
  ~Game();
  bool Update();
  void handleEvent(Event *e);

  void randomCubes();
  void randomPanels();
	
  Core *core;
  MaterialManager* manager;
  PhysicsScene *scene;
  Screen* hud;
  Vector2 center, mouse;
    
private:
  bool running;
  bool enableMouse;
  Number width, height;

  Player *player;
};
