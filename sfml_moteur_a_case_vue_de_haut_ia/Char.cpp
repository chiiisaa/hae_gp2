#include "Char.hpp"
#include "Game.hpp"
#include <iostream>

void Char::setCellPosition(int cx, int cy)
{
	rx = 0.5;
	ry = 0.99;
	this->cx = cx;
	this->cy = cy;
}

void Char::setPosition(int rpx, int rpy) {
	cx = rpx / GRID_SIZE;
	rx = rpx - (cx * GRID_SIZE);

	cy = rpy / GRID_SIZE;
	ry = rpy - (cy * GRID_SIZE);
}

void Char::onWallCollision() {
	if (state == WalkTo) stop();
}

void Char::IdleState(Char* lthis) {

	lthis->spr.setFillColor(sf::Color(0xFA3092ff));


	if (lthis->speedX != 0 || lthis->speedY != 0 )
	{
		lthis->updateState = WalkState;
		lthis->state = Walk;
	}
}

void Char::WalkState(Char* lthis) {

	lthis->spr.setFillColor(sf::Color::Black);

	if (lthis->isWallHit(lthis->cx + 1, lthis->cy)) {
		lthis->setState(Cover);
	}

	if (lthis->isWallHit(lthis->cx - 1, lthis->cy)) {
		lthis->setState(Cover);
	}

	if (lthis->isWallHit(lthis->cx, lthis->cy + 1)) {
		lthis->setState(Cover);
	}

	if (lthis->speedX > 40 || lthis->speedY > 40 || lthis->speedX < -40 || lthis->speedY < -40)
	{
		lthis->setState(Running);
	}
}

void Char::running(Char*lthis) {

	lthis->spr.setFillColor(sf::Color::Yellow);
	
	if (lthis->isWallHit(lthis->cx + 1, lthis->cy)) {
		lthis->setState(Cover);
	}

	if (lthis->isWallHit(lthis->cx - 1, lthis->cy)) {
		lthis->setState(Cover);
	}

	if (lthis->isWallHit(lthis->cx, lthis->cy + 1)) {
		lthis->setState(Cover);
	}

}

void Char::CoverState(Char* lthis) {
	lthis->spr.setFillColor(sf::Color::Red);

	if (!lthis->isWallHit(lthis->cx + 1, lthis->cy) && !lthis->isWallHit(lthis->cx - 1, lthis->cy) && !lthis->isWallHit(lthis->cx, lthis->cy + 1)) {
		lthis->setState(Idle);
	}

}


void Char::update(double dt) {

	rx += speedX * dt;
	ry += speedY * dt;

	while (rx > 1) {
		if (isWallHit(cx + 1, cy)) {
			rx = 0.95;
		}
		else {
			rx--;
			cx++;
		}
	}

	while (rx < 0) {
		if (isWallHit(cx - 1, cy)) {
			rx = 0.05;
		}
		else {
			rx++;
			cx--;
		}
	}

	while (ry > 1) {
		if (isWallHit(cx, cy+1)) {
			ry = 0.95;
		}
		else {
			ry--;
			cy++;
		}
	}

	while (ry < 0) {
		if (isWallHit(cx, cy-1)) {
			ry = 0.05;
		}
		else {
			ry++;
			cy--;
		}
	}

	/*if (updateState2) {
		updateState2(*this);
	}*/

	/*if (updateState)
	{
		updateState(this);
	}*/
	
	/*if (cupdateState)
		cupdateState->updateState();*/

	/*if (state == Jumping) {
		jumping();
	}
	if (state == Running) {
		running();
	}*/

	switch (state)
	{
	case WalkTo:
		/*
		if (	isWallHit(cx, cy - 1)
			||	 isWallHit(cx, cy + 1)
			|| isWallHit(cx - 1, cy)
			|| isWallHit(cx + 1, cy)
			) {
			stop();
		}
		*/
		/*
		if (speedX > 0 && isWallHit( cx + 1, cy)) {
			stop();
		}
		else if (speedX < 0 && isWallHit(cx - 1, cy)) {
			stop();
		}
		else if (speedY < 0 && isWallHit(cx, cy -1)) {
			stop();
		}
		else if (speedY >0 && isWallHit(cx, cy + 1)) {
			stop();
		}
		else
		*/
	{
		if ((((int)destX) == cx) && (((int)destY) == cy)) {
			speedX = 0.0;
			speedY = 0.0;
			setState(Idle);
		}
	}
	break;
	case Idle:
		if (
			isWallHit(cx, cy - 1)
			|| isWallHit(cx, cy + 1)
			|| isWallHit(cx - 1, cy)
			|| isWallHit(cx + 1, cy)
			) {
			setState(Cover);
		}
		break;
	case Cover:
		break;
	case Walk:
		if ((abs(speedX) < 0.01) && (abs(speedY) < 0.01)) {
			speedX = 0.0;
			speedY = 0.0;
			setState(Idle);
		}
		break;
	case Running:
		if ((abs(speedX) < 0.01) && (abs(speedY) < 0.01)) {
			speedX = 0.0;
			speedY = 0.0;
			setState(Idle);
		}
		break;
	default:
		break;
	}

	speedX *= frictX;
	speedY *= frictX;

	spr.setPosition(getPositionPixel());
}

/*void Char::doRunningState() {
	if (!isWallHit(cx, cy + 1)) {
		setState(Jumping);
	}
}

void Char::doJumpingState() {
	if (speedY < 0)
		while (ry < 0) {
			ry++;
			cy--;
		}

	if (speedY > 0)
		while (ry > 0.99) {
			if (isWallHit(cx, cy + 1)) {
				ry = 0.99;
				speedY = 0.0;
				speedX *= 0.5;
				setState(Running);
				break;
			}
			else {
				ry--;
				cy++;
			}
		}
}

void Char::setState(State st) {
	state = st;
	if (st == Running) {
		updateState2 = std::mem_fn(&Char::doRunningState);
	}
	else if (st == Jumping) {
		updateState2 = std::mem_fn(&Char::doJumpingState);
	}
}*/

void Char::stop() {
	speedX = 0.0;
	speedY = 0.0;
	setState(Idle);
}

void Char::defaultFriction() {
	frictX = 0.87;
	frictY = 0.87;
}

void Char::setState(State st) {
	/*state = st;
	if (st == Idle) {

		updateState = IdleState;
		//cupdateState = new CIdleState(this);
	}
	else if (st == Walk) {
		updateState = WalkState;
		//cupdateState = new CWalkState(this);
	}
	else if (st == Running) {

		updateState = running;
		//cupdateState = new CRunningState(this);
	}
	else if (st == Cover) {
		updateState = CoverState;
		//cupdateState = new CJumpingState(this);
	}*/

	state = st;

	destX = 0;
	destY = 0;
	defaultFriction();

	switch (state)
	{
	case WalkTo:
		spr.setFillColor(sf::Color(0x6a6a6aff));
		frictX = 1.0;
		frictY = 1.0;
		break;
	case Idle:
		spr.setFillColor(sf::Color(0xffffffff));
		break;
	case Cover:
		spr.setFillColor(sf::Color(0xF0E452ff));
		break;
	case Walk:
		spr.setFillColor(sf::Color(0x57FAB1ff));
		break;
	case Running:
		spr.setFillColor(sf::Color(0xF75E59ff));
		break;
	default:
		break;
	}
}

bool Char::isWallHit(int cx, int cy)
{
	return game->isWall(cx, cy);
}
