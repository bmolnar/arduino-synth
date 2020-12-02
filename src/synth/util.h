#ifndef SYNTH__UTIL_H_
#define SYNTH__UTIL_H_

#include "types.h"
#include "graph.h"

namespace synth {

char* find_char(const char* s, char c);
void PrintIndent(Print& print, uint8_t level);
void PrintGraph(Print& print, GraphObjectBasePtr obj, uint8_t level = 0);

} // namespace synth

#endif // SYNTH__UTIL_H_
