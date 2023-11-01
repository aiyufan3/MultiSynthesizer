#include "pch.h"
#include "CompressorEffect.h"


CCompressorEffect::CCompressorEffect()
{
}


CCompressorEffect::~CCompressorEffect()
{
}

void CCompressorEffect::Process(double* input, double* output)
{
    for (int i = 0; i < 2; i++)  // Process for both left and right channels
    {
        double inputLevel = 20 * log10(std::abs(input[i]) + 1e-8);  // Compute level in dB
        if (inputLevel > mThreshold)
        {
            double compressionAmount = 1.0 - 1.0 / mRatio;
            double desiredGainReduction = compressionAmount * (inputLevel - mThreshold);
            mGainReduction = (mGainReduction + desiredGainReduction * mAttack) / (1.0 + mAttack);
        }
        else
        {
            mGainReduction /= 1.0 + mRelease;
        }

        output[i] = input[i] * mGainReduction;
    }
}

void CCompressorEffect::Start()
{
    mGainReduction = 1.0;

}

bool CCompressorEffect::Generate()
{
	return true;
}