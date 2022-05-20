#pragma once
#include "cocos2d.h"

USING_NS_CC;

class EnemyScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	//void createEnemy();

	CREATE_FUNC(EnemyScene);
	void setHealth(int newHealth);

private:
	int myHealth;
	Sprite *body;
	Sprite *weapon;

	
};