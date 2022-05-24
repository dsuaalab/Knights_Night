#include "Joystick.h"

Joystick* Joystick::create()
{
	Joystick* joystick = new (std::nothrow) Joystick();	// 정상적으로 생성되지 않을 때의 예외처리

	// Initialize
	if (joystick && joystick->init())
		return joystick;

	return nullptr;
}

bool Joystick::init()
{
	joystickBG = Sprite::create("joystick_background.png");
	joystickBG->setPosition(Vec2(250, 250));
	joystickBG->setScale(1.0f);	// Size
	joystickBG->setOpacity(150);
	addChild(joystickBG);

	joystick = Sprite::create("joystick_thumb.png");
	joystick->setPosition(Vec2(250, 250));
	joystick->setScale(1.0f);	// Size
	joystick->setOpacity(100);
	addChild(joystick);

	attackBtn = Sprite::create("joystick_background.png");		// 임시 이미지
	attackBtn->setPosition(Vec2(Director::getInstance()->getVisibleSize().width -  250, 250));
	attackBtn->setScale(1.0f);	// Size
	attackBtn->setOpacity(100);
	addChild(attackBtn);

	startPoint = Vec2(250, 250);
	joystickTouched = false;
	attackBtnTouched = false;

	// Touches Listener
	auto TListener = EventListenerTouchAllAtOnce::create();
	TListener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
	TListener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
	TListener->onTouchesCancelled = CC_CALLBACK_2(Joystick::onTouchesCancelled, this);
	TListener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(TListener, this);

	return true;
}

void Joystick::setJoystickScale(float scale)
{
	joystickBG->setScale(scale);
	joystick->setScale(scale);
}

void Joystick::setAttackBtnScale(float scale)
{
	attackBtn->setScale(scale);
}

void Joystick::setJoystickPosition(Point point)
{
	joystickBG->setPosition(point);
	joystick->setPosition(point);
	startPoint = point;
}

float Joystick::getDLength()
{
	return sqrtf(((startPoint.x - joystick->getPosition().x)
		* (startPoint.x - joystick->getPosition().x)
		+ (startPoint.y - joystick->getPosition().y)
		* (startPoint.y - joystick->getPosition().y))
		/ ((joystickBG->getContentSize().width / 2) * joystickBG->getScale())
	);
}

Point Joystick::getDPoint()
{
	Point point;
	point.x = (joystick->getPosition().x - startPoint.x) / ((joystickBG->getContentSize().width / 2) * joystickBG->getScale());
	point.y = (joystick->getPosition().y - startPoint.y) / ((joystickBG->getContentSize().width / 2) * joystickBG->getScale());
	return point;
}

void Joystick::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();	// Same to 'auto it = touches.end()'.

	Touch* touch;
	Point tap;

	for (auto it = touches.begin(); it != touches.end(); it++)
	{
		touch = (Touch*)(*it);

		if (touch)
		{
			tap = touch->getLocation();

			if (joystickBG->getBoundingBox().containsPoint(tap) && !joystickTouched)
			{
				joystick->setPosition(touch->getLocation());
				joystickTouched = true;

				// Only Debug.
				CCLOG("location x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
			}

			if (attackBtn->getBoundingBox().containsPoint(tap) && !attackBtnTouched)
			{
				attackBtnTouched = true;
				// Only Debug.
				CCLOG("Began::Worked Attack Button.");
			}
		}
	}
}

void Joystick::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch* touch;
	Point tap;
	Point ntap;

	if (joystickTouched)
	{
		for (auto it = touches.begin(); it != touches.end(); it++)
		{
			touch = (Touch*)(*it);

			if (touch)
			{
				tap = touch->getLocation();
				CCLOG("%f , %f", tap.x, startPoint.x + (joystickBG->getContentSize().width / 2) * joystickBG->getScale());

				if (tap.x > startPoint.x + (joystickBG->getContentSize().width / 2) * joystickBG->getScale())
				{
					ntap.x = startPoint.x + (joystickBG->getContentSize().width / 2) * joystickBG->getScale();
				}
				else if (tap.x < startPoint.x - (joystickBG->getContentSize().width / 2) * joystickBG->getScale())
				{
					ntap.x = startPoint.x - (joystickBG->getContentSize().width / 2) * joystickBG->getScale();
				}
				else
				{
					ntap.x = tap.x;
				}

				if (tap.y > startPoint.y + (joystickBG->getContentSize().height / 2) * joystickBG->getScale())
				{
					ntap.y = startPoint.y + (joystickBG->getContentSize().height / 2) * joystickBG->getScale();
				}
				else if (tap.y < startPoint.y - (joystickBG->getContentSize().height / 2) * joystickBG->getScale())
				{
					ntap.y = startPoint.y - (joystickBG->getContentSize().height / 2) * joystickBG->getScale();
				}
				else
				{
					ntap.y = tap.y;
				}

				joystick->setPosition(ntap);
			}
		}
	}

	if (attackBtnTouched)
	{
		CCLOG("Move::Worked Attack Button.");
	}
}

void Joystick::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
{
	joystick->setPosition(startPoint);
	joystickTouched = false;
	attackBtnTouched = false;
}

void Joystick::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	joystick->setPosition(startPoint);
	joystickTouched = false;
	attackBtnTouched = false;
}