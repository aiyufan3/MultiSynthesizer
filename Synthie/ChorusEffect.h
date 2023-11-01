#pragma once
#include "AudioEffect.h"
#include <vector>

class CChorusEffect : public CAudioEffect
{
public:
    CChorusEffect();
    virtual ~CChorusEffect();

    virtual void Process(double* input, double* output) override;
    virtual void Start() override;
    virtual bool Generate() override;

    void SetSampleRate(double rate) { m_sampleRate = rate; }
    double GetSampleRate() { return m_sampleRate; }

    void SetDepth(double depth) { mDepth = depth; }
    void SetRate(double rate) { mRate = rate; }

private:
    double m_sampleRate = 44100.0;
    double mDepth = 0.005;  // Depth of the chorus effect in seconds
    double mRate = 0.5;    // Rate of the LFO in Hz

    double mPhase = 0.0;

    std::vector<double> mDelayBufferL;
    std::vector<double> mDelayBufferR;
    size_t mWritePos = 0;
};