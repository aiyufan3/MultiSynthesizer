#include "pch.h"
#include "ReverberationEffect.h"

CReverbEffect::CReverbEffect()
{
}

CReverbEffect::~CReverbEffect()
{
}

void CReverbEffect::Process(double* input, double* output)
{
    mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
    m_queueL[mWrloc] = input[0] + FEEDBACK * m_queueL[mRdloc];
    mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
    m_queueR[mWrloc] = input[1] + FEEDBACK * m_queueR[mRdloc];

    int delayLength = int((mDelay * GetSampleRate() + 0.5));
    mRdloc = (mWrloc + MAXQUEUESIZE - delayLength) % MAXQUEUESIZE;

    output[0] = mWet * m_queueL[mRdloc] + mDry * input[0];
    output[1] = mWet * m_queueR[mRdloc] + mDry * input[1];
}

void CReverbEffect::Start()
{
    mWrloc = 0;
    mRdloc = 0;
    m_queueL.resize(MAXQUEUESIZE);
    m_queueR.resize(MAXQUEUESIZE);
}

bool CReverbEffect::Generate()
{
    return true;
}
