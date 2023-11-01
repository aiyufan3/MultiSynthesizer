#pragma once
#include "AudioEffect.h"
#include <vector>
#include <cmath>

class CReverbEffect : public CAudioEffect
{
public:
    CReverbEffect();
    virtual ~CReverbEffect();

    virtual void Process(double* input, double* output) override;
    virtual void Start() override;
    virtual bool Generate() override;


private:
    double mWet = 0.5;
    double mDry = 0.5;
    double mDelay = 0.15;  // Initial delay of 150ms for reverberation

    double m_sampleRate = 44100.0;

    int mWrloc = 0;
    int mRdloc = 0;

    std::vector<double> m_queueL;
    std::vector<double> m_queueR;

    const double FEEDBACK = 0.7;
};

