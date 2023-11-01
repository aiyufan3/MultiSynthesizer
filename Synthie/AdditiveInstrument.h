#pragma once
#include "CInstrument.h"
#include "AdditiveWave.h"

#include <list>

using namespace std;

class CAdditiveInstrument :
	public CInstrument
{
public:
	CAdditiveInstrument();
	virtual ~CAdditiveInstrument();
	CAdditiveInstrument(double bpm);

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note) override;

	// used for cross fading
	void SetNextNote(CNote* next_note);
	void AddHarmonics(std::wstring harmonics);

	void SetFreq(double freq) { m_additive_wave.SetFreq(freq); }
	void SetAmplitude(double amp) { m_additive_wave.SetAmp(amp); }
	void SetDuration(double duration) { m_timeSpan = duration; }

private:
	double m_timeSpan;
	double m_currentTime;
	double m_fadeDuration = 0;
	CAdditiveWave m_additive_wave;
	CAdditiveInstrument* m_next = nullptr;
};

