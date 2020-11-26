#include "Game.hpp"

static time_t lastModification = 0;
void Game::onFileTick() {
	struct stat statDesc;
	stat("test.txt", &statDesc);

	if (lastModification < statDesc.st_mtime) {
		parse();
		lastModification = statDesc.st_mtime;
	}
}

static float timer = 0.0;
void Game::update(double dt) {
	pollInput(dt);
	Tortue.update(dt);

	timer -= dt;
	if (timer <= 0.0) {
		onFileTick();
		timer = 0.1;
	}
}
