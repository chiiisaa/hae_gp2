#include "totue.hpp"

void tortue::update(double dt) {
	life += dt;
	if (cmdBuffer.size()) {
		if (life > 1.0) {
			play(cmdBuffer[0]);
			cmdBuffer.erase(cmdBuffer.begin());
			life = 0;
		}
	}

	angle = (targetAngle - angle) * 0.12 + angle;
	Vector2f position = player.getPosition();
	position.x = (targetPosition.x - position.x) * 0.1 + position.x;
	position.y = (targetPosition.y - position.y) * 0.1 + position.y;
	_setPosition(position);
	a.setRotation(angle);
}

void tortue::play(Cmd exe) {

	switch (exe)
	{
	case Advance:avancer(30);break;
	case Backward:reculer(30);break;
	case TurnLeft45:turnProgressive(45); break;
	case TurnRight45:turnProgressive(-45); break;
	case DrawOn: drawOn(); break;
	case DrawOff: drawOff(); break;
	default:
		break;
	}
}

void tortue::play(std::vector<Cmd> execute) {
	for (Cmd& cmd : execute) {
		play(cmd);
	}
}

void tortue::PlayProgressif(vector<Cmd>& execute) {
	cmdBuffer = execute;
}



