#include "PlayerMoveScene.h"

Scene* PlayerMove::createScene()
{
	return PlayerMove::create();
}

bool PlayerMove::init()
{
	// Scene �ʱ�ȭ�� �ùٸ��� ���� �ʾ��� �� ����ó��.
	if (!Scene::init())
		return false;

	return true;
}