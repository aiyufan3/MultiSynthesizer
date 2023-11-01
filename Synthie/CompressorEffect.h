#pragma once
#include "AudioEffect.h"
class CCompressorEffect :
	public CAudioEffect
{
public:
    CCompressorEffect();
    virtual ~CCompressorEffect();

    virtual void Process(double* input, double* output) override;
    virtual void Start() override;
    virtual bool Generate() override;

    void SetSampleRate(double rate) { m_sampleRate = rate; }
    double GetSampleRate() { return m_sampleRate; }

    void SetThreshold(double threshold) { mThreshold = threshold; }
    void SetRatio(double ratio) { mRatio = ratio; }
    void SetAttack(double attack) { mAttack = attack; }
    void SetRelease(double release) { mRelease = release; }

private:
    double m_sampleRate = 44100.0;
    double mThreshold = -20.0;  // Threshold in dB
    double mRatio = 4.0;  // Compression ratio 4:1 by default
    double mAttack = 0.01;  // Attack time in seconds
    double mRelease = 0.1;  // Release time in seconds

    double mGainReduction = 1.0;
};

