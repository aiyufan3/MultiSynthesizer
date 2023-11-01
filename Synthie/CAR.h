#pragma once
#include "CAudioNode.h"

class CAR :
    public CAudioNode
{
public:
    CAR(void);

    virtual void Start();
    virtual bool Generate();

    void SetAttack(double attack) { m_attack = attack; }
    void SetRelease(double release) { m_release = release; }
    void SetDuration(double duration) { m_duration = duration; }
    void SetSource(CAudioNode* source) { m_source = source; }

private:
    // The audio source
    CAudioNode* m_source;

    double m_attack;
    double m_release;
    double m_duration;
    double m_time;
};