#pragma once
#include <vector>
#include "OrganInstrument.h"

class COrganFactory
{
public:
	COrganFactory();
	virtual ~COrganFactory();

	COrganInstrument *COrganFactory::CreateOrgan(double bpm);
	void COrganFactory::SetNote(CNote *note);
	void SetFactoryDrawbars(int drawbarNum);

private:
	double m_amp;

	double m_vibratoFreq;
	double m_vibratoFlag;

	bool m_leslieChanged;
	double m_leslieFreq;
	double m_leslieStartFreq;
	double m_leslieEndFreq;
	double m_leslieRadius;
	double m_leslieAttackTime;
	double m_leslieReleaseTime;

	int m_drawbarNum;
	vector<double> m_drawbars;

	vector<double> m_harmonics;
};

