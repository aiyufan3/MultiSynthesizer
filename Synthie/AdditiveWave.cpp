#include "pch.h"
#include "AdditiveWave.h"
#include <cmath>


CAdditiveWave::CAdditiveWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


CAdditiveWave::~CAdditiveWave()
{
}


void CAdditiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}


bool CAdditiveWave::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];

	// set phase
	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}


void CAdditiveWave::SetWavetables()
{
	// set the table size to the sample rate
	double table_size = GetSampleRate();
	m_wavetable.resize(table_size);

	double sine_rads = 0;
	double vibrato_rads = 0;

	for (auto i = 0; i < table_size; i++, m_time += 1. / GetSampleRate())
	{
		auto sample = sin(sine_rads) * m_amp;

		if (m_harmonics.size() > 0)
		{
			ImplementHarmonics(&sample, m_time);
		}

		if (m_vibrato)
		{
			ImplementVibrato(&sine_rads, &vibrato_rads);
		}

		m_wavetable[i] = sample;
	}
}


void CAdditiveWave::ImplementHarmonics(double* sample, double time)
{
	auto nyquist_freq = GetSampleRate() / 2;

	for (auto x = 0; x < m_harmonics.size() && (m_freq * (x + 1)) < nyquist_freq; x++)
	{
		auto harmonic = x + 1;

		*sample += m_harmonics[x] * (m_amp / harmonic) * (sin(time * 2 * PI * harmonic * m_freq));
	}
}


void CAdditiveWave::ImplementVibrato(double* sine_rads, double* vibrato_rads)
{
	double diff = sin(*vibrato_rads) * m_vibrato_effect.vibrato;

	*sine_rads += (2 * PI * (m_freq + diff)) / m_sampleRate;
	*vibrato_rads += (2 * PI * m_vibrato_effect.vibrato_rate) / m_sampleRate;
}

void CAdditiveWave::GenerateCrossfade(double time, double crossfade_dur)
{
	auto elapsed_time = time - m_crossfade_start_time;

	if (m_next_wave && m_phase < m_next_wave->GetWavetableSize() && m_phase < GetWavetableSize())
	{
		double weight_current = (crossfade_dur - elapsed_time) / crossfade_dur;
		double weight_next = elapsed_time / crossfade_dur;

		m_frame[0] = m_frame[1] = m_wavetable[m_phase] * weight_current + m_next_wave->m_wavetable[m_phase] * weight_next;
	}
	else
	{
		m_frame[0] = m_frame[1] = m_wavetable[m_phase];
	}

	m_phase = (m_phase + 1) % m_wavetable.size();
}