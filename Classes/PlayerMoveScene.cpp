#include "PlayerMoveScene.h"

Scene* PlayerMove::createScene()
{
	return PlayerMove::create();
}

bool PlayerMove::init()
{
	// Scene 초기화가 올바르게 되지 않았을 때 예외처리.
	if (!Scene::init())
		return false;

	return true;
}