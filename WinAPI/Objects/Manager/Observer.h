#pragma once

class Observer : public Singleton<Observer>
{
private:
    friend class Singleton;

    Observer() = default;
    ~Observer() = default;

public:
    void AddEvent(string key, Event event);
    void AddParamEvent(string key, ParamEvent event);

    void ExcuteEvents(string key);
    void ExcuteParamEvents(string key, void* object);

private:
    //void 포인터 : 어떤 자료형인지 정해지지 않았을 때 사용하는 포인터
    typedef vector<ParamEvent> ParamEvents;
    typedef vector<Event> Events;

    map<string, Events> totalEvent;
    map<string, ParamEvents> totalParamEvent;
};