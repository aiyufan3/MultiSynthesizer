#include "pch.h"
#include "NoiseGateEffect.h"


CNoiseGateEffect::CNoiseGateEffect()
{
}


CNoiseGateEffect::~CNoiseGateEffect()
{
}

void CNoiseGateEffect::Process(double* input, double* output)
{
    for (int i = 0; i < 2; i++)  // Process for both left and right channels
    {
        double inputLevel = 20 * log10(std::abs(input[i]) + 1e-8);  // Compute level in dB

        if (inputLevel > mThreshold && !mGateOpen)
        {
            mGateOpen = true;
            mHoldTimer = mHold;
        }
        else if (mGateOpen)
        {
            if (inputLevel < mThreshold)
            {
                mHoldTimer -= 1.0 / m_sampleRate;
                if (mHoldTimer <= 0.0)
                    mGateOpen = false;
            }
            else
            {
                mHoldTimer = mHold;
            }
        }

        output[i] = mGateOpen ? input[i] : 0.0;
    }

}

void CNoiseGateEffect::Start()
{
    mGateOpen = false;
    mHoldTimer = 0.0;
}

bool CNoiseGateEffect::Generate()
{
	return true;
}