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
    //void ������ : � �ڷ������� �������� �ʾ��� �� ����ϴ� ������
    typedef vector<ParamEvent> ParamEvents;
    typedef vector<Event> Events;

    map<string, Events> totalEvent;
    map<string, ParamEvents> totalParamEvent;
};