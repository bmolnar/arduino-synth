#include "util.h"
#include "types.h"
#include "graph.h"

namespace synth {

char* find_char(const char* s, char c)
{
  const char* p = s;
  while (*p != c && *p != '\0') {
    ++p;
  }
  return (*p == '\0') ? nullptr : p;
}

void PrintIndent(Print& print, uint8_t level)
{
  while (level-- > 0) {
    print.print("  ");
  }

}
void PrintGraph(Print& print, GraphObjectBasePtr obj, uint8_t level)
{
  if (obj != nullptr) {
    PrintIndent(print, level);
    print.print("+ obj(id="); print.print(((size_t)(void*)obj)); print.print(",ts="); print.print(obj->Timestamp()); print.println("):");
    for (uint8_t i = 0; i < obj->GetNumChildren(); ++i) {
      PrintGraph(print, obj->GetChild(i), (level + 1));
    }
  }
}


} // namespace synth
