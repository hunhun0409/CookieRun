#include "Framework.h"

KumihoCookie::KumihoCookie()
	:CookieCharacter(L"Textures/CookieRun/Kumiho.bmp", 11, 5)
{
    size = { 120, 150 };
    imageOffset = { 0, -110 };

    CreateAnimation();
    animations[curState]->Play();
}

KumihoCookie::~KumihoCookie()
{
}

void KumihoCookie::Update()
{
    SetAnimation();
    CookieCharacter::Update();

}

void KumihoCookie::Render(HDC hdc)
{
    CookieCharacter::Render(hdc);
}

void KumihoCookie::Run()
{
    CookieCharacter::Run();
}

void KumihoCookie::JumpLoop()
{
    CookieCharacter::JumpLoop();
}

void KumihoCookie::CreateAnimation()
{
    animations[RUN] = new Animation(texture->GetFrame(), 1.2f);
    animations[RUN]->SetPart(11, 14, true);

    animations[JUMP1] = new Animation(texture->GetFrame(), 1.2f);
    animations[JUMP1]->SetPart(7, 8, true);

    animations[JUMP2_START] = new Animation(texture->GetFrame(), 1.2f);
    //animations[JUMP2_START]->SetPart(0, 4);
    int arr[] = { 0, 1, 2, 3, 4, 1, 2, 3, 4 };
    animations[JUMP2_START]->SetArray(arr, 9);
    animations[JUMP2_START]->SetEndEvent(bind(&KumihoCookie::JumpLoop, this));

    animations[JUMP2_LOOP] = new Animation(texture->GetFrame(), 1.2f);
    animations[JUMP2_LOOP]->SetPart(5, 5, true);

    int arr1[] = {6, 6};
    animations[JUMP2_END] = new Animation(texture->GetFrame(), 1.2f);
    //animations[JUMP2_END]->SetPart(6, 6);
    animations[JUMP2_END]->SetArray(arr1, 2);
    animations[JUMP2_END]->SetEndEvent(bind(&KumihoCookie::Run, this));

    animations[SLIDE] = new Animation(texture->GetFrame(), 1.2f);
    animations[SLIDE]->SetPart(9, 10, true);
    
    

    animations[CRASH] = new Animation(texture->GetFrame());
    animations[CRASH]->SetPart(43, 44, false, true);

    animations[EXHAUST] = new Animation(texture->GetFrame());
    animations[EXHAUST]->SetPart(49, 53);

    animations[DEAD] = new Animation(texture->GetFrame());
    animations[DEAD]->SetPart(43, 48);
}

void KumihoCookie::SetAnimation()
{
    if (curState == CRASH) return;
    if (IsDead()) return;
    
    if(velocity.y == 0)
    {
        if (curState == SLIDE || curState == JUMP2_END) return;
        SetAction(RUN);
    }
}

