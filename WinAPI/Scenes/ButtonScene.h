#pragma once

class ButtonScene : public Scene
{
public:
    ButtonScene();
    ~ButtonScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void StartBattleScene();
    void StartDigScene();

    void LoadFile();

    void LoadFolder();

private:
    HFONT hFont;

    Button* battleButton;
    Button* digButton;

    Pet* pet;
};