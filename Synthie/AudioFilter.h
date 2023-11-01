#pragma once
#include "CAudioNode.h"

class CEnvelope;

class CAudioFilter :
	public CAudioNode
{
public:
	CAudioFilter();
	virtual ~CAudioFilter();

	// SETTERS
	void SetEnvelope(CEnvelope* envelope) { m_envelope = envelope; }
	void SetSource(CAudioNode* source) { m_source = source; }
	void SetDuration(double duration) { m_duration = duration; }

protected:
	// source of the audio node
	CAudioNode* m_source;
	// envelope object
	CEnvelope* m_envelope;
	// audio duration
	double m_duration;
	// keep track of time
	double m_time;
};

