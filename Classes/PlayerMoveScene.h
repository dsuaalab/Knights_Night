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

	// PC 테스트용 키입력 이벤트 함수
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	CREATE_FUNC(PlayerMoveScene);
};