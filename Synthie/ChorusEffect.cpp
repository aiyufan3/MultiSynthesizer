#include "pch.h"
#include "ChorusEffect.h"
#include <algorithm>
#include <cmath>

CChorusEffect::CChorusEffect()
{
    mDelayBufferL.resize(size_t(m_sampleRate * mDepth * 2));
    mDelayBufferR.resize(size_t(m_sampleRate * mDepth * 2));
}

CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Process(double* input, double* output)
{
    double delayLength = mDepth * (1.0 + sin(2 * M_PI * mRate * mPhase));

    size_t delaySamples = static_cast<size_t>(delayLength * m_sampleRate);

    size_t readPos = (mWritePos + mDelayBufferL.size() - delaySamples) % mDelayBufferL.size();

    mDelayBufferL[mWritePos] = input[0];
    mDelayBufferR[mWritePos] = input[1];

    // A basic mix of original and delayed signal
    output[0] = (input[0] + mDelayBufferL[readPos]) * 0.5;
    output[1] = (input[1] + mDelayBufferR[readPos]) * 0.5;

    mWritePos = (mWritePos + 1) % mDelayBufferL.size();
    mPhase += 1.0 / m_sampleRate;
    if (mPhase > 1.0) mPhase -= 1.0;
}

void CChorusEffect::Start()
{
    mWritePos = 0;
    mPhase = 0.0;
    std::fill(mDelayBufferL.begin(), mDelayBufferL.end(), 0.0);
    std::fill(mDelayBufferR.begin(), mDelayBufferR.end(), 0.0);
}

bool CChorusEffect::Generate()
{
    return true;
}
