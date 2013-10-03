#include "game.h"
#include "player.h"

using namespace Polycode;

Player::Player(Game* g) {
  sprinting = false;
  modifyMouse = 1;
  maxPitch = PI/2;
  minPitch = -PI/2;
  rotateY = maxPitch/4;
  rotateX = maxPitch/6;
  game = g;
	player = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,1.0,0.5);
	player->loadTexture("Resources/pink_texture.png");
	player->setColor(1.0, 1.0, 0.0, 1.0);
	player->setPosition(2,1,2);
	controller = game->scene->addCharacterChild(player, 10.0, 1.0, 0.001);
	walkSpeed = 0;
	
	game->scene->getDefaultCamera()->setPosition(player->getPosition());
	game->scene->getDefaultCamera()->setYaw(player->getYaw());
}

Player::~Player() {
  delete player;
  delete controller;
}

void Player::HandleInput(Event* e) {
  if(e->getDispatcher() == game->core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		
		switch(e->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
					case KEY_r:
						controller->warpCharacter(Vector3(2,1,2));
					break;				
					case KEY_w:
						walkSpeed = constWS;
					break;
					case KEY_s:
						walkSpeed = -constWS;
					break;
					case KEY_a:
						strafeSpeed = constSS;
					break;
					case KEY_d:
						strafeSpeed = -constSS;
					break;
          case KEY_LSHIFT:
            sprinting = true;
            break;
					case KEY_SPACE:
						controller->jump();
					break;
				}
			break;
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
					case KEY_w:
					case KEY_s:
						walkSpeed = 0;					
					break;					
					case KEY_a:
					case KEY_d:
						strafeSpeed = 0;					
					break;
          case KEY_LSHIFT:
            sprinting = false;
            break;
				}
			break;			
		}
	}
}

void Player::Update(Number elapsed) {
  pitch += elapsed * rotateX * modifyMouse * (game->center.y - game->mouse.y);
  if (pitch > maxPitch) pitch = maxPitch;
  else if (pitch < minPitch) pitch = minPitch;

  direction += elapsed * rotateY * (game->center.x - game->mouse.x);
  Vector3 pdir = Vector3(walkSpeed * -sin(direction),0,walkSpeed * -cos(-direction));
  pdir.x += strafeSpeed * elapsed * -cos(direction);
  pdir.z += strafeSpeed * elapsed * -sin(-direction);

  if (sprinting) {
    pdir = pdir * sprintFactor;
  }
  
  player->setYaw(direction*(180/PI));
  controller->setWalkDirection(pdir);
  
  game->scene->getDefaultCamera()->setPosition(player->getPosition());
  game->scene->getDefaultCamera()->setYaw(player->getYaw());
  game->scene->getDefaultCamera()->setPitch(pitch * (180/PI));
}
