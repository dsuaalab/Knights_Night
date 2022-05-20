#include "Player.h"

Player* Player::create()
{
	Player* sprite = new (std::nothrow) Player();	// 정상적으로 생성되지 않을 때의 예외처리
	
	// Initialize
	if (sprite && sprite->initWithTexture(sprite->texture, Rect(16, 32, 48, 48)))
	{
		sprite->setScale(3.0f);
		sprite->autorelease();		// Sprite 사용 끝날 시, 메모리 자동으로 해제가 가능하게 함.

		sprite->bIsReadyToAttack = false;
		return sprite;
	}

	CC_SAFE_DELETE(sprite);		// Sprite 제거
	return nullptr;
}

void Player::onWalkAnimation()
{
	if (this->numberOfRunningActions() != 0)
		return;

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.05f);

	for (int i = 1; i < 14; i++)
		animation->addSpriteFrameWithTexture(texture, Rect(16 + (40.6 * i), 32, 48, 48));

	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void Player::onAttackAnimation()
{
	if (this->numberOfRunningActions() != 0)
		return;

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 3; i < 4; i++)
		animation->addSpriteFrameWithTexture(texture, Rect(22 + (45 * i), 110, 48, 48));
	for (int i = 4; i < 11; i++)
		animation->addSpriteFrameWithTexture(texture, Rect(16 + (50.4 * i), 110, 48, 48));

	auto animate = Animate::create(animation);
	this->runAction(animate);
	this->bIsReadyToAttack = true;
}

void Player::stopAnimation()
{
	this->setTextureRect(Rect(16, 32, 48, 48));
	this->stopAllActions();
}