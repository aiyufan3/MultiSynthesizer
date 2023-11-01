#include "pch.h"
#include "SubtractiveWave.h"
#include <cmath>

CSubtractiveWave::CSubtractiveWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


CSubtractiveWave::~CSubtractiveWave()
{
}

void CSubtractiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}

bool CSubtractiveWave::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];
	
	// set phase
	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}
//similar setting in additive
void CSubtractiveWave::SetWavetables()
{
    double table_size = GetSampleRate();
    m_wavetable.resize(table_size);
    double amplitudeFilter = 1.0 - 0.05 * ((m_freq - 1000.) / 44100.);

    double setFreq = m_freq;
    double freqDelta = 440. / table_size;
    for (auto i = 0; i < table_size; i++, m_time += 1. / GetSampleRate()) {
        double sample = 0.0;

        if (m_down || (m_back_up && i < table_size / 2) || (m_back_down && i >= table_size / 2)) {
            setFreq -= freqDelta;
        }
        else {
            setFreq += freqDelta;
        }

        if (m_wave_type == L"Sawtooth") {
            sample = amplitudeFilter * m_amp * sin(m_time * 2 * PI * setFreq);
        }
        else if (m_wave_type == L"Square") {
            sample = amplitudeFilter * m_amp * (sin(m_time * 2 * PI * setFreq) > 0 ? 1 : -1);
        }
        else if (m_wave_type == L"Triangle") {
            sample = amplitudeFilter * m_amp * asin(sin(m_time * 2 * PI * setFreq));
        }

        if (m_reson && i > 1) {
            ImplementReson(&sample, i);
        }

        m_wavetable[i] = sample;
    }
}
//Reson Implementation
void CSubtractiveWave::ImplementReson(double* sample, int tableIndex)
{
    double R = 1.0 - (m_reson_bandwidth / 2.0);
    double cosTheta = (2 * R * cos(2 * PI * m_reson_freq)) / (1 + pow(R, 2));
    double A = (1 - pow(R, 2)) * sqrt(1 - pow(cosTheta, 2));

    int prevIndex = (tableIndex - 1 + m_wavetable.size()) % m_wavetable.size();
    int secondPrevIndex = (tableIndex - 2 + m_wavetable.size()) % m_wavetable.size();

    *sample = A * *sample + (2 * R * cosTheta) * m_wavetable[prevIndex] - pow(R, 2) * m_wavetable[secondPrevIndex];
}