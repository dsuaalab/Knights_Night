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
		player->stopAnimation();
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