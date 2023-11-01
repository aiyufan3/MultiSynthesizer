#include "pch.h"
#include "CSynthesizer.h"
#include "CToneInstrument.h"
#include "xmlhelp.h"
#include <algorithm>

CSynthesizer::CSynthesizer()
{
	CoInitialize(NULL);

	m_channels = 2;
	m_sampleRate = 44100.;
	m_samplePeriod = 1 / m_sampleRate;

	m_bpm = 120;
	m_secperbeat = 0.5;
	m_beatspermeasure = 4;
	m_time = 0;
}


CSynthesizer::~CSynthesizer()
{
}

//! Start the synthesizer
void CSynthesizer::Start(void)
{
	//
	m_instruments.clear();
	m_currentNote = 0;
	m_measure = 0;
	m_beat = 0;
	m_time = 0;
}

//! Generate one audio frame
bool CSynthesizer::Generate(double * frame)
{
	// Noise gate threshold
	double noiseGateThreshold = 0.01;

	// Chorus parameters
	double chorusDelay = GetSampleRate() * 0.03;
	double lastFrame[2] = { 0, 0 };

	// Reverberation parameters
	double reverbDelay = GetSampleRate() * 0.1;
	double reverbFeedback = 0.7;
	double reverbFrame[2] = { 0, 0 };

	// Compression parameters
	double compressionThreshold = 0.5;
	double compressionRatio = 0.5;

	//Flanging parameters
	double m_flangeDepth = 0.005;       // Depth (in seconds) of the flanging effect
	double m_flangeFeedback = 0.7;     // Feedback of the flanging effect
	double m_flangeRate = 0.5;         // Rate (in Hz) of the modulation
	double m_flangePos = 0;            // Current position in the modulation
	std::vector<double> m_flangeBuffer; // Circular buffer for flanging effect

	int m_flangeBufferIdx = 0;         // Current position in the buffer
	m_flangeBuffer.assign(static_cast<int>(0.02 * m_sampleRate), 0.0);
	//  effects of frame
	bool sends[] = { false, false, false, false, false };

	//
	// Phase 1: Determine if any notes need to be played.
	//

	while (m_currentNote < (int)m_notes.size())
	{
		// Get a pointer to the current note
		CNote *note = &m_notes[m_currentNote];

		// If the measure is in the future we can't play
		// this note just yet.
		if (note->Measure() > m_measure)
			break;

		// If this is the current measure, but the
		// beat has not been reached, we can't play
		// this note.
		if (note->Measure() == m_measure && note->Beat() > m_beat)
			break;

		//
		// Play the note!
		//

		// Create the instrument object
		CInstrument *instrument = NULL;
		if (note->Instrument() == L"ToneInstrument")
		{
			instrument = new CToneInstrument(GetBPM());
		}

		else if (note->Instrument() == L"AdditiveInstrument")
		{
			instrument = new CAdditiveInstrument(GetBPM());

			if ((m_currentNote + 1) < m_notes.size())
			{
				static_cast<CAdditiveInstrument*>(instrument)->SetNextNote(&m_notes[m_currentNote + 1]);
			}
		}

		else if (note->Instrument() == L"SubtractiveInstrument")
		{
			instrument = new CSubtractiveInstrument(GetBPM());
		}

		else if (note->Instrument() == L"Organ")
		{
			m_organFactory.SetNote(note);
			instrument = m_organFactory.CreateOrgan(GetBPM());
		}

		else if (note->Instrument() == L"NoiseGate")
		{
			sends[0] = true;
			mChorusEffect.SetNote(note);
			mChorusEffect.Start();
		}
		else if (note->Instrument() == L"Compress")
		{
			sends[1] = true;
			mFlangeEffect.SetNote(note);
			mFlangeEffect.Start();
		}
		else if (note->Instrument() == L"Flange")
		{
			sends[2] = true;
			mCompressorEffect.SetNote(note);
			mCompressorEffect.Start();
		}
		else if (note->Instrument() == L"Chorus")
		{
			sends[3] = true;
			mNoiseGateEffect.SetNote(note);
			mNoiseGateEffect.Start();
		}
		else if (note->Instrument() == L"Reverb")
		{
			sends[4] = true;
			mReverbEffect.SetNote(note);
			mReverbEffect.Start();
		}
		// Configure the instrument object
		if (instrument != NULL)
		{
			instrument->SetSampleRate(GetSampleRate());
			instrument->SetNote(note);
			instrument->Start();

			m_instruments.push_back(instrument);
		}

		m_currentNote++;
	}

	//
	// Phase 2: Clear all channels to silence 
	//

	// effects frames
	double channelframes[6][2];
	for (int i = 0; i < 6; i++)
	{
		for (int c = 0; c < GetNumChannels(); c++)
		{
			channelframes[i][c] = 0;
		}
	}

	for (int c = 0; c<GetNumChannels(); c++)
	{
		frame[c] = 0;
	}

	//
	// Phase 3: Play an active instruments
	//

	//
	// We have a list of active (playing) instruments.  We iterate over 
	// that list.  For each instrument we call generate, then add the
	// output to our output frame.  If an instrument is done (Generate()
	// returns false), we remove it from the list.
	//

	for (list<CInstrument *>::iterator node = m_instruments.begin(); node != m_instruments.end();)
	{
		// Since we may be removing an item from the list, we need to know in 
		// advance, what is after it in the list.  We keep that node as "next"
		list<CInstrument *>::iterator next = node;
		next++;

		// Get a pointer to the allocated instrument
		CInstrument *instrument = *node;

		// Call the generate function
		if (instrument->Generate())
		{

			for (int c = 0; c < GetNumChannels(); c++)
			 {
			     frame[c] += instrument->Frame(c);
			     // Noise gating
			     if (m_activeEffects & NoiseGating) {
			         if (abs(frame[c]) < noiseGateThreshold) {
			             frame[c] = 0;
			         }
			     }

			     // Chorus
			     if (m_activeEffects & Chorus) {
			         double chorusSample = (frame[c] + lastFrame[c]) / 2.0;
			         lastFrame[c] = frame[c];
			         frame[c] += chorusSample;
			     }

			     // Compression
			     if (m_activeEffects & Compression) {
			         if (abs(frame[c]) > compressionThreshold) {
			             {
			                 if (frame[c] > 0)
			                     frame[c] = compressionThreshold + (frame[c] - compressionThreshold) * compressionRatio;
			                 else
			                     frame[c] = -compressionThreshold + (frame[c] + compressionThreshold) * compressionRatio;
			             }
			         }
			     }

			     //Reverberation
			     if (m_activeEffects & Reverberation) {
			         frame[c] = (1 - reverbFeedback) * frame[c] + reverbFeedback * reverbFrame[c];
			         reverbFrame[c] = frame[c];
			     }

			     //Flanging
			     if (m_activeEffects & Flanging)
			     {
			         // Calculate the current delay in samples
			         int delay = static_cast<int>((0.5 + 0.5 * sin(2 * 3.14159265 * m_flangeRate * m_time)) * m_flangeDepth * GetSampleRate());
			         // Store the current sample in the flange buffer
			         m_flangeBuffer[m_flangeBufferIdx] = frame[c];
			         // Read the delayed sample from the buffer
			         int readIdx = (m_flangeBufferIdx - delay + m_flangeBuffer.size()) % m_flangeBuffer.size();
			         double delayedSample = m_flangeBuffer[readIdx];
			         // Apply the flanging effect
			         frame[c] += m_flangeFeedback * delayedSample;
			         // Update the buffer index
			         m_flangeBufferIdx = (m_flangeBufferIdx + 1) % m_flangeBuffer.size();
			     }
			 }

			for (int i = 0; i < 5; i++)
			{
				if (sends[i])
				{
					instrument->SetSend(i+1, 1 + i * .5);
					instrument->SetSend(0, 0);
				}
			}

			for (int i = 0; i < 6; i++)
			{
				for (int c = 0; c < GetNumChannels(); c++)
				{
					channelframes[i][c] += instrument->Frame(c) * instrument->Send(i);
				}
			}

		}
		else
		{
			// If we returned false, the instrument is done.  Remove it
			// from the list and delete it from memory.
			m_instruments.erase(node);
			delete instrument;
		}

		//
		// Phase 3a: Effects!
		//

		double frames[2];
		for (int i = 0; i < GetNumChannels(); i++)
		{
			frames[i] = channelframes[0][i];
		}

		double chorusframes[2], flangeframes[2], compressframes[2], noisegateframes[2], reverbframes[2];
		for (int i = 0; i < 2; i++)
		{
			chorusframes[i] = flangeframes[i] = compressframes[i] = noisegateframes[i] = reverbframes[i] = 0;
		}

		
		if (channelframes[1][0] != 0)
		{
			mChorusEffect.Process(channelframes[1], chorusframes);
		}
		if (channelframes[2][0] != 0)
		{
			mFlangeEffect.Process(channelframes[2], flangeframes);
		}
		if (channelframes[3][0] != 0)
		{
			mCompressorEffect.Process(channelframes[3], compressframes);
		}
		if (channelframes[4][0] != 0)
		{
			mNoiseGateEffect.Process(channelframes[4], noisegateframes);
		}
		if (channelframes[5][0] != 0)
		{
			mReverbEffect.Process(channelframes[5], reverbframes);
		}

		for (int i = 0; i < GetNumChannels(); i++)
		{
			frame[i] += frames[i];
			frame[i] += chorusframes[i];
			frame[i] += flangeframes[i];
			frame[i] += compressframes[i];
			frame[i] += noisegateframes[i];
			frame[i] += reverbframes[i];
		}



		// Move to the next instrument in the list
		node = next;
	}

	//
	// Phase 4: Advance the time and beats
	//

	// Time advances by the sample period
	m_time += GetSamplePeriod();

	// Beat advances by the sample period divided by the 
	// number of seconds per beat.  The inverse of seconds
	// per beat is beats per second.
	m_beat += GetSamplePeriod() / m_secperbeat;

	// When the measure is complete, we move to
	// a new measure.  We might be a fraction into
	// the new measure, so we subtract out rather 
	// than just setting to zero.
	if (m_beat > m_beatspermeasure)
	{
		m_beat -= m_beatspermeasure;
		m_measure++;
	}

	//
	// Phase 5: Determine when we are done
	//

	// We are done when there is nothing to play.  We'll put something more 
	// complex here later.
	return !m_instruments.empty() || m_currentNote < (int)m_notes.size();
}

void CSynthesizer::Clear(void)
{
	m_instruments.clear();
	m_notes.clear();
}

void CSynthesizer::OpenScore(CString & filename)
{
	Clear();

	//
	// Create an XML document
	//

	CComPtr<IXMLDOMDocument>  pXMLDoc;
	bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
		IID_IXMLDOMDocument, (void**)&pXMLDoc));
	if (!succeeded)
	{
		AfxMessageBox(L"Failed to create an XML document to use");
		return;
	}

	// Open the XML document
	VARIANT_BOOL ok;
	succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
	if (!succeeded || ok == VARIANT_FALSE)
	{
		AfxMessageBox(L"Failed to open XML score file");
		return;
	}

	//
	// Traverse the XML document in memory!!!!
	// Top level tag is <score>
	//

	CComPtr<IXMLDOMNode> node;
	pXMLDoc->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR nodeName;
		node->get_nodeName(&nodeName);

		if (nodeName == "score")
		{
			XmlLoadScore(node);
		}

	}

	sort(m_notes.begin(), m_notes.end());
}

void CSynthesizer::XmlLoadScore(IXMLDOMNode * xml)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		if (name == L"bpm")
		{
			value.ChangeType(VT_R8);
			m_bpm = value.dblVal;
			m_secperbeat = 1 / (m_bpm / 60);
		}
		else if (name == L"beatspermeasure")
		{
			value.ChangeType(VT_I4);
			m_beatspermeasure = value.intVal;
		}

	}

	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"instrument")
		{
			XmlLoadInstrument(node);
		}

	}
}

void CSynthesizer::XmlLoadInstrument(IXMLDOMNode * xml)
{
	wstring instrument = L"";

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "instrument")
		{
			instrument = value.bstrVal;
		}
	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"note")
		{
			XmlLoadNote(node, instrument);
		}
	}
}

void CSynthesizer::XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument)
{
	m_notes.push_back(CNote());
	m_notes.back().XmlLoad(xml, instrument);
}

void CSynthesizer::ToggleEffect(Effect effect)
{
	if (IsEffectActive(effect))
	{
		m_activeEffects &= ~effect; // deactivate the effect
	}
	else
	{
		m_activeEffects |= effect;  // activate the effect
	}
}

void CSynthesizer::SetEffectMix(Effect effect, double mix)
{
	m_effectMixes[effect] = mix;
}

bool CSynthesizer::IsEffectActive(Effect effect)
{
	return (m_activeEffects & effect) != 0;
}

void CSynthesizer::SetEffect(Effect effect)
{
	m_activeEffects |= effect; // activate the effect
}