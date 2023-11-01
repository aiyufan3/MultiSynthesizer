#pragma once
#include "AudioEffect.h"
class CFlangeEffect :
	public CAudioEffect
{
public:
	CFlangeEffect();
	virtual ~CFlangeEffect();

    virtual void Process(double* input, double* output) override;
    virtual void Start() override;
    virtual bool Generate() override;

    void SetSampleRate(double rate) { m_sampleRate = rate; }
    double GetSampleRate() { return m_sampleRate; }

    void SetWet(double wet) { mWet = wet; }
    void SetDry(double dry) { mDry = dry; }
    void SetDelay(double delay) { mDelay = delay; }

private:
    double mWet = 0.5;
    double mDry = 0.5;
    double mDelay = 0.005; // 5 ms initial delay

    double m_sampleRate = 44100.0;

    int mWrloc = 0;
    int mRdloc = 0;

    std::vector<double> m_queueL;
    std::vector<double> m_queueR;

    // Constants for flanging rate and depth
    const double RATE = 0.25;   // Quarter Hz
    const double RANGE = 0.002; // Range of 2ms
};

