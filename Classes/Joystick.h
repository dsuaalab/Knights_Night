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
	float getDLength();	// ������ ������ ���̽�ƽ�� ���̸� ��Ÿ��.
	Point getDPoint();	// ������ �������� ���̽�ƽ�� �󸶳� ���������� ��ǥ�� ��Ÿ��.


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