#include "Framework.h"

HeroCookie::HeroCookie()
	:CookieCharacter(L"Textures/CookieRun/Cookies/Hero.bmp", 10, 8)
{
    size = { 80, 140 };
    imageOffset = { 5, -size.y * 0.8f };

    standSize = size;
    crouchSize = { size.x, size.y / 2 };

    normalSize = size;
    giantSize = size * 2;

    crouchNormalSize = crouchSize;
    crouchGiantSize = crouchSize * 2;

    imageNormalSize = texture->GetSize();
    imageGiantSize = imageNormalSize * 2;

    Texture* back = Texture::Add(L"Textures/CookieRun/UI/skillGaugeBack.bmp");
    Texture* front = Texture::Add(L"Textures/CookieRun/UI/skillGaugeFront.bmp");

    skillGauge = new ProgressBar(front, back);


    Audio::Get()->Add("hero_jump", "Sounds/CookieRun/Cookie/HeroCookie/hero_jump.wav");
    Audio::Get()->Add("hero_slide", "Sounds/CookieRun/Cookie/HeroCookie/hero_slide.wav");

    Audio::Get()->Add("transform_start", "Sounds/CookieRun/Cookie/HeroCookie/transform_start.wav");
    Audio::Get()->Add("transform_end", "Sounds/CookieRun/Cookie/HeroCookie/transform_end.wav");
    Audio::Get()->Add("transform_flight", "Sounds/CookieRun/Cookie/HeroCookie/transform_flight.wav");
    Audio::Get()->Add("transform_boost", "Sounds/CookieRun/Cookie/HeroCookie/transform_boost.wav");

    Texture* texture = Texture::Add(L"Textures/CookieRun/Effects/HeroChangeEffect.bmp", 5, 1);
    EffectManager::Get()->Add("HeroChangeEffect", 1, texture);



    CreateAnimation();
    animations[curState]->Play();
}

HeroCookie::~HeroCookie()
{
}

void HeroCookie::Update()
{
    CookieCharacter::Update();

    skillGauge->pos = pos - Camera::Get()->GetPos();
    skillGauge->pos.y = pos.y - size.y * 0.8f;
    skillGauge->SetValue(cooldown / SKILL_COOLDOWN);

    if (IsDead()) return;
    if (BonusTimeManager::Get()->isBonusTime) return;

    cooldown += DELTA;

    if (cooldown >= SKILL_COOLDOWN && !isSkill)//스킬 쿨타임이 0이되면 스킬발동
        SkillStart();

    if (isSkill)
    {
        if (!Audio::Get()->IsPlaySound("transform_boost"))
            Audio::Get()->Play("transform_boost", 0.5f);

        duration -= DELTA;
        cooldown -= (1 + SKILL_COOLDOWN / SKILL_DURATION) * DELTA;
        if (cooldown <= 0)//지속시간이 0이 되면 스킬 취소
        {
            Audio::Get()->Play("transform_end", 0.5f);
            SetAction(SKILL_END);
            isSkill = false;
        }
    }
    SetAnimation();

}

void HeroCookie::Render(HDC hdc)
{
    CookieCharacter::Render(hdc);
    skillGauge->Render(hdc);
}

void HeroCookie::Render(HDC hdc, int alpha)
{
    CookieCharacter::Render(hdc, alpha);

}

void HeroCookie::Run()
{
    CookieCharacter::Run();
}

void HeroCookie::SkillStart()
{
    isFly = true;
    isSkill = true;
    isInvincible = true;

    //velocity.y = 10*JUMP_POWER;
    SetMoveTo(CENTER_Y);
    
    Audio::Get()->Play("transform_start", 0.5f);
    EffectManager::Get()->Play("HeroChangeEffect", pos);
    SetAction(SKILL_START);
}

void HeroCookie::SkillLoop()
{
    Audio::Get()->Play("transform_flight", 0.5f);

    maxSpeed = DASH_SPEED;
    velocity.x = DASH_SPEED;

    SetAction(SKILL_LOOP);
}

void HeroCookie::SkillEnd()
{
    if (!isDash)
    {
        isInvincible = false;
        velocity.y = 0;
        maxSpeed = RUN_SPEED;
        SetAction(RUN);
    }
    else
    {
        SetAction(DASH);
    }
    isFly = false;
    cooldown = 0;
    duration = SKILL_DURATION;
    isGhost = true;
    ghostTime = GHOST_TIME;
}


void HeroCookie::Jump()
{
    if (IsDead()) return;
    if (jumpCount < 2 && KEY_DOWN(VK_UP))
    {
        if(!isGiant)
            Audio::Get()->Play("hero_jump", 0.5f);
    }
    CookieCharacter::Jump();
    
}

void HeroCookie::JumpLoop()
{
    CookieCharacter::JumpLoop();
}

void HeroCookie::Slide()
{
    if (IsDead()) return;
    if (KEY_DOWN(VK_DOWN))
    {
        Audio::Get()->Play("hero_slide", 0.5f);

    }
    CookieCharacter::Slide();
    
}

void HeroCookie::CreateAnimation()
{
    animations[RUN] = new Animation(texture->GetFrame(), 1.2f);
    animations[RUN]->SetPart(13, 16, true);

    animations[DASH] = new Animation(texture->GetFrame(), 1.2f);
    animations[DASH]->SetPart(17, 20, true);

    animations[JUMP1] = new Animation(texture->GetFrame(), 1.2f);
    animations[JUMP1]->SetPart(7, 8, true);

    animations[JUMP2_START] = new Animation(texture->GetFrame(), 1.2f);
    //animations[JUMP2_START]->SetPart(0, 4);
    int arr[] = { 0, 1, 2, 3, 1, 2, 3, 4 };
    animations[JUMP2_START]->SetArray(arr, 8);
    animations[JUMP2_START]->SetEndEvent(bind(&HeroCookie::JumpLoop, this));

    animations[JUMP2_LOOP] = new Animation(texture->GetFrame(), 1.2f);
    animations[JUMP2_LOOP]->SetPart(5, 5, true);

    int arr1[] = { 6, 6 };
    animations[JUMP2_END] = new Animation(texture->GetFrame(), 1.2f);
    //animations[JUMP2_END]->SetPart(6, 6);
    animations[JUMP2_END]->SetArray(arr1, 2);
    animations[JUMP2_END]->SetEndEvent(bind(&HeroCookie::Run, this));

    animations[SLIDE] = new Animation(texture->GetFrame(), 1.2f);
    animations[SLIDE]->SetPart(9, 10, true);

    animations[SKILL_START] = new Animation(texture->GetFrame(), 1.0f);
    animations[SKILL_START]->SetPart(55, 64);
    animations[SKILL_START]->SetEndEvent(bind(&HeroCookie::SkillLoop, this));

    animations[SKILL_LOOP] = new Animation(texture->GetFrame(), 1.2f);
    animations[SKILL_LOOP]->SetPart(65, 68, true);

    animations[SKILL_END] = new Animation(texture->GetFrame(), 1.0f);
    animations[SKILL_END]->SetPart(69, 71);
    animations[SKILL_END]->SetEndEvent(bind(&HeroCookie::SkillEnd, this));

    animations[BONUSTIME_START] = new Animation(texture->GetFrame(), 1.0f);
    int arr2[] = { 21, 22, 23, 24, 25, 26, 23, 24, 25, 26, 27, 28, 29 };
    animations[BONUSTIME_START]->SetArray(arr2, 13);
    animations[BONUSTIME_START]->SetEndEvent(bind(&HeroCookie::BonustimeLoop, this));

    animations[BONUSTIME_LOOP] = new Animation(texture->GetFrame(), 1.0f);
    animations[BONUSTIME_LOOP]->SetPart(30, 38, true);
    
    animations[BONUSTIME_LOOP_UP] = new Animation(texture->GetFrame(), 1.0f);
    animations[BONUSTIME_LOOP_UP]->SetPart(39, 41, true);

    animations[BONUSTIME_END] = new Animation(texture->GetFrame(), 0.5f);
    animations[BONUSTIME_END]->SetPart(42, 44);

    animations[CRASH] = new Animation(texture->GetFrame());
    int arr3[] = { 45, 45 };
    animations[CRASH]->SetArray(arr3, 2);
    animations[CRASH]->SetEndEvent(bind(&HeroCookie::EndCrash, this));


    animations[EXHAUST] = new Animation(texture->GetFrame());
    animations[EXHAUST]->SetPart(50, 54);

    animations[DEAD] = new Animation(texture->GetFrame());
    animations[DEAD]->SetPart(45, 49);
}

void HeroCookie::SetAnimation()
{
    if (IsDead()) return;
    if (curHP <= 0)
    {
        Exhaust();
    }
    if (curState == CRASH) return;

    if (isSkill || curState == SKILL_END)
    {
        return;
    }
    if (velocity.y == 0)
    {
        if (curState == SLIDE || curState == JUMP2_END) return;
        Run();
    }

    
}
