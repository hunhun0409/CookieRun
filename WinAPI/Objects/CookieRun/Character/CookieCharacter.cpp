#include "Framework.h"

CookieCharacter::CookieCharacter(wstring file, int frameX, int frameY, COLORREF transColor)
{
    texture = Texture::Add(file, frameX, frameY, transColor);

    imageRect = new ImageRect(texture);

    Texture* frontTexture = Texture::Add(L"Textures/CookieRun/UI/HP_Front.bmp");
    Texture* backTexture = Texture::Add(L"Textures/CookieRun/UI/HP_Back.bmp");
    hpBar = new ProgressBar(frontTexture, backTexture);
    hpBar->SetValue(1.0f);
    hpBar->BackOffset() = {-26, 0};

    hpBar->pos = { CENTER_X + 60, 50 };

    tag = "Cookie";

    Observer::Get()->AddEvent("CookieCrash", bind(&CookieCharacter::Crash, this));
    Observer::Get()->AddEvent("CookieGrow", bind(&CookieCharacter::GiantStart, this));
    Observer::Get()->AddEvent("CookieDash", bind(&CookieCharacter::DashStart, this));
    Observer::Get()->AddEvent("BonusTimeStart", bind(&CookieCharacter::BonustimeStart, this));
    Observer::Get()->AddEvent("BonusTimeEnd", bind(&CookieCharacter::BonustimeEnd, this));

    Audio::Get()->Add("giant_jump", "Sounds/CookieRun/Cookie/HeroCookie/giant_jump.wav");
    Audio::Get()->Add("giant_land", "Sounds/CookieRun/Cookie/HeroCookie/giant_land.wav");
    Audio::Get()->Add("giant_end", "Sounds/CookieRun/giant_end.wav");
    Audio::Get()->Add("GameEnd", "Sounds/Cookierun/Cookie/GameEnd.wav");

}

CookieCharacter::CookieCharacter(Texture* texture)
{
    this->texture = texture;

    imageRect = new ImageRect(texture);

    Texture* frontTexture = Texture::Add(L"Textures/CookieRun/UI/HP_Front.bmp");
    Texture* backTexture = Texture::Add(L"Textures/CookieRun/UI/HP_Back.bmp");
    hpBar = new ProgressBar(frontTexture, backTexture);
    hpBar->SetValue(1.0f);
    hpBar->pos = { CENTER_X, 200 };

    tag = "Cookie";

    Observer::Get()->AddEvent("CookieCrash", bind(&CookieCharacter::Crash, this));
    Observer::Get()->AddEvent("CookieGrow", bind(&CookieCharacter::GiantStart, this));
    Observer::Get()->AddEvent("CookieDash", bind(&CookieCharacter::DashStart, this));

    Audio::Get()->Add("giant_jump", "Sounds/CookieRun/Cookie/HeroCookie/giant_jump.wav");
    Audio::Get()->Add("giant_land", "Sounds/CookieRun/Cookie/HeroCookie/giant_land.wav");
    Audio::Get()->Add("giant_end", "Sounds/CookieRun/giant_end.wav");
    Audio::Get()->Add("GameEnd", "Sounds/Cookierun/Cookie/GameEnd.wav");
}

CookieCharacter::~CookieCharacter()
{
    delete imageRect;
    delete hpBar;

    for (pair<CharacterState, Animation*> animation : animations)
        delete animation.second;
}

void CookieCharacter::Update()
{
    imageRect->pos = pos + imageOffset;
    
    if (animations.count(curState) > 0)
        animations[curState]->Update();
    if (isGhost)
    {
        ghostTime -= DELTA;
        if (ghostTime <= 0)
        {
            isGhost = false;
        }
    }
    if (isGiant)
    {
        GiantLoop();
    }
    if (isShrink)
    {
        GiantEnd();
    }
    if (isDash)
    {
        DashLoop();
    }
    if (isMoveTo)
    {
        MoveTo();
    }
    else
    {
        Control();
        Gravity();
        Move();
    }
    if (!BonusTimeManager::Get()->isBonusTime)
    {
        curHP -= 2 * DELTA;
        curHP = Clamp(0, maxHP, curHP);
        hpBar->SetValue(curHP / maxHP);
    }
}

void CookieCharacter::Render(HDC hdc)
{
    if (KEY_DOWN(VK_TAB))
    {
        DebugMode = !DebugMode;
    }
    if(DebugMode)
        Rect::CamLineRender(hdc);

    if (animations.count(curState) == 0)
    {
        imageRect->CamRender(hdc);
        return;
    }

    imageRect->CamRender(hdc, animations[curState]->GetFrame());

    hpBar->Render(hdc);
}

void CookieCharacter::Render(HDC hdc, int alpha)
{
    Rect::CamLineRender(hdc);

    if (animations.count(curState) == 0)
    {
        imageRect->CamRender(hdc);
        return;
    }

    imageRect->CamRender(hdc, alpha, animations[curState]->GetFrame());
    hpBar->Render(hdc);
}

void CookieCharacter::MoveTo()
{
    pos.y = Lerp(pos.y, destHeight, moveToSpeed * DELTA);
    if (Vector2(0, pos.y-destHeight).Length() < 20.0f)
    {
        isMoveTo = false;
        destHeight = 0;
    }
}

void CookieCharacter::Gravity()
{
    Vector2 bottomPos;
    bottomPos.x = pos.x;
    bottomPos.y = Bottom() - BOTTOM_CHECK;
    float groundHeight = StageManager::Get()->GetGroundHeight(bottomPos);

    velocity.y -= GRAVITY * DELTA;
    velocity.y = Clamp(-1000, 2000, velocity.y);
    if (isFly) //날고있나?
    {
        velocity.y = Clamp(-300, 300, velocity.y);

        pos.y -= velocity.y * DELTA;

        pos.y = Clamp(Half().y, 560 - Half().y, pos.y);
    }

    else
    {
        if (Bottom() >= groundHeight)//착지
        {
            if (velocity.y < 0)
            {
                velocity.y = 0.0f;
                jumpCount = 0;
                pos.y = groundHeight - Half().y;
                Land();
            }
        }
        pos.y -= velocity.y * DELTA;
        if (isDash)
        {
            pos.y = Clamp(Half().y, 560 - Half().y, pos.y);
        }

        if (pos.y > WIN_HEIGHT + Half().y + 200)
        {
            if (curState == BONUSTIME_END) return;

            Dead();
        }
    }
}

void CookieCharacter::Control()
{
    if (IsDead()) return;

    if (isFly)
    {
        if (KEY_PRESS(VK_UP))
        {
            velocity.y = JUMP_POWER;
        }
        if (KEY_UP(VK_UP))
        {
            velocity.y = 0;
        }
        velocity.y = Clamp(-300, 300, velocity.y);

    }
    else
    {
        Jump();
        Slide();
    }
    
}

void CookieCharacter::Move()
{
    if (IsDead()) return;
    velocity.x += 500 * DELTA;
    velocity.x = Clamp(0, maxSpeed, velocity.x);
    pos.x += velocity.x * DELTA;
}

void CookieCharacter::Run()
{
    if (curState == CRASH) return;
    if (IsDead()) return;
    if (isSkill)
    {
        SetAction(SKILL_LOOP);
    }
    if (isDash)
    {
        SetAction(DASH);

    }
    else
    {
        SetAction(RUN);

    }
}


void CookieCharacter::Slide()
{
    if (IsDead()) return;
    if (curState == CRASH) return;
    if (KEY_PRESS(VK_DOWN))
    {
        SetAction(SLIDE);
        float y = crouchSize.y - size.y;
        size.y += y;
        pos.y -= y * 0.5f;
        imageOffset.y += y * 0.5f;

    }
    if (KEY_UP(VK_DOWN))
    {
        SetAction(RUN);
        float y = standSize.y - crouchSize.y;
        size.y += y;
        pos.y -= y * 0.5f;
        imageOffset.y += y * 0.5f;

        
        //size = standSize;
        //imageOffset.y /= 1.3f;
        //pos.y -= crouchSize.y / 2;

        //pos.y -= increaseHeight;
    }
}

void CookieCharacter::Jump()
{
    if (IsDead()) return;
    if (jumpCount < 2 && KEY_DOWN(VK_UP))
    {
        if (isGiant)
            Audio::Get()->Play("giant_jump", 0.5f);

        velocity.y = JUMP_POWER;
        jumpCount++;

        if (jumpCount >= 2)
        {
            SetAction(JUMP2_START);
        }
        else
        {
            SetAction(JUMP1);
        }
    }
}

void CookieCharacter::JumpLoop()
{
    if (IsDead()) return;
    if (curState == CRASH) return;

    SetAction(JUMP2_LOOP);
}

void CookieCharacter::Land()
{
    if (IsDead()) return;
    if (curState == JUMP2_LOOP || curState == BONUSTIME_END)
    {
        if (isGiant)
        {
            Audio::Get()->Play("giant_land", 0.5f);
            Camera::Get()->CameraShake();
        }
        
        if (curState == BONUSTIME_END)
        {
            EffectManager::Get()->Play("HeroChangeEffect", pos);
        }
        SetAction(JUMP2_END);
    }
}

void CookieCharacter::Crash()
{
    if (IsDead()) return;
    if (isGhost) return;
    if (IsDead()) return;

    isGhost = true;
    ghostTime = GHOST_TIME;
    curHP -= 10;
    velocity.x = RUN_SPEED*0.5f;
    if (curHP > 0)
    {
        SetAction(CRASH);
        Audio::Get()->Play("CrashObstacle", 0.5f);
        Camera::Get()->CameraShake();
    }
    else
        Dead();
}

void CookieCharacter::EndCrash()
{
    SetAction(RUN);
}

void CookieCharacter::Exhaust()
{
    Audio::Get()->Stop("HeroBGM");
    Audio::Get()->Play("GameEnd");
    SetAction(EXHAUST);
}

void CookieCharacter::Dead()
{
    if (IsDead()) return;
    Audio::Get()->Stop("HeroBGM");
    Audio::Get()->Play("GameEnd");

    curHP = 0;
    SetAction(DEAD);
}

void CookieCharacter::GiantStart()
{
    if (IsDead()) return;
    isInvincible = true;
    isGiant = true;
    isShrink = false;
    giantTime = GIANT_TIME;
}

void CookieCharacter::GiantLoop()
{
    giantTime -= DELTA;
    pSize += DELTA;
    pSize = Clamp(0.0f, 1.0f, pSize);

    if (curState == SLIDE)
    {
        size = Lerp(crouchNormalSize, crouchGiantSize, pSize);
        imageOffset.y = -crouchSize.y * 2.1f;
    }
    else
    {
        size = Lerp(normalSize, giantSize, pSize);
        imageOffset.y = -standSize.y * 0.8f;
    }
    standSize = Lerp(normalSize, giantSize, pSize);
    crouchSize = Lerp(crouchNormalSize, crouchGiantSize, pSize);
    imageRect->size = Lerp(imageNormalSize, imageGiantSize, pSize);

    if (giantTime <= 0)
    {
        isGiant = false;
        isShrink = true;
        giantTime = GIANT_TIME;
        Audio::Get()->Play("giant_end", 0.5f);
    }
}

void CookieCharacter::GiantEnd()
{
    pSize -= DELTA;
    pSize = Clamp(0.0f, 1.0f, pSize);


    if (curState == SLIDE)
    {
        size = Lerp(crouchNormalSize, crouchGiantSize, pSize);
        imageOffset.y = -crouchSize.y * 2.1f;
    }
    else
    {
        size = Lerp(normalSize, giantSize, pSize);
        imageOffset.y = -standSize.y * 0.8f;
    }
    standSize = Lerp(normalSize, giantSize, pSize);
    crouchSize = Lerp(crouchNormalSize, crouchGiantSize, pSize);
    imageRect->size = Lerp(imageNormalSize, imageGiantSize, pSize);

    if (pSize == 0)
    {
        isInvincible = false;
        isShrink = false;
        isGhost = true;
        ghostTime = GHOST_TIME;
    }
}

void CookieCharacter::DashStart()
{
    isInvincible = true;
    isDash = true;
    maxSpeed = DASH_SPEED;
    velocity.x = DASH_SPEED;
    if(!isSkill && curState != SKILL_END)
        SetAction(DASH);
}

void CookieCharacter::DashLoop()
{
    dashTime -= DELTA;
    if (dashTime <= 0)
    {
        dashTime = DASH_TIME;
        DashEnd();
    }
}

void CookieCharacter::DashEnd()
{
    if (!isSkill)
    {
        isInvincible = false;
        maxSpeed = RUN_SPEED;
        isGhost = true;
        ghostTime = GHOST_TIME;
    }
    
    isDash = false;
    
}

void CookieCharacter::BonustimeStart()
{
    SetMoveTo(CENTER_Y);

    velocity.x = 0;
    SetAction(BONUSTIME_START);
    isFly = true;
    isGhost = true;
    ghostTime = GHOST_TIME;
}

void CookieCharacter::BonustimeLoop()
{
    SetAction(BONUSTIME_LOOP);
}

void CookieCharacter::BonustimeEnd()
{
    velocity.x = 0;
    SetMoveTo(pos.y - 200);
    isFly = false;
    isGhost = true;
    ghostTime = GHOST_TIME;
    SetAction(BONUSTIME_END);
}


float CookieCharacter::GetHeight(const Vector2& pos)
{
    return StageManager::Get()->GetGroundHeight(pos);
}

void CookieCharacter::SetAction(CharacterState state)
{
    if (IsDead()) return;
    if (curState == state) return;

    curState = state;
    animations[state]->Play();
}

void CookieCharacter::SetMoveTo(float dest)
{
    isMoveTo = true;
    destHeight = dest;
    
}

void CookieCharacter::SetHealth(float changeAmount)
{
    curHP += changeAmount;
    curHP = Clamp(0, maxHP, curHP);
}