#pragma once

class CookieRunScene : public Scene
{
public:
    CookieRunScene();
    ~CookieRunScene();
        
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    virtual void Start() override;
    virtual void End() override;

    void SetCookie(void* cookie);
private:
    /*Landscape* landscape;
    Cookie* cookie;*/

    ImageRect* land;
    ImageRect* backGround;

    CookieCharacter* cookie;

    Pet* pet;

    Vector2 oldStagePos;

};