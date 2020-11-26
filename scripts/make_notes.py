#!/usr/bin/env python3

import sys

class Key:
  def __init__(self, name, value):
    self.name = name
    self.value = value

KEYS = [
  Key("C", 0), Key("Cs", 1), Key("Dd", 1), Key("D", 2),
  Key("Ds", 3), Key("Eb", 3), Key("E", 4), Key("F", 5),
  Key("Fs", 6), Key("Gb", 6), Key("G", 7), Key("Gs", 8), Key("Ab", 8),
  Key("A", 9), Key("As", 10), Key("Bb", 10), Key("B", 11),
]

class Note:
  def __init__(self, octave, key):
    self.octave = octave
    self.key = key
  def get_midi(self):
    return 12 * (self.octave + 1) + self.key.value
  def get_voltage(self):
    return 1.0 * float(self.octave) + float(self.key.value) / 12.0
  def get_dac(self):
    return int(819.0 * float(self.octave) + (819.0 * float(self.key.value) / 12.0))
  def get_name(self):
    return "%s%d" % (self.key.name, self.octave)

NOTES = []
for octave in range(10):
  for key in KEYS:
    note = Note(octave, key)
    if note.get_midi() < 128:
      NOTES.append(note)


class NoteHeaderGenerator:
  def __init__(self, fp):
    self.fp = fp

  def generate_header_top(self):
    self.fp.write("#ifndef SYNTH__NOTES_H_\n")
    self.fp.write("#define SYNTH__NOTES_H_\n")
    self.fp.write("\n")
    self.fp.write("#include <Arduino.h>\n")
    self.fp.write("\n")
    self.fp.write("namespace synth {\n")
    self.fp.write("namespace notes {\n")
  def generate_header_bottom(self):
    self.fp.write("} // namespace notes\n")
    self.fp.write("} // namespace synth\n")
    self.fp.write("#endif // SYNTH__NOTES_H_\n")

  def generate_midi_values(self):
    self.fp.write("namespace midi {\n")
    for note in NOTES:
      self.fp.write("static const uint8_t Note_%s = %d;\n" % (note.get_name(), note.get_midi()))
    self.fp.write("} // namespace midi\n")

  def generate_millivolts_values(self):
    self.fp.write("namespace voltage {\n")
    for note in NOTES:
      self.fp.write("static const voltage_t Note_%s = millivolts(%d);\n" % (note.get_name(), int(1000.0 * note.get_voltage())))
    self.fp.write("} // namespace voltage\n")

  def generate_dac_values(self):
    self.fp.write("namespace dac {\n")
    for note in NOTES:
      if note.get_dac() >= 4096:
        break
      self.fp.write("static const uint16_t Note_%s = %d;\n" % (note.get_name(), note.get_dac()))
    self.fp.write("} // namespace dac\n")

  def generate(self):
    self.generate_header_top()
    self.fp.write("\n")
    self.generate_midi_values()
    self.fp.write("\n")
    self.generate_millivolts_values()
    self.fp.write("\n")
    #self.generate_dac_values()
    #self.fp.write("\n")
    self.generate_header_bottom()


def main():
  gen = NoteHeaderGenerator(sys.stdout)
  gen.generate()

if __name__ == '__main__':
  main()
