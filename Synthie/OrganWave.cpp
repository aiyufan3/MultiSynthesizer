#include "pch.h"
#include "OrganWave.h"
#include <cmath>


using namespace std;

COrganWave::COrganWave()
{
	m_time = 0;
    
	m_vibratoFreq = 0;
	m_vibratoFlag = 0;
    
	m_leslieRadius = 0;
	m_leslieAttackTime = 0;
	m_leslieReleaseTime = 0;
	m_leslie_phase = 0;
	m_leslieStartFreq = 0;
	m_amp = 1.0;
    
	m_drawbars.resize(9, 0.0);
	m_drawbars[0] = 8.0;
    
    // toneweels of the Hammond  
	m_harmonics.resize(9, 0);
	m_harmonics[0] = 1;
	m_harmonics[1] = 3;
	m_harmonics[2] = 2;
	m_harmonics[3] = 4;
	m_harmonics[4] = 6;
	m_harmonics[5] = 8;
	m_harmonics[6] = 10;
	m_harmonics[7] = 12;
	m_harmonics[8] = 16;
}

COrganWave::~COrganWave()
{
}

void COrganWave::Start()
{
	m_phase = 0;
	m_vibrato_phase = 0;
}
bool COrganWave::Generate()
{
    // The vibrato magnitude 
    double vibMag = m_vibratoFlag * m_freq / 200.0;  
    double sampleSum = 0;

    // Accumulate samples from the tonewheels
    for (int i = 0; i < 9; ++i) {
        sampleSum += m_drawbars[i] * sin(m_phase * m_harmonics[i]);
    }

    // Smooth out
    double leslieEffect = 1 + (0.5 * m_leslieRadius * cos(m_leslie_phase) / 340.3);  

    // Adjust for vibrato effect
    double vibratoEffect = vibMag * sin(m_vibrato_phase);

    // Combine the effects
    double combinedSample = sampleSum * m_amp * leslieEffect * vibratoEffect;

    m_frame[0] = m_frame[1] = combinedSample;

    // Update the sound phase with vibrato effect 
    double freqUpdate = m_freq + vibratoEffect;
    if (freqUpdate > 800) {  
        freqUpdate = 800;
    }
    m_phase += 2 * PI * freqUpdate * GetSamplePeriod();

    // Update the vibrato phase
    m_vibrato_phase += 2 * PI * m_vibratoFreq * GetSamplePeriod();

    // Calculate Leslie modulation points
    double leslieAttackPoint = m_leslieAttackTime * GetSampleRate();
    double leslieReleasePoint = m_duration - m_leslieReleaseTime * GetSampleRate();

    // Adjust the Leslie phase based on the modulation points
    if (m_time < leslieAttackPoint && m_leslieChanged) {
        m_leslie_phase += 2 * PI * (m_leslieStartFreq + (m_leslieFreq - m_leslieStartFreq) * m_time / leslieAttackPoint) * GetSamplePeriod();
    }
    else if (m_time > leslieReleasePoint) {
        m_leslie_phase += 2 * PI * (m_leslieEndFreq + (m_leslieFreq - m_leslieEndFreq) * (m_duration - m_time) / (m_duration - leslieReleasePoint)) * GetSamplePeriod();
    }
    else {
        m_leslie_phase += 2 * PI * m_leslieFreq * GetSamplePeriod();
    }

    m_time++;

    return true;
}
