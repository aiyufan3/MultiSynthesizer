#pragma once
#include "AudioEffect.h"

class CNoiseGateEffect :
	public CAudioEffect
{
public:
	CNoiseGateEffect();
	virtual ~CNoiseGateEffect();


    virtual void Process(double* input, double* output) override;
    virtual void Start() override;
    virtual bool Generate() override;

    void SetSampleRate(double rate) { m_sampleRate = rate; }
    double GetSampleRate() { return m_sampleRate; }

    void SetThreshold(double threshold) { mThreshold = threshold; }
    void SetAttack(double attack) { mAttack = attack; }
    void SetHold(double hold) { mHold = hold; }
    void SetRelease(double release) { mRelease = release; }

private:
    double m_sampleRate = 44100.0;
    double mThreshold = -40.0;  // Threshold in dB
    double mAttack = 0.01;  // Attack time in seconds
    double mHold = 0.2;    // Hold time in seconds
    double mRelease = 0.1; // Release time in seconds

    bool mGateOpen = false;
    double mHoldTimer = 0.0;

};

