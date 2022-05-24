#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Joystick : public Layer
{
private:
	Point startPoint;
public:
	static Joystick* create();
	virtual bool init();

	void setJoystickScale(float scale);
	void setAttackBtnScale(float scale);
	void setJoystickPosition(Point point);
	float getDLength();	// 원점과 움직인 조이스틱의 길이를 나타냄.
	Point getDPoint();	// 원점을 기준으로 조이스틱을 얼마나 움직였는지 좌표로 나타냄.


	Sprite* joystick;
	Sprite* joystickBG;
	Sprite* attackBtn;
	bool joystickTouched;
	bool attackBtnTouched;

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
	virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};