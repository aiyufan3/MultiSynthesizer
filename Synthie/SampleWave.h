#pragma once
#include "CAudioNode.h"
#include <vector>

class CSampleWave :
	public CAudioNode
{
public:
	CSampleWave();
	virtual ~CSampleWave();

	double GetWavetableSize() { return m_wavetable.size(); }
	double GetFreq() { return m_freq; }
	double GetAmp() { return m_amp; }
	double GetPhase() { return m_phase; }
	bool GetFilter() { return m_filter; }


	void SetFreq(double f) { m_freq = f; }
	void SetAmp(double a) { m_amp = a; }
	virtual void SetWavetables() = 0;

protected:
	std::vector<double> m_wavetable; 
	double m_freq; // frequency
	double m_amp;  // amplitude
	int m_phase;  // phase
	bool m_filter;  // filter
};

