#ifndef SYNTH__UTIL_H_
#define SYNTH__UTIL_H_

#include "types.h"
#include "graph.h"

namespace synth {

/**
 * Finds pointer to character in string
 *
 * @param s A const pointer to the begining of a C-style string
 * @param c The character (char) to search for
 * @return A pointer to the found character, otherwise nullptr
 */
char* find_char(const char* s, char c);

/**
 * Prints a given number of indents to a Print object
 *
 * @param print A Print object that will be used for output
 * @param level The number of levels of indentation to print
 */
void PrintIndent(Print& print, uint8_t level);

/**
 * Prints a represenation of a graph object and its children
 *
 * @param print A Print object that will be used for output
 * @param obj A pointer to a GraphObjectBase object
 * @param level The level of indentation used when printing
 */
void PrintGraph(Print& print, GraphObjectBasePtr obj, uint8_t level = 0);

} // namespace synth

#endif // SYNTH__UTIL_H_
