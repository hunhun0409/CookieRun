#include "Framework.h"

UINT Animation::FramePerSecond = 10;

Animation::Animation(POINT imageFrame, float speed)
    : imageFrame(imageFrame), speed(speed)
{
    intervalTime = 1.0f / FRAME_PER_SECOND;

    frames.reserve(imageFrame.x * imageFrame.y);
    for (int y = 0; y < imageFrame.y; y++)
    {
        for (int x = 0; x < imageFrame.x; x++)
        {
            frames.push_back({ x, y });
        }
    }
}

void Animation::Update()
{
    if (!isPlay) return;

    playTime += speed * DELTA;

    intervalTime = 1.0f / FramePerSecond;

    if (playTime >= intervalTime)
    {
        playTime -= intervalTime;

        if (!notifies.empty())
        {
            for (Notify notify : notifies)
            {
                if (notify.idx > curFrameNum)
                {
                    break;
                }
                else if (notify.idx < curFrameNum)
                {
                    continue;
                }
                else
                {
                    notifyEvent(notify.name);
                }
            }
        }

        curFrameNum++;

        if (curFrameNum > action.size() - 1)
        {
            if (isLoop)
                curFrameNum = 0;
            else
            {
                curFrameNum--;
                Stop();
            }
        }
    }
}

void Animation::SetDefault(bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (UINT i = 0; i < frames.size(); i++)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (UINT i = start; i <= end; i++)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetArray(int* arr, int arrSize, bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (UINT i = 0; i < arrSize; i++)
        action.push_back(arr[i]);

    if (pingpong)
        SetPingpong();
}

void Animation::SetPingpong()
{
    for (int i = action.size() - 2; i >= 0; i--)
        action.push_back(action[i]);
}

void Animation::Stop()
{
    isPlay = false;

    if (endEvent)
        endEvent();
}

void Animation::SetNotifyEvent(function<void(string)> event, UINT idx, string name)
{
    notifyEvent = event;
    Notify notify = { idx, name };
    notifies.push_back(notify);

    sort(notifies.begin(), notifies.end(), compareByIndex);
}
