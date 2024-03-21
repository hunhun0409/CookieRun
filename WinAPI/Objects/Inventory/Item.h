#pragma once

class Item : public Button
{
public:
	Item(ItemData data);
	~Item();

	void Update();
	void Render(HDC hdc);

	void SetLocalPos(Vector2 pos) { localPos = pos; }
	Vector2& GetLocalPos() { return localPos; }
	ItemData& GetData() { return data; }

	void LeftClickStoreItem();
	void RightClickStoreItem();
	void LeftClickInventoryItem();
	void RightClickInventoryItem();

	Vector2& LocalPos() { return localPos; }

private:
	ItemData data;
	Vector2 localPos = {  };
};