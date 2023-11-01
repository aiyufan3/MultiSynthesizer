#include "pch.h"
#include "CAR.h"
#include <cmath>

CAR::CAR(void) 
{
    m_time = 0;
    m_attack = 0.05;
    m_release = 0.05;
    m_duration = 0.1;
}

void CAR::Start()
{
    m_time = 0;
}

bool CAR::Generate()
{
    if (!m_source)
        return false; // No source connected

    m_source->Generate();

    double sample[2];
    sample[0] = m_source->Frame(0);
    sample[1] = m_source->Frame(1);

    double envelope = 1.0;

    if (m_time < m_attack)
    {
        envelope = m_time / m_attack;  // attack
    }
    else if (m_time > m_duration - m_release)
    {
        envelope = (m_duration - m_time) / m_release;  // release
    }

    m_frame[0] = sample[0] * envelope;
    m_frame[1] = sample[1] * envelope;

    m_time += GetSamplePeriod();

    return m_time < m_duration;
}