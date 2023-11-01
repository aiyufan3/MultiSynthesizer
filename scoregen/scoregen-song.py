import xml.etree.ElementTree as ET

# Given XML data
xml_data = '''<?xml version="1.0" encoding="utf-8"?>
<score bpm="120" beatspermeasure="2">
  <instrument instrument="ToneInstrument">
    <note measure="1" beat="1" duration="0.5" note="D4"/>
    <note measure="1" beat="1.5" duration="0.33" note="D4"/>
    <note measure="1" beat="1.83" duration="0.33" note="F4"/>
    <note measure="2" beat="1" duration="0.5" note="D5"/>
    <note measure="2" beat="1.5" duration="0.5" note="E5"/>
    <note measure="2" beat="2.0" duration="0.33" note="C5"/>
    <note measure="3" beat="1" duration="0.5" note="G5"/>
    <note measure="3" beat="1.5" duration="0.5" note="E4"/>
    <note measure="3" beat="2.0" duration="0.5" note="E5"/>
    <note measure="4" beat="1" duration="0.33" note="G4"/>
    <note measure="4" beat="1.33" duration="0.5" note="F5"/>
    <note measure="4" beat="1.83" duration="0.33" note="G5"/>
    <note measure="5" beat="1" duration="0.5" note="F4"/>
    <note measure="5" beat="1.5" duration="0.5" note="B4"/>
    <note measure="5" beat="2.0" duration="0.5" note="F4"/>
    <note measure="6" beat="1" duration="0.5" note="C4"/>
    <note measure="6" beat="1.5" duration="0.5" note="E4"/>
    <note measure="6" beat="2.0" duration="0.33" note="C5"/>
    <note measure="7" beat="1" duration="0.33" note="E4"/>
    <note measure="7" beat="1.33" duration="0.33" note="E4"/>
    <note measure="7" beat="1.66" duration="0.5" note="D5"/>
    <note measure="8" beat="1" duration="0.5" note="B4"/>
    <note measure="8" beat="1.5" duration="0.5" note="B4"/>
    <note measure="8" beat="2.0" duration="0.33" note="G4"/>
    <note measure="9" beat="1" duration="0.33" note="D4"/>
    <note measure="9" beat="1.33" duration="0.5" note="C5"/>
    <note measure="9" beat="1.83" duration="0.33" note="C5"/>
    <note measure="10" beat="1" duration="0.5" note="F4"/>
    <note measure="10" beat="1.5" duration="0.5" note="E4"/>
    <note measure="10" beat="2.0" duration="0.33" note="D5"/>
    <note measure="11" beat="1" duration="0.33" note="E5"/>
    <note measure="11" beat="1.33" duration="0.33" note="B4"/>
    <note measure="11" beat="1.66" duration="0.5" note="G4"/>
    <note measure="12" beat="1" duration="0.5" note="D5"/>
    <note measure="12" beat="1.5" duration="0.5" note="F4"/>
    <note measure="12" beat="2.0" duration="0.33" note="D4"/>
    <note measure="13" beat="1" duration="0.5" note="F4"/>
    <note measure="13" beat="1.5" duration="0.33" note="C4"/>
    <note measure="13" beat="1.83" duration="0.33" note="C4"/>
    <note measure="14" beat="1" duration="0.5" note="D4"/>
    <note measure="14" beat="1.5" duration="0.33" note="C4"/>
    <note measure="14" beat="1.83" duration="0.5" note="G5"/>
    <note measure="15" beat="1" duration="0.33" note="E5"/>
    <note measure="15" beat="1.33" duration="0.33" note="E4"/>
    <note measure="15" beat="1.66" duration="0.5" note="F5"/>
    <note measure="16" beat="1" duration="0.33" note="D5"/>
    <note measure="16" beat="1.33" duration="0.33" note="C4"/>
    <note measure="16" beat="1.66" duration="0.5" note="E5"/>
    <note measure="17" beat="1" duration="0.33" note="C5"/>
    <note measure="17" beat="1.33" duration="0.5" note="E5"/>
    <note measure="17" beat="1.83" duration="0.5" note="B4"/>
    <note measure="18" beat="1" duration="0.33" note="A4"/>
    <note measure="18" beat="1.33" duration="0.5" note="B4"/>
    <note measure="18" beat="1.83" duration="0.33" note="E5"/>
    <note measure="19" beat="1" duration="0.5" note="E4"/>
    <note measure="19" beat="1.5" duration="0.33" note="E5"/>
    <note measure="19" beat="1.83" duration="0.5" note="E5"/>
    <note measure="20" beat="1" duration="0.5" note="D5"/>
    <note measure="20" beat="1.5" duration="0.33" note="C4"/>
    <note measure="20" beat="1.83" duration="0.5" note="C5"/>
    <note measure="21" beat="1" duration="0.5" note="E4"/>
    <note measure="21" beat="1.5" duration="0.5" note="F4"/>
    <note measure="21" beat="2.0" duration="0.5" note="B4"/>
    <note measure="22" beat="1" duration="0.33" note="G4"/>
    <note measure="22" beat="1.33" duration="0.5" note="B4"/>
    <note measure="22" beat="1.83" duration="0.5" note="E5"/>
    <note measure="23" beat="1" duration="0.33" note="F5"/>
    <note measure="23" beat="1.33" duration="0.33" note="C4"/>
    <note measure="23" beat="1.66" duration="0.33" note="F4"/>
    <note measure="23" beat="1.99" duration="0.33" note="C4"/>
    <note measure="24" beat="1" duration="0.5" note="F4"/>
    <note measure="24" beat="1.5" duration="0.33" note="E5"/>
    <note measure="24" beat="1.83" duration="0.33" note="E4"/>
    <note measure="25" beat="1" duration="0.33" note="E5"/>
    <note measure="25" beat="1.33" duration="0.33" note="D5"/>
    <note measure="25" beat="1.66" duration="0.33" note="E5"/>
    <note measure="25" beat="1.99" duration="0.33" note="B4"/>
    <note measure="26" beat="1" duration="0.5" note="G5"/>
    <note measure="26" beat="1.5" duration="0.5" note="E4"/>
    <note measure="26" beat="2.0" duration="0.33" note="D5"/>
    <note measure="27" beat="1" duration="0.33" note="F5"/>
    <note measure="27" beat="1.33" duration="0.33" note="F4"/>
    <note measure="27" beat="1.66" duration="0.5" note="A4"/>
    <note measure="28" beat="1" duration="0.33" note="B4"/>
    <note measure="28" beat="1.33" duration="0.33" note="G4"/>
    <note measure="28" beat="1.66" duration="0.33" note="F4"/>
    <note measure="28" beat="1.99" duration="0.5" note="A4"/>
    <note measure="29" beat="1" duration="0.33" note="C5"/>
    <note measure="29" beat="1.33" duration="0.33" note="D5"/>
    <note measure="29" beat="1.6600000000000001" duration="0.33" note="G4"/>
    <note measure="29" beat="1.9900000000000002" duration="0.5" note="G4"/>
    <note measure="30" beat="1" duration="0.5" note="G5"/>
    <note measure="30" beat="1.5" duration="0.33" note="E5"/>
    <note measure="30" beat="1.83" duration="0.33" note="A4"/>
    <note measure="31" beat="1" duration="0.5" note="B4"/>
    <note measure="31" beat="1.5" duration="0.5" note="C4"/>
    <note measure="31" beat="2.0" duration="0.33" note="C5"/>
    <note measure="32" beat="1" duration="0.5" note="F4"/>
    <note measure="32" beat="1.5" duration="0.33" note="F4"/>
    <note measure="32" beat="1.83" duration="0.5" note="C4"/>
    <note measure="33" beat="1" duration="0.5" note="B4"/>
    <note measure="33" beat="1.5" duration="0.33" note="C4"/>
    <note measure="33" beat="1.83" duration="0.33" note="G5"/>
    <note measure="34" beat="1" duration="0.33" note="G5"/>
    <note measure="34" beat="1.33" duration="0.33" note="A4"/>
    <note measure="34" beat="1.6600000000000001" duration="0.5" note="G4"/>
    <note measure="35" beat="1" duration="0.5" note="F5"/>
    <note measure="35" beat="1.5" duration="0.5" note="E4"/>
    <note measure="35" beat="2.0" duration="0.5" note="F4"/>
    <note measure="36" beat="1" duration="0.5" note="D4"/>
    <note measure="36" beat="1.5" duration="0.33" note="F4"/>
    <note measure="36" beat="1.83" duration="0.5" note="C5"/>
    <note measure="37" beat="1" duration="0.5" note="E4"/>
    <note measure="37" beat="1.5" duration="0.33" note="G5"/>
    <note measure="37" beat="1.83" duration="0.33" note="C4"/>
    <note measure="38" beat="1" duration="0.5" note="C4"/>
    <note measure="38" beat="1.5" duration="0.33" note="D5"/>
    <note measure="38" beat="1.83" duration="0.33" note="G4"/>
    <note measure="39" beat="1" duration="0.33" note="D5"/>
    <note measure="39" beat="1.33" duration="0.5" note="F4"/>
    <note measure="39" beat="1.83" duration="0.5" note="F4"/>
    <note measure="40" beat="1" duration="0.5" note="G5"/>
    <note measure="40" beat="1.5" duration="0.5" note="F5"/>
    <note measure="40" beat="2.0" duration="0.5" note="F5"/>
    <note measure="41" beat="1" duration="0.5" note="A4"/>
    <note measure="41" beat="1.5" duration="0.5" note="A4"/>
    <note measure="41" beat="2.0" duration="0.5" note="G5"/>
    <note measure="42" beat="1" duration="0.33" note="B4"/>
    <note measure="42" beat="1.33" duration="0.33" note="G5"/>
    <note measure="42" beat="1.6600000000000001" duration="0.33" note="C5"/>
    <note measure="42" beat="1.9900000000000002" duration="0.5" note="G4"/>
    <note measure="43" beat="1" duration="0.33" note="C4"/>
    <note measure="43" beat="1.33" duration="0.5" note="G4"/>
    <note measure="43" beat="1.83" duration="0.5" note="G5"/>
    <note measure="44" beat="1" duration="0.33" note="F5"/>
    <note measure="44" beat="1.33" duration="0.5" note="D5"/>
    <note measure="44" beat="1.83" duration="0.33" note="E4"/>
    <note measure="45" beat="1" duration="0.5" note="E4"/>
    <note measure="45" beat="1.5" duration="0.33" note="C4"/>
    <note measure="45" beat="1.83" duration="0.5" note="F4"/>
    <note measure="46" beat="1" duration="0.5" note="F4"/>
    <note measure="46" beat="1.5" duration="0.5" note="B4"/>
    <note measure="46" beat="2.0" duration="0.33" note="E4"/>
    <note measure="47" beat="1" duration="0.5" note="G5"/>
    <note measure="47" beat="1.5" duration="0.5" note="B4"/>
    <note measure="47" beat="2.0" duration="0.5" note="A4"/>
    <note measure="48" beat="1" duration="0.33" note="B4"/>
    <note measure="48" beat="1.33" duration="0.33" note="G5"/>
    <note measure="48" beat="1.6600000000000001" duration="0.5" note="F4"/>
    <note measure="49" beat="1" duration="0.33" note="G5"/>
    <note measure="49" beat="1.33" duration="0.33" note="F4"/>
    <note measure="49" beat="1.6600000000000001" duration="0.33" note="D5"/>
    <note measure="49" beat="1.9900000000000002" duration="0.5" note="C4"/>
    <note measure="50" beat="1" duration="0.5" note="D5"/>
    <note measure="50" beat="1.5" duration="0.5" note="F4"/>
    <note measure="50" beat="2.0" duration="0.5" note="E5"/>
    <note measure="51" beat="1" duration="0.33" note="C4"/>
    <note measure="51" beat="1.33" duration="0.33" note="D4"/>
    <note measure="51" beat="1.6600000000000001" duration="0.5" note="G4"/>
    <note measure="52" beat="1" duration="0.33" note="G4"/>
    <note measure="52" beat="1.33" duration="0.5" note="E4"/>
    <note measure="52" beat="1.83" duration="0.5" note="F5"/>
    <note measure="53" beat="1" duration="0.33" note="D4"/>
    <note measure="53" beat="1.33" duration="0.5" note="G5"/>
    <note measure="53" beat="1.83" duration="0.5" note="E4"/>
    <note measure="54" beat="1" duration="0.33" note="F4"/>
    <note measure="54" beat="1.33" duration="0.5" note="D4"/>
    <note measure="54" beat="1.83" duration="0.5" note="D4"/>
    <note measure="55" beat="1" duration="0.5" note="E4"/>
    <note measure="55" beat="1.5" duration="0.33" note="B4"/>
    <note measure="55" beat="1.83" duration="0.5" note="D5"/>
    <note measure="56" beat="1" duration="0.33" note="G5"/>
    <note measure="56" beat="1.33" duration="0.33" note="F5"/>
    <note measure="56" beat="1.6600000000000001" duration="0.33" note="F5"/>
    <note measure="56" beat="1.9900000000000002" duration="0.33" note="E5"/>
    <note measure="57" beat="1" duration="0.33" note="C4"/>
    <note measure="57" beat="1.33" duration="0.33" note="D4"/>
    <note measure="57" beat="1.6600000000000001" duration="0.33" note="C4"/>
    <note measure="57" beat="1.9900000000000002" duration="0.5" note="C4"/>
    <note measure="58" beat="1" duration="0.5" note="E5"/>
    <note measure="58" beat="1.5" duration="0.33" note="B4"/>
    <note measure="58" beat="1.83" duration="0.33" note="G4"/>
    <note measure="59" beat="1" duration="0.33" note="B4"/>
    <note measure="59" beat="1.33" duration="0.5" note="F4"/>
    <note measure="59" beat="1.83" duration="0.5" note="C4"/>
    <note measure="60" beat="1" duration="0.5" note="E5"/>
    <note measure="60" beat="1.5" duration="0.33" note="F5"/>
    <note measure="60" beat="1.83" duration="0.5" note="D4"/>
    <note measure="61" beat="1" duration="0.33" note="G5"/>
    <note measure="61" beat="1.33" duration="0.33" note="D5"/>
    <note measure="61" beat="1.6600000000000001" duration="0.33" note="F5"/>
    <note measure="61" beat="1.9900000000000002" duration="0.33" note="C4"/>
    <note measure="62" beat="1" duration="0.5" note="D4"/>
    <note measure="62" beat="1.5" duration="0.5" note="E4"/>
    <note measure="62" beat="2.0" duration="0.33" note="B4"/>
    <note measure="63" beat="1" duration="0.5" note="G4"/>
    <note measure="63" beat="1.5" duration="0.33" note="B4"/>
    <note measure="63" beat="1.83" duration="0.5" note="C4"/>
    <note measure="64" beat="1" duration="0.33" note="D4"/>
    <note measure="64" beat="1.33" duration="0.5" note="C5"/>
    <note measure="64" beat="1.83" duration="0.33" note="C4"/>
    <note measure="65" beat="1" duration="0.5" note="G5"/>
    <note measure="65" beat="1.5" duration="0.5" note="F5"/>
    <note measure="65" beat="2.0" duration="0.5" note="F5"/>
    <note measure="66" beat="1" duration="0.33" note="F4"/>
    <note measure="66" beat="1.33" duration="0.5" note="F4"/>
    <note measure="66" beat="1.83" duration="0.5" note="B4"/>
    <note measure="67" beat="1" duration="0.33" note="F4"/>
    <note measure="67" beat="1.33" duration="0.33" note="D5"/>
    <note measure="67" beat="1.6600000000000001" duration="0.5" note="F4"/>
    <note measure="68" beat="1" duration="0.5" note="F4"/>
    <note measure="68" beat="1.5" duration="0.5" note="C5"/>
    <note measure="68" beat="2.0" duration="0.33" note="D5"/>
    <note measure="69" beat="1" duration="0.5" note="B4"/>
    <note measure="69" beat="1.5" duration="0.5" note="D4"/>
    <note measure="69" beat="2.0" duration="0.33" note="C4"/>
    <note measure="70" beat="1" duration="0.33" note="D5"/>
    <note measure="70" beat="1.33" duration="0.33" note="D5"/>
    <note measure="70" beat="1.6600000000000001" duration="0.5" note="F4"/>
    <note measure="71" beat="1" duration="0.5" note="C5"/>
    <note measure="71" beat="1.5" duration="0.33" note="G4"/>
    <note measure="71" beat="1.83" duration="0.33" note="F4"/>
    <note measure="72" beat="1" duration="0.5" note="F5"/>
    <note measure="72" beat="1.5" duration="0.33" note="F5"/>
    <note measure="72" beat="1.83" duration="0.5" note="C4"/>
    <note measure="73" beat="1" duration="0.5" note="E4"/>
    <note measure="73" beat="1.5" duration="0.5" note="F4"/>
    <note measure="73" beat="2.0" duration="0.5" note="F4"/>
    <note measure="74" beat="1" duration="0.33" note="D5"/>
    <note measure="74" beat="1.33" duration="0.33" note="G4"/>
    <note measure="74" beat="1.6600000000000001" duration="0.5" note="F5"/>
    <note measure="75" beat="1" duration="0.33" note="E5"/>
    <note measure="75" beat="1.33" duration="0.33" note="A4"/>
    <note measure="75" beat="1.6600000000000001" duration="0.5" note="E4"/>
    <note measure="76" beat="1" duration="0.33" note="F5"/>
    <note measure="76" beat="1.33" duration="0.5" note="F4"/>
    <note measure="76" beat="1.83" duration="0.5" note="C5"/>
    <note measure="77" beat="1" duration="0.5" note="D4"/>
    <note measure="77" beat="1.5" duration="0.5" note="A4"/>
    <note measure="77" beat="2.0" duration="0.33" note="F4"/>
  </instrument>
</score>'''

# New sequence of notes
new_notes = [
"Eb3", "Ab3", "Ab3", "Eb3", "Eb3", "Eb3", "Eb3", "CC3", "Bb3", "Bb3", "Ab3", "Ab3", "Eb3", "Eb3", "Eb3", "C3", "C3", "Bb3", "Bb3", "C3",
"Ab3", "Ab3", "C3", "Bb3",
"Eb3", "Ab3", "Eb3", "Eb3", "Eb3", "C3", "C3", "C3", "Bb3", "Bb3", "Ab3", "Ab3", "C3", "C3", "Bb3", "Bb3", "Ab3", "Ab3", "Eb3", "Ab3",
"Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "A3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"C3", "Eb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3", "Eb3", "Eb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3",
"Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "C3", "C3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "C3", "C3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "C3", "C3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Eb3", "Eb3", "Eb3", "Eb3", "C3", "C3", "C3", "Bb3", "Bb3", "Ab3", "C3", "Eb3", "F3", "C3", "C3", "Bb3", "Bb3", "C3", "Ab3", "Ab3", "C3", "Bb3",
"Eb3", "Eb3", "Eb3", "Eb3", "Eb3", "C3", "C3", "Bb3", "Bb3", "Ab3", "C3", "Eb3", "F3", "C3", "C3", "Bb3", "Bb3", "C3", "C3", "Bb3",
"Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3",
"Ab3", "Bb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3", "Ab3", "Bb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3", "Ab3",
"Bb3", "Bb3", "C3", "A3", "b3", "B3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "C3", "C3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Eb3", "Ab3", "Ab3", "Eb3", "Eb3", "Eb3", "Eb3", "CC3", "Bb3", "Bb3", "Ab3", "Ab3", "Eb3", "Eb3", "Eb3", "C3", "C3", "Bb3", "Bb3", "C3",
"Ab3", "Ab3", "C3", "Bb3",
"Eb3", "Ab3", "Eb3", "Eb3", "Eb3", "C3", "C3", "C3", "Bb3", "Bb3", "Ab3", "Ab3", "C3", "C3", "Bb3", "Bb3", "Ab3", "Ab3", "Eb3", "Ab3",
"Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "A3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"C3", "Eb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3", "Eb3", "Eb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3",
"Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "C3", "C3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Eb3", "Ab3", "Ab3", "Eb3", "Eb3", "Eb3", "Eb3", "CC3", "Bb3", "Bb3", "Ab3", "Ab3", "Eb3", "Eb3", "Eb3", "C3", "C3", "Bb3", "Bb3", "C3",
"Ab3", "Ab3", "C3", "Bb3",
"Eb3", "Ab3", "Eb3", "Eb3", "Eb3", "C3", "C3", "C3", "Bb3", "Bb3", "Ab3", "Ab3", "C3", "C3", "Bb3", "Bb3", "Ab3", "Ab3", "Eb3", "Ab3",
"Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "A3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"C3", "Eb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3", "Eb3", "Eb3", "C3", "Bb3", "Ab3", "Eb3", "C3", "Bb3",
"Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "Bb3", "Bb3", "C3", "Ab3", "Bb3", "Bb3", "Ab3", "Bb3", "Bb3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3",
"Ab3", "C3", "C3", "Ab3", "Ab3", "Bb3", "Bb3", "Ab3"
]

# Parse the XML data
root = ET.fromstring(xml_data)

# Locate all <note> elements and update the 'note' attribute
for i, note_element in enumerate(root.findall(".//note")):
    if i < len(new_notes):
        note_element.set("note", new_notes[i])

# Convert the updated XML tree back to a string
updated_xml_data = ET.tostring(root, encoding="utf-8").decode("utf-8")

print(updated_xml_data)
