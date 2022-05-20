#pragma once
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class PlayerMoveScene : public Scene
{
public:
	static Scene* createScene();

	Player* player;

	virtual bool init();
	virtual void update(float delta);

	// PC �׽�Ʈ�� Ű�Է� �̺�Ʈ �Լ�
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	CREATE_FUNC(PlayerMoveScene);
};