#pragma once

class Digit : public ImageRect
{
public:
	Digit();
	~Digit();

	void Update();
	void Render(HDC hdc);

	void SetDigit(UINT digit) { value = digit; }

private:
	UINT value = 1;
};
