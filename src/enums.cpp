// ======================================================================

#include "enums.h"

// ----------------------------------------------------------------------

#include <unordered_map>

// ======================================================================

namespace logger {

// ======================================================================

std::unordered_map< Depth, std::string > _depth_string_map{
	{ Depth::TRACE, "TRACE" }, { Depth::DEBUG, "DEBUG" },
	{ Depth::INFO, "INFO" },   { Depth::WARNING, "WARNING" },
	{ Depth::ERROR, "ERROR" }, { Depth::CRITICAL, "CRITICAL" },
	{ Depth::NONE, "NONE" },
};

// ----------------------------------------------------------------------

std::unordered_map< Depth, Color > _depth_color_map{
	{ Depth::TRACE, Color::BLUE }, { Depth::DEBUG, Color::GREEN },
	{ Depth::INFO, Color::CYAN },  { Depth::WARNING, Color::YELLOW },
	{ Depth::ERROR, Color::RED },  { Depth::CRITICAL, Color::PURPLE },
	{ Depth::NONE, Color::NONE },
};

// ======================================================================

// ----------------------------------------------------------------------

size_t longest_depth_length() {
	return to_string( Depth::CRITICAL ).length();
}

// ----------------------------------------------------------------------

std::string to_string( Depth depth ) {
	return _depth_string_map.at( depth );
}

// ----------------------------------------------------------------------

Color to_color( Depth depth ) {
	return _depth_color_map.at( depth );
}

// ======================================================================

}	 // namespace logger

// ======================================================================
