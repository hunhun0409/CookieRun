#pragma once

class ImageRect : public Rect
{
public:
    ImageRect();
    ImageRect(wstring file, UINT frameX = 1, UINT frameY = 1,  
        COLORREF transColor = MAGENTA);
    ImageRect(Texture* texture);
    ~ImageRect();

    void Render(HDC hdc, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

    void CamRender(HDC hdc, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void CamRender(HDC hdc, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

    Texture* GetTexture() { return texture; }
    void SetTexture(Texture* texture);

    Rect* GetCamRect() { return camRect; }



protected:
    Texture* texture = nullptr;
    Rect* camRect;
};