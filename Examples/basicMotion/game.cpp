#include "game.h"
#include "player.h"

Game::Game(PolycodeView *view) : EventHandler() {
  running = true;
  enableMouse = false;
  width = 640;
  height = 480;
  center.set(width * .5, height * .5);
  mouse = center;
	core = new POLYCODE_CORE(view, 800,600,false,false,4,0,120, 0);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
  scene = new PhysicsScene();

  hud = new Screen();

  ScreenLabel* movement = new ScreenLabel("WASD - move | Space - jump | Mouse - look", 16);
  ScreenLabel* movement2 = new ScreenLabel("Sprint - shift |  R - reset", 16);
  ScreenLabel* misc = new ScreenLabel("Escape - release cursor | Q - quit", 16);
  ScreenLabel* gen = new ScreenLabel("F - random boxes | G - random panels", 16);
  movement2->setPosition(0,16);
  misc->setPosition(0,32);
  gen->setPosition(0,48);

  hud->addChild(movement);
  hud->addChild(movement2);
  hud->addChild(misc);
  hud->addChild(gen);

	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 30, 30);
  manager = CoreServices::getInstance()->getMaterialManager();
  Texture* tiles = manager->createTextureFromFile("Resources/green_texture.png", false, false);
  ground->setTexture(tiles);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);

  player = new Player(this);

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
		
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	
  core->warpCursor(center.x, center.y);
  core->enableMouse(enableMouse);
}

void Game::randomCubes() {
  for(int i=0; i < 10; i++) {
		ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.8,0.8,0.8);
		box->loadTexture("Resources/pink_texture.png");
		box->Roll(-45 + (rand() % 90));
		box->Pitch(-45 + (rand() % 90));		
		box->setPosition(-2 + (rand() % 4), 10, -2 + (rand() % 4));
		scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 1.0);
	}
}

void Game::randomPanels() {
  for(int i=0; i < 10; i++) {
		ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.8,0.1,0.8);
		box->loadTexture("Resources/pink_texture.png");
		box->Roll(-45 + (rand() % 90));
		box->Pitch(-45 + (rand() % 90));		
		box->setPosition(-2 + (rand() % 4), 10, -2 + (rand() % 4));
		scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 1.0);
	}
}

void Game::handleEvent(Event *e) {
  player->HandleInput(e);
  if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		
		switch(e->getEventCode()) {
      case InputEvent::EVENT_MOUSEMOVE:
        mouse.x = inputEvent->mousePosition.x;
        mouse.y = inputEvent->mousePosition.y;
        break;
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
          case KEY_ESCAPE:
            enableMouse = !enableMouse;
            core->enableMouse(enableMouse);
            mouse = center;
            break;
          case KEY_f:
            randomCubes();
            break;
          case KEY_g:
            randomPanels();
            break;
          case KEY_q:
            running = false;
            break;
				}
			break;
		}
	}
}

Game::~Game() {
  delete core;
  delete scene;
  delete player;
}

bool Game::Update() {
	Number elapsed = core->getElapsed();

  if(!enableMouse) {
    player->Update(elapsed);
    
    core->warpCursor(center.x, center.y);
    mouse.x = center.x;
    mouse.y = center.y;
  }

  return running && core->updateAndRender();
}
