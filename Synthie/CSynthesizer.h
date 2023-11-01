#pragma once

#include "msxml2.h"
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "CInstrument.h"
#include "CToneInstrument.h"
#include "CNote.h"
#include "AdditiveInstrument.h"
#include "SubtractiveInstrument.h"
#include "OrganFactory.h"
#include "ChorusEffect.h"
#include "FlangeEffect.h"
#include "CompressorEffect.h"
#include "NoiseGateEffect.h"
#include "ReverberationEffect.h"

using namespace std;

class CSynthesizer
{
public:
	CSynthesizer();
	virtual ~CSynthesizer();

public:
	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

	void Start();

	bool Generate(double * frame);

	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

	void Clear();

	void OpenScore(CString & filename);

	double GetBPM() { return m_bpm; }

	//Effect with dry/wet control
	enum Effect {
		None = 0,
		NoiseGating = 1 << 0,
		Chorus = 1 << 1,
		Compression = 1 << 2,
		Reverberation = 1 << 3,
		Flanging = 1 << 4   // extra point for flanging
	};
	void ToggleEffect(Effect effect);
	void SetEffectMix(Effect effect, double mix);
	bool IsEffectActive(Effect effect);
	void SetEffect(Effect effect);

private:
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double m_time;
	list<CInstrument *> m_instruments;
	double  m_bpm;                  //!< Beats per minute
	int     m_beatspermeasure;  //!< Beats per measure
	double  m_secperbeat;        //!< Seconds per beat
	vector<CNote> m_notes;
	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure
	COrganFactory m_organFactory;

private:
	void XmlLoadScore(IXMLDOMNode * xml);
	void XmlLoadInstrument(IXMLDOMNode * xml);
	void XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument);

private:

	int m_activeEffects = None;


	std::map<Effect, double> m_effectMixes;

	// Effects
	CChorusEffect mChorusEffect;
	CFlangeEffect mFlangeEffect;
	CCompressorEffect mCompressorEffect;
	CNoiseGateEffect mNoiseGateEffect;
	CReverbEffect mReverbEffect;
};

#pragma comment(lib, "msxml2.lib")