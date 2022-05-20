#include "EnemyScene.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* EnemyScene::createScene()
{
	return EnemyScene::create();
}

bool EnemyScene::init()
{
	// Scene 초기화가 올바르게 되지 않았을 때 예외처리.
	if (!Scene::init())
		return false;
	auto testEnemy = Sprite::create("grossini.png");
	testEnemy->setPosition(Vec2(0, 1));
	this->addChild(testEnemy);
	

	return true;
}

/*void Enemy::createEnemy()
{

}*/

void EnemyScene::setHealth(int newHealth)
{
	myHealth = newHealth;
}