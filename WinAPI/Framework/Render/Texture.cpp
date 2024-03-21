#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;
bool Texture::isDebugMode = true;

Texture::Texture(wstring file, COLORREF transColor, UINT frameX, UINT frameY)
    : imageFrame{ (long)frameX, (long)frameY }, transfColor(transColor)
{
    HDC hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    alphaMemDC = CreateCompatibleDC(hdc);
    hBitmap = (HBITMAP)LoadImage(hInst, file.c_str(),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);    

    
    SelectObject(memDC, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
    imageSize = { bitmap.bmWidth, bitmap.bmHeight };    

    cutSize = { imageSize.x / imageFrame.x, imageSize.y / imageFrame.y };    

    hAlphaBitmap = CreateCompatibleBitmap(hdc, cutSize.x, cutSize.y);

    SelectObject(alphaMemDC, hAlphaBitmap);

    ReleaseDC(hWnd, hdc);
}

Texture::~Texture()
{
    DeleteDC(memDC);
    DeleteObject(hBitmap);
}

Texture* Texture::Add(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Texture(file, transColor, frameX, frameY);
    textures[file] = texture;

    return texture;
}

void Texture::Remove(wstring file)
{
    if (textures.count(file) == 0)
        return;

    delete textures[file];
    textures.erase(file);
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
    {
        delete texture.second;
    }
}

void Texture::Render(HDC hdc, Rect* rect, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    if (!isTrans)
    {
        BitBlt(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            memDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,            
            SRCCOPY
        );
        return;
    }

    GdiTransparentBlt(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        memDC,
        cutSize.x * curFrame.x,
        cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );
}

void Texture::Render(HDC hdc, Rect* rect, int alpha, POINT curFrame, bool isTrans)
{
    if (isDebugMode)
    {
        rect->LineRender(hdc);
    }

    blendFunc.SourceConstantAlpha = alpha;

    if (!isTrans)
    {
        GdiAlphaBlend(
            hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->size.x, (int)rect->size.y,
            alphaMemDC,
            cutSize.x * curFrame.x,
            cutSize.y * curFrame.y,
            cutSize.x, cutSize.y,
            blendFunc
        );
        return;
    }

    BitBlt(
        alphaMemDC,
        0, 0, cutSize.x, cutSize.y,
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        SRCCOPY
    );

    GdiTransparentBlt(
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        memDC,
        cutSize.x * curFrame.x,
        cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transfColor
    );

    GdiAlphaBlend(
        hdc,
        (int)rect->Left(), (int)rect->Top(),
        (int)rect->size.x, (int)rect->size.y,
        alphaMemDC,
        0, 0,
        cutSize.x, cutSize.y,
        blendFunc
    );
}

float Texture::GetPixelHeight(const Vector2& pos)
{
    int startY = pos.y < 0.0f ? 0 : (int)pos.y;

    for (int y = startY; y < imageSize.y; y++)
    {
        COLORREF color = GetPixel(memDC, (int)pos.x, y);

        if (color != transfColor)
            return (float)y;
    }

    return (float)imageSize.y;
}
