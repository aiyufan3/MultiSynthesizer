#pragma once
#include "SampleWave.h"
using namespace std;

class CSubtractiveWave :
	public CSampleWave
{
public:
	CSubtractiveWave();
	~CSubtractiveWave();

	void Start();
	bool Generate();

	void ImplementReson(double* sample, int tableIndex);

	//Setters for each components
	void SetWaveType(CStringW type){ m_wave_type = type; }
	void SetReson(bool reson){ m_reson = reson; }
	void SetResonFreq(double freq){ m_reson_freq = freq; }
	void SetResonBandwidth(double band){ m_reson_bandwidth = band; }
	void SetSweepDown(bool flag){ m_down = flag; }
	void SetSweepUp(bool flag){ m_up = flag; }
	void SetSweepBackUp(bool flag){ m_back_up = flag; }
	void SetSweepBackDown(bool flag){ m_back_down = flag; }
	void SetWavetables();

private:
	//  square, sawtooth, triange
	CStringW m_wave_type; 
	double m_time;
	bool m_reson = false;
	double m_reson_freq = 0.01134;
	double m_reson_bandwidth = 0.01;
	double m_sweep_freq = 0.0;
	// a frequency sweep for play some frame
	bool m_down = false;
	bool m_up = false;
	bool m_back_up = false;
	bool m_back_down = false;
};

