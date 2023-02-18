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

std::string to_string( Depth depth ) {
	switch( depth ) {
		case Depth::TRACE: return "TRACE";
		case Depth::DEBUG: return "DEBUG";
		case Depth::INFO: return "INFO";
		case Depth::WARNING: return "WARNING";
		case Depth::ERROR: return "ERROR";
		case Depth::CRITICAL: return "CRITICAL";
		default: return "";
	}
}

// ----------------------------------------------------------------------

Color to_color( Depth depth ) {
	switch( depth ) {
		case Depth::TRACE: return Color::BLUE;
		case Depth::DEBUG: return Color::GREEN;
		case Depth::INFO: return Color::CYAN;
		case Depth::WARNING: return Color::YELLOW;
		case Depth::ERROR: return Color::RED;
		case Depth::CRITICAL: return Color::PURPLE;
		default: return Color::NONE;
	}
}

// ======================================================================

}	 // namespace logger

// ======================================================================

#endif
