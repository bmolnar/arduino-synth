#include "util.h"

namespace synth {

char* find_char(const char* s, char c)
{
  const char* p = s;
  while (*p != c && *p != '\0') {
    ++p;
  }
  return (*p == '\0') ? nullptr : p;
}


} // namespace synth
