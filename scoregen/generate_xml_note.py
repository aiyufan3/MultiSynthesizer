import random
import xml.etree.ElementTree as ET
from xml.dom import minidom

# Given parameters
BPM = 120
total_duration_seconds = 60
total_notes = 240
possible_durations = [0.5, 0.33]
possible_notes = ["C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5"]

# Create XML structure
score = ET.Element("score", bpm=str(BPM), beatspermeasure="2")
instrument = ET.SubElement(score, "instrument", instrument="ToneInstrument")

# Initialize measure and beat counters
current_measure = 1
current_beat = 1

# Add notes
for _ in range(total_notes):
    duration = random.choice(possible_durations)
    note_name = random.choice(possible_notes)

    # Add note to XML
    note = ET.SubElement(instrument, "note", 
                         measure=str(current_measure), 
                         beat=str(current_beat), 
                         duration=str(duration), 
                         note=note_name)
    
    # Update measure and beat for next iteration
    current_beat += duration
    if current_beat > 2:  # Go to the next measure
        current_measure += 1
        current_beat = 1

# Prettify and print XML
def prettify(elem):
    """Return a pretty-printed XML string for the Element."""
    rough_string = ET.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

print(prettify(score))
