
// SynthieView.h : interface of the CSynthieView class
//


#pragma once

#include "Progress.h"
#include "CSynthesizer.h"
#include "audio/wave.h"
#include "audio/DirSoundStream.h"	// Added by ClassView
#include "audio/WaveformBuffer.h"
#include "map"


// CSynthieView window

class CSynthieView : public CWnd, private CProgress
{
// Construction
public:
	CSynthieView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CSynthieView();

	// Generated message map functions


protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	bool m_fileoutput;
	bool m_audiooutput;

	bool m_reverberation;
	bool m_chorus;
	bool m_noisegating;
	bool m_compression;
	bool m_flanging;

	void GenerateWriteFrame(short *p_frame);
	bool OpenGenerateFile(CWaveOut &p_wave);
	void GenerateEnd();
	bool GenerateBegin();

    // Audio destinations..
    CWaveOut        m_wave;
    CDirSoundStream m_soundstream;
    CWaveformBuffer m_waveformBuffer;

	int NumChannels() {return 2;}
	double SampleRate() {return 44100;}

	std::map<CSynthesizer::Effect, bool> m_effectsState;
	double mix;
public:
	afx_msg void OnGenerateFileoutput();
	afx_msg void OnUpdateGenerateFileoutput(CCmdUI *pCmdUI);
	afx_msg void OnGenerateAudiooutput();
	afx_msg void OnUpdateGenerateAudiooutput(CCmdUI *pCmdUI);
	afx_msg void OnGenerate1000hztone();

private:
	CSynthesizer m_synthesizer;
public:
	afx_msg void OnGenerateSynthesizer();
	afx_msg void OnFileOpenscore();


	afx_msg void OnEffectReverberation();
	afx_msg void OnEffectChorus();
	afx_msg void OnEffectCompression();
	afx_msg void OnEffectNoisegating();
	afx_msg void OnEffectFlanging();
	afx_msg void OnUpdateEffectFlanging(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEffectReverberation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEffectCompression(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEffectNoisegating(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEffectChorus(CCmdUI* pCmdUI);
};

