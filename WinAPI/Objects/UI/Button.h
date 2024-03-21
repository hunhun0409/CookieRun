#pragma once

class Button : public ImageRect
{
private:
    enum State
    {
        NORMAL, OVER, DOWN
    };

public:
    Button(wstring file);
    Button(Texture* texture);
    ~Button();

    void Update();
    void Render(HDC hdc);

    void SetFont(HFONT font, int fontSize = 20, COLORREF fontColor = BLACK);

    void SetLeftEvent(Event event) { this->leftClickEvent = event; }
    void SetRightEvent(Event event) { this->rightClickEvent = event; }

    void SetOverTexture(Texture* texture) { overTexture = texture; }
    void SetDownTexture(Texture* texture) { downTexture = texture; }

    void SetText(string text) { this->text = text; }

    void SetOffset(Vector2 offset) { this->offset = offset; }

protected:
    State state = NORMAL;

    bool isLClick = false;
    bool isRClick = false;

    Event leftClickEvent = nullptr;
    Event rightClickEvent = nullptr;

    Texture* normalTexture = nullptr;
    Texture* overTexture = nullptr;
    Texture* downTexture = nullptr;

    Vector2 normalSize;
    Vector2 overSize;
    Vector2 downSize;

    string text;

    HFONT font = nullptr, oldFont = nullptr;
    int fontSize = 20;
    COLORREF fontColor = BLACK;

    Vector2 offset = {};
};