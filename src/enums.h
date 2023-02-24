#ifndef _LOGGER_ENUMS_H
#define _LOGGER_ENUMS_H

// ======================================================================

#include <string>

// ======================================================================

namespace logger {

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
std::string to_string( Depth depth, bool format = true );

// ======================================================================

}	 // namespace logger

// ======================================================================

#endif
