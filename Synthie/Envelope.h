#pragma once
#include "CAudioNode.h"

class CEnvelope :
	public CAudioNode
{
public:
	CEnvelope();
	virtual ~CEnvelope();

	//! Start the node generation
	virtual void Start() override {};
	//! Cause one sample to be generated
	virtual bool Generate() override { return false; }

	// GETTERS
	double GetEnvelopeLevel() { return m_level; }

	// SETTERS
	void SetDuration(double duration) { m_duration = duration; }

protected:
	// how long the sample audio goes
	double m_duration;
	// keep track of time
	double m_time;
	// the envelope level
	double m_level;
};

