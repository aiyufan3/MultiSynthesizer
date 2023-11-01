#include "pch.h"
#include "OrganInstrument.h"
#include "Notes.h"

COrganInstrument::COrganInstrument()
{
	m_duration = 0.1;
}

//	Constructor 
//	Tonewheels are the sound generators in a Hammond B3 organ
COrganInstrument::COrganInstrument(double bpm) : m_leslieChanged(true)
{
	m_drawbars.assign(9, 0.0);
	m_bpm = bpm;
}
COrganInstrument::~COrganInstrument()
{
}

void COrganInstrument::Start()
{
	m_time = 0;
	m_organWave.SetSampleRate(GetSampleRate());
	m_organWave.Start();

	m_envelope.SetSource(&m_organWave);
	m_envelope.SetSampleRate(GetSampleRate());
	m_envelope.Start();
}


bool COrganInstrument::Generate()
{
	// generate an audio 
	m_organWave.Generate();

	// use the envelope
	bool valid = m_envelope.Generate();
	m_frame[0] = m_envelope.Frame(0);
	m_frame[1] = m_envelope.Frame(1);
	m_time += GetSamplePeriod();

	return valid;
}

void COrganInstrument::SetOrganDrawbars(int drawbarNum)
{
	int digit = 0;
	for (int i = 0; i < 9; i++)
	{
		digit = (drawbarNum / (int)pow(10.0, 8 - i)) % 10;
		m_drawbars[i] = digit ? pow(10.0, (((8 - (double)digit) * -3) / 20)) : 0.0;
	}
	SetWaveDrawbars(m_drawbars);
}

void COrganInstrument::SetLeslieAttackTime(double leslieAttack)
{
	if (m_leslieChanged)
	{
		m_organWave.SetLeslieAttackTime(leslieAttack);
		m_leslieChanged = false;
	}
}

void COrganInstrument::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "leslieAttackTime")
		{
			value.ChangeType(VT_R8);
			SetLeslieAttackTime(value.dblVal);
		}
		else if (name == "leslieReleaseTime")
		{
			value.ChangeType(VT_R8);
			SetLeslieReleaseTime(value.dblVal);
		}
		else if (name == "leslieFreq")
		{
			value.ChangeType(VT_R8);
			SetLeslieFreq(value.dblVal);
			SetLeslieChanged(true);
		}
		else if (name == "leslieEndFreq")
		{
			value.ChangeType(VT_R8);
			SetLeslieEndFreq(value.dblVal);
		}
		else if (name == "leslieRadius")
		{
			value.ChangeType(VT_R8);
			SetLeslieRadius(value.dblVal);
		}
		else if (name == "vibratoMag")
		{
			value.ChangeType(VT_R8);
			SetVibratoFlag(value.dblVal);
		}
		else if (name == "vibratoFreq")
		{
			value.ChangeType(VT_R8);
			SetVibratoFreq(value.dblVal);
		}
		else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_envelope.SetAttack(value.dblVal);
		}
		else if (name == "decay")
		{
			value.ChangeType(VT_R8);
			m_envelope.SetDecay(value.dblVal);
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_envelope.SetRelease(value.dblVal);
		}
		else if (name == "amplitude")
		{
			value.ChangeType(VT_R8);
			SetAmplitude(value.dblVal);
		}
		else if (name == "drawbar")
		{
			value.ChangeType(VT_I4);
			SetOrganDrawbars(value.intVal);
		}
	}

}