#pragma once
#include "Envelope.h"

class CADSREnvelope :
	public CEnvelope
{
public:
	CADSREnvelope();
	virtual ~CADSREnvelope();

	//! Start the node generation
	virtual void Start() override;
	//! Cause one sample to be generated
	virtual bool Generate() override;

	// SETTERS

	// set attack length
	void SetAttack(double attack) { m_attack = attack; }
	// set decay length
	void SetDecay(double decay) { m_decay = decay; }
	// set the sustain level
	void SetSustain(double sustain) { m_sustain = sustain; }
	// set release length
	void SetRelease(double release) { m_release = release; }

private:
	// ADSR
	double m_attack;
	double m_decay;
	double m_sustain; // sustain level
	double m_release;
};

