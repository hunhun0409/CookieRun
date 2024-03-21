#include "Framework.h"

Item::Item(ItemData data)
	:Button(data.file), data(data)
{
	
}

Item::~Item()
{
}

void Item::Update()
{
	Button::Update();
}

void Item::Render(HDC hdc)
{
	Button::Render(hdc);
}

void Item::LeftClickStoreItem()
{
	Observer::Get()->ExcuteParamEvents("StoreItemSelect", this);
}

void Item::RightClickStoreItem()
{
	Observer::Get()->ExcuteParamEvents("StoreItemSelect", this);
	Observer::Get()->ExcuteEvents("StoreClickPurchaseButton");
}

void Item::LeftClickInventoryItem()
{
	Observer::Get()->ExcuteParamEvents("InventoryItemSelect", this);

}

void Item::RightClickInventoryItem()
{
	Observer::Get()->ExcuteParamEvents("InventoryItemSelect", this);
	Observer::Get()->ExcuteEvents("SellItem");

}


