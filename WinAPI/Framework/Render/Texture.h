#pragma once

class Rect;

class Texture
{
private:
    Texture(wstring file, COLORREF transColor, UINT frameX, UINT frameY);
    ~Texture();

public:
    static Texture* Add(wstring file, UINT frameX = 1, UINT frameY = 1, COLORREF transColor = MAGENTA);
    static void Remove(wstring file);
    static void Delete();

    void Render(HDC hdc, Rect* rect, POINT curFrame = { 0, 0 }, bool isTrans = true);
    void Render(HDC hdc, Rect* rect, int alpha, POINT curFrame = { 0, 0 }, bool isTrans = true);

    float GetPixelHeight(const Vector2& pos);

    Vector2 GetSize() { return Vector2(cutSize); }
    POINT GetFrame() { return imageFrame; }
    HDC GetMemDC() { return memDC; }


    static void SetDebug() { isDebugMode = !isDebugMode; }
private:
    HDC memDC;
    HDC alphaMemDC;
    HBITMAP hBitmap;
    HBITMAP hAlphaBitmap;

    BLENDFUNCTION blendFunc;

    COLORREF transfColor;

    POINT imageSize;
    POINT imageFrame;
    POINT cutSize;

    static unordered_map<wstring, Texture*> textures;
    static bool isDebugMode;
};