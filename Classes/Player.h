#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
private:
	const std::string filename = "debug_Player_SpriteSheet.png";
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filename);
public:
	enum State { STOP, UP, DOWN, LEFT, RIGHT, ATTACK } state = STOP;

	static Player* create();
	void onWalkAnimation();
	void onAttackAnimation();
	void stopAnimation();

	bool bIsReadyToAttack;
};