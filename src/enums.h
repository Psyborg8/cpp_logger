#ifndef _LOGGER_ENUMS_H
#define _LOGGER_ENUMS_H

// ======================================================================

#include <string>

// ======================================================================

namespace logger {

// ======================================================================

enum class Color : unsigned short int {
	NONE   = 0,
	BLACK  = 30,
	RED	   = 31,
	GREEN  = 32,
	YELLOW = 33,
	BLUE   = 34,
	PURPLE = 35,
	CYAN   = 36,
	WHITE  = 37,
};

// ======================================================================

enum class Depth : unsigned short int {
	TRACE = 0,	  // Almost too much information
	DEBUG,		  // Relevant information while actively debugging an issue
	INFO,		  // Information about processes which don't require attention
	WARNING,	  // Potential issues which may be ignored
	ERROR,		  // Issues which prevent/affect core funtionality
	CRITICAL,	  // The process is about to crash
	NONE		  // Will always be displayed
};

// ----------------------------------------------------------------------

size_t longest_depth_length();
std::string to_string( Depth depth );
Color to_color( Depth depth );

// ======================================================================

}	 // namespace logger

// ======================================================================

#endif
