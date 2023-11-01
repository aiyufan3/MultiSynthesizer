#pragma once
#include "SampleWave.h"

using namespace std;

class CAdditiveWave :
	public CSampleWave
{
public:
	CAdditiveWave();
	virtual ~CAdditiveWave();

	// implementing the Vibrato effect
	struct Vibrato
	{
		double vibrato = 0;
		double vibrato_rate = 0;
	};

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetWavetables() override;

	void AddHarmonic(double harmonic) { m_harmonics.push_back(harmonic); }
	void ImplementHarmonics(double* sample, double time);
	void ImplementVibrato(double* sine_rads, double* vibrato_rads);
	void GenerateCrossfade(double time, double crossfade_dur);

	vector<double> GetHarmonics() { return m_harmonics; }
	bool GetVibratoFlag() { return m_vibrato; }
	bool GetCrossfadeActive(){ return m_crossfade; }
	double GetCrossfadeStartTime() { return m_crossfade_start_time; }

	// Set the cross-fade implementation
	void SetCrossfadeActive(bool flag) { m_crossfade = flag; }
	void SetCrossfadeStartTime(double time) { m_crossfade_start_time = time; }
	//	Vibrato flag to determine if vibrato should be applied
	void SetVibratoFlag(bool flag) { m_vibrato = flag; }
	//	Set the depth or magnitude of the vibrato effect
	void SetVibrato(double vibrato) { m_vibrato_effect.vibrato = vibrato; }
	//	Set the rate at which the vibrato oscillates
	void SetVibratoRate(double vibrato_rate) { m_vibrato_effect.vibrato_rate = vibrato_rate; }
	//	Set the next wave object
	void SetNextWave(CAdditiveWave* next) { m_next_wave = next; }

private:
	vector<double> m_harmonics;
	double m_time;
	bool m_vibrato = false;
	bool m_crossfade = false;
	double m_crossfade_start_time;
	Vibrato m_vibrato_effect;
	CAdditiveWave* m_next_wave = nullptr;
};

