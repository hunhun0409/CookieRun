#pragma once

class GameManager : public Singleton<GameManager>
{
private:
    friend class Singleton;

    GameManager();
    ~GameManager();

public:
    void Init();

    void Update();
    void Render();    

private:
    static GameManager* instance;

    HDC hdc = nullptr;

    HDC hBackDC = nullptr;
    HBITMAP hBackBitmap = nullptr;
};