#include "Framework.h"

Digit::Digit()
	:ImageRect(L"Textures/CookieRun/UI/Digit.bmp", 10, 1)
{
}

Digit::~Digit()
{
}

void Digit::Update()
{
	if (KEY_DOWN('0'))
	{
		value = 0;
	}
	if (KEY_DOWN('1'))
	{
		value = 1;
	}
	if (KEY_DOWN('2'))
	{
		value = 2;
	}
	if (KEY_DOWN('3'))
	{
		value = 3;
	}
	if (KEY_DOWN('4'))
	{
		value = 4;
	}
	if (KEY_DOWN('5'))
	{
		value = 5;
	}
	if (KEY_DOWN('6'))
	{
		value = 6;
	}

}

void Digit::Render(HDC hdc)
{
	POINT p;
	p.x = value;
	p.y = 0;
	ImageRect::Render(hdc, p);
}
