#!/usr/bin/env python3

import sys
import math

class FunctionHeaderGenerator:
  def __init__(self, fp):
    self.fp = fp

  def generate_sine_table(self, count, amplitude, dc_offset):
    self.fp.write("{")
    for idx in range(count):
      value = int(float(dc_offset) + (float(amplitude)-0.5) * math.sin(float(idx) * 2.0 * math.pi / float(count)))
      if (idx > 0):
        self.fp.write(",")
      if ((idx % 8) == 0):
        self.fp.write("\n  ")
      else:
        self.fp.write(" ")
      self.fp.write("%6d" % (value,))
    self.fp.write(",\n}")


  def generate(self):
    self.fp.write("#ifndef SYNTH__PERIODIC_FUNCTIONS_H_\n")
    self.fp.write("#define SYNTH__PERIODIC_FUNCTIONS_H_\n")
    self.fp.write("\n")
    self.fp.write("#include <Arduino.h>\n")
    self.fp.write("\n")
    self.fp.write("namespace synth {\n")

    self.fp.write("\n")

    self.fp.write("const PROGMEM uint16_t SineTable512[512] =\n")
    self.generate_sine_table(512, 2048, 2048)
    self.fp.write(";\n")

    self.fp.write("const PROGMEM int16_t SignedSineTable512[512] =\n")
    self.generate_sine_table(512, 32768, 0)
    self.fp.write(";\n")


    self.fp.write("} // namespace synth\n")
    self.fp.write("#endif // SYNTH__PERIODIC_FUNCTIONS_H_\n")


def main():
  gen = FunctionHeaderGenerator(sys.stdout)
  gen.generate()


if __name__ == '__main__':
  main()
