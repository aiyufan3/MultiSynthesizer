#pragma once
#include "CInstrument.h"
#include "Notes.h"
#include "CAR.h"
#include <vector>
#include "OrganEnvelope.h"
#include "OrganWave.h"

using namespace std;

class COrganInstrument :
	public CInstrument
{
public:
	COrganInstrument();
	COrganInstrument(double bpm);
	virtual ~COrganInstrument();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();
	
	// Setters
	void SetLeslieAttackTime(double attack);
	void SetLeslieStartFreq(double startTime) { m_organWave.SetLeslieStartFreq(startTime); }
	void SetLeslieEndFreq(double endTime) { m_organWave.SetLeslieEndFreq(endTime); }
	void SetLeslieReleaseTime(double releaseTime) { m_organWave.SetLeslieReleaseTime(releaseTime); }
	void SetLeslieChanged(bool isChanged) { m_organWave.SetLeslieChanged(isChanged); }
	void SetLeslieRadius(double radius) { m_organWave.SetLeslieRadius(radius); }
	void SetLeslieFreq(double frequency) { m_organWave.SetLeslieFreq(frequency); }
	void SetWaveDrawbars(vector<double> drawbars) { m_organWave.SetDrawbars(drawbars); }
	void SetVibratoFreq(double m_freq) { m_organWave.SetVibratoFreq(m_freq); }
	void SetVibratoFlag(double flag) { m_organWave.SetVibratoFlag(flag); }
	void SetFreq(double flag) { m_organWave.SetFreq(flag); }
	void SetAmplitude(double amplitude) { m_organWave.SetAmplitude(amplitude); }
	void SetDuration(double duration) { m_envelope.SetDuration(duration); m_organWave.SetDuration(duration); }
	virtual void SetNote(CNote* note);
	void COrganInstrument::SetOrganDrawbars(int drawbarNum);

	// Get frame return to audio
	double GetFrame(int i) { return m_frame[i]; }


private:
	COrganWave m_organWave;
	double m_duration;
	double m_time;
	CAR m_ar;

	COrganEnvelope m_envelope;
	vector<double> m_drawbars;
	bool m_leslieChanged;
};

