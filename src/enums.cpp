// ======================================================================

#include "enums.h"

// ----------------------------------------------------------------------

#include <unordered_map>

// ----------------------------------------------------------------------

#include "consoler.h"

// ======================================================================

namespace logger {

// ======================================================================

std::unordered_map< Depth, console::String > _depth_string_map{
	{ Depth::TRACE,
	  { "TRACE",
		{ console::Color_16::BRIGHT_BLUE, console::Color_16::DEFAULT, false, false, false, false, false, false, false, console::Underline_Mode::NONE } } },
	{ Depth::DEBUG,
	  { "DEBUG",
		{ console::Color_16::BRIGHT_GREEN, console::Color_16::DEFAULT, false, false, false, false, false, false, false, console::Underline_Mode::NONE } } },
	{ Depth::INFO,
	  { "INFO",
		{ console::Color_16::BRIGHT_CYAN, console::Color_16::DEFAULT, false, false, false, false, false, false, false, console::Underline_Mode::NONE } } },
	{ Depth::WARNING,
	  { "WARNING",
		{ console::Color_16::BRIGHT_YELLOW, console::Color_16::DEFAULT, false, false, false, false, false, false, false, console::Underline_Mode::NONE } } },
	{ Depth::ERROR,
	  { "ERROR",
		{ console::Color_16::BRIGHT_RED, console::Color_16::DEFAULT, false, false, false, false, false, false, false, console::Underline_Mode::NONE } } },
	{ Depth::CRITICAL,
	  { "CRITICAL",
		{ console::Color_16::BLACK, console::Color_16::BRIGHT_RED, false, false, false, false, false, false, false, console::Underline_Mode::NONE } } }
};

// ======================================================================

size_t longest_depth_length() {
	return to_string( Depth::CRITICAL, false ).length();
}

// ----------------------------------------------------------------------

std::string to_string( Depth depth, bool format ) {
	if( format )
		return _depth_string_map.at( depth ).format();
	else
		return _depth_string_map.at( depth ).get_string();
}

// ======================================================================

}	 // namespace logger

// ======================================================================
