#include "Framework.h"

Timer::Timer()
{
    //1초동안 CPU진동수를 반환하는 함수
    QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

    //현재 CPU진동수를 반환하는 함수
    QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

    timeScale = 1.0f / (float)periodFrequency;
}

Timer::~Timer()
{
}

void Timer::Update()
{
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    elapsedTime = (float)(curTime - lastTime) * timeScale;

    if (lockFPS != 0)
    {
        while (elapsedTime < (1.0f / lockFPS))
        {
            QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
            elapsedTime = (float)(curTime - lastTime) * timeScale;
        }
    }

    lastTime = curTime;

    frameCount++;
    oneSecCount += elapsedTime;

    if (oneSecCount >= 1.0f)
    {
        frameRate = frameCount;
        frameCount = 0;
        oneSecCount = 0.0f;
    }    
}

void Timer::Render(HDC hdc)
{
    wstring str = L"FPS : " + to_wstring(frameRate);
    TextOut(hdc, 0, 0, str.c_str(), (int)str.length());
    str = L"Delta : " + to_wstring(elapsedTime);
    TextOut(hdc, 0, 20, str.c_str(), (int)str.length());
}
