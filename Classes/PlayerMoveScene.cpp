#include "PlayerMoveScene.h"

Scene* PlayerMoveScene::createScene()
{
	return PlayerMoveScene::create();
}

bool PlayerMoveScene::init()
{
	// Scene 초기화가 올바르게 되지 않았을 때 예외처리.
	if (!Scene::init())
		return false;

	auto bgColor = LayerColor::create(Color4B(0, 200, 0, 255));
	this->addChild(bgColor);

	player = Player::create();
	player->setPosition(800, 450);
	// player->onAnimation();
	this->addChild(player);

	joystick = Joystick::create();		// It's Layer! Not Sprite!
	joystick->setJoystickPosition(Vec2(200, 200));
	joystick->setJoystickScale(2.0f);
	joystick->setAttackBtnScale(2.0f);
	this->addChild(joystick, 1);

	// Keyboard Listener
	auto kListener = EventListenerKeyboard::create();
	kListener->onKeyPressed = CC_CALLBACK_2(PlayerMoveScene::onKeyPressed, this);
	kListener->onKeyReleased = CC_CALLBACK_2(PlayerMoveScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(kListener, this);

	this->scheduleUpdate();

	return true;
}

void PlayerMoveScene::update(float delta)
{
	int speed = 2;

	// Joystick Part
	player->setPosition(player->getPosition().x + joystick->getDPoint().x * speed, player->getPosition().y + joystick->getDPoint().y * speed);

	if (joystick->joystickTouched)	// Touches on
	{
		if (joystick->getDPoint().x > 0)
			player->setFlippedX(true);
		else
			player->setFlippedX(false);

		player->onWalkAnimation();
	}
	else if (joystick->attackBtnTouched)
	{
		player->onAttackAnimation();
	}
	else
	{
		player->stopAnimation();
	}



	// Keyboard Part
	switch (player->state)
	{
	case Player::State::UP:
		player->setPosition(player->getPosition().x, player->getPosition().y + speed);
		player->onWalkAnimation();
		break;
	case Player::State::DOWN:
		player->setPosition(player->getPosition().x, player->getPosition().y - speed);
		player->onWalkAnimation();
		break;
	case Player::State::LEFT:
		player->setPosition(player->getPosition().x - speed, player->getPosition().y);
		player->setFlippedX(false);
		player->onWalkAnimation();
		break;
	case Player::State::RIGHT:
		player->setPosition(player->getPosition().x + speed, player->getPosition().y);
		player->setFlippedX(true);
		player->onWalkAnimation();
		break;
	case Player::State::STOP:
		// player->stopAnimation();
		break;
	case Player::State::ATTACK:
		player->onAttackAnimation();
		CCLOG("ATTACK!");
		break;
	}
}

void PlayerMoveScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		player->state = Player::State::UP;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player->state = Player::State::DOWN;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		player->state = Player::State::LEFT;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player->state = Player::State::RIGHT;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		player->state = Player::State::ATTACK;
		break;
	}
}

void PlayerMoveScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	player->state = Player::State::STOP;
}