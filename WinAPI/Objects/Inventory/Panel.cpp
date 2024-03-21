#include "Framework.h"

Panel::Panel(wstring file)
	:Button(file)
{
	dragRect = new Rect();
	thumbnailImage = new ImageRect();
}

Panel::~Panel()
{
	delete dragRect;
	delete thumbnailImage;
	for (Item* item : items)
	{
		delete item;
	}
}

void Panel::Update()
{
	Button::Update();
	Drag();
	SetItemPos();

	if (thumbnailImage)
	{
		thumbnailOffset.x = -size.x * 0.325f;
		thumbnailOffset.y = -size.y * 0.24f;


		thumbnailImage->size = {size.y * 0.32f,size.y * 0.32f };
		thumbnailImage->pos = pos + thumbnailOffset;
	}

	for (Item* item : items)
	{
		item->pos = pos + item->GetLocalPos();
		item->Update();
	}
}

void Panel::Render(HDC hdc)
{
	Button::Render(hdc);
	dragRect->LineRender(hdc);

	if (thumbnailImage)
	{
		thumbnailImage->Render(hdc);
		thumbnailImage->LineRender(hdc);
	}

	for (Item* item : items)
	{
		item->Render(hdc);
	}
	Vector2 textPos = pos + Vector2(-30, -90);
	TextOutA(hdc, textPos.x, textPos.y, descStr.c_str(), descStr.size());

	if (font)
	{
		oldFont = (HFONT)SelectObject(hdc, font);
	}

	COLORREF oldColor = SetTextColor(hdc, fontColor);

	RECT rect = { dragRect->Left(), dragRect->Top() + fontSize * 0.5f,
		Right(), Bottom() + fontSize * 0.25f };
	DrawTextA(hdc, name.c_str(), name.length(), &rect, DT_CENTER);

	if(font)
		SelectObject(hdc, oldFont);
	SetTextColor(hdc, oldColor);
}

void Panel::Drag()
{
	dragRect->size = { size.x, size.y * 0.1f };
	dragRect->pos.x = pos.x;
	dragRect->pos.y = pos.y - size.y * 0.45f;

	if (KEY_DOWN(VK_LBUTTON))
	{
		if (dragRect->IsCollision(mousePos))
		{
			isDrag = true;
			offset = pos - mousePos;
		}
	}

	if (isDrag && KEY_PRESS(VK_LBUTTON))
	{
		pos = mousePos + offset;
	}

	if (KEY_UP(VK_LBUTTON))
	{
		isDrag = false;
		offset = {};
	}
}
void Panel::SetItemPos()
{
	int colCount = 15;
	float interval = 6.0f;
	Vector2 startOffset(-274, 20);

	int count = 0;
	for (Item* item : items)
	{
		Vector2 coord;
		coord.x = count % colCount;
		coord.y = count / colCount;

		item->LocalPos() = startOffset + coord * item->size + coord * interval;

		count++;
	}

}
void Panel::SelectItem(void* item)
{
	if (item)
	{
		selectItem = (Item*)item;

		thumbnailImage->SetTexture(selectItem->GetTexture());
		thumbnailImage->size = { size.y * 0.32f,size.y * 0.32f };

		descStr = "이름 : " + selectItem->GetData().name + "      ";
		descStr += "가격 : " + to_string(selectItem->GetData().price);
	}
	
}


