#include "game.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Hello Polycode!");
	Game *app = new Game(view);
	while(app->Update()) {}
	return 0;
}
