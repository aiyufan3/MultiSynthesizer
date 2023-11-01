#include "pch.h"
#include "OrganEnvelope.h"

COrganEnvelope::COrganEnvelope(void)
{
	m_attack = 0.05;
	m_decay = 0.05;
	m_release = 0.01;
	m_duration = 0.1;
	m_source = NULL;
}

COrganEnvelope::~COrganEnvelope(void)
{
}

void COrganEnvelope::Start()
{
	m_time = 0;
}

bool COrganEnvelope::Generate()
{
    double gain = 1.0;

    // Determine the gain based on the current time
    if (m_time < m_attack) {
        // Linearly increase gain during the attack phase
        gain = m_time / m_attack;
    }
    else if (m_time < m_attack + m_decay) {
        // Linearly decrease gain during the decay phase
        double decayProgress = (m_time - m_attack) / m_decay;
        gain = 1.0 - decayProgress;
    }
    else if (m_time > m_duration - m_release) {
        // Linearly decrease gain during the release phase
        double releaseProgress = (m_time - (m_duration - m_release)) / m_release;
        gain = 1.0 - releaseProgress;
    }

    // If the envelope has completed its duration
    if (m_time >= m_duration) {
        m_frame[0] = m_frame[1] = 0;
        return false;
    }

    // Apply the gain to the source frames
    if (m_source) {
        m_frame[0] = m_source->Frame(0) * gain;
        m_frame[1] = m_source->Frame(1) * gain;
    }

    m_time += GetSamplePeriod();
    return true;
}