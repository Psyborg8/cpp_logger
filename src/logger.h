#ifndef _LOGGER_H
#define _LOGGER_H

/***********************************************************************/
/***************************** LOGGER.H ********************************/
/***********************************************************************/

// A light-weight header-only library to standardize logging
// in my own projects.

// **********************************************************************
// FORMATTING:
//      Format strings support the following options:
//          $t - The date/time stamp (using the dateTimeFormat string )
//          $d - The depth string
//          $m - The log message
//          $n - Logger name
// **********************************************************************


#include <string>

// ----------------------------------------------------------------------

#include "cursor.h"
#include "enums.h"

// ======================================================================

namespace logger {

// ======================================================================
// Settings

struct Settings {
	std::string name{ "CORE" };
	Depth visible_depth{ Depth::WARNING };

	// Format
	std::string date_time_format{ "%Y-%m-%d-%H:%M:%S" };

	// Console Logging
	bool console_color_enabled{ true };
	size_t console_separator_length{ 32u };
	bool console_enabled{ true };

	// File Logging
	std::string file_directory{ "logs" };
	std::string file_name{ "output" };
	size_t file_separator_length{ 32u };
	bool file_enabled{ true };
};

// ======================================================================
// Defaults

// Get/Set the default settings struct for newly constructed loggers
void set_default( const Settings& defaults );
const Settings& get_defaults();

// Reset the indentation level
void reset();

// ======================================================================

class Logger {
public:
	Logger();
	Logger( Settings settings );

public:
	void log( std::string message, Depth depth = Depth::NONE ) const;
	void log_separator( std::string str, Depth depth = Depth::NONE ) const;
	void log_separator( char character, Depth depth = Depth::NONE ) const;

	void set_settings( Settings settings );
	inline Settings get_settings() const { return m_settings; }

private:
	Settings m_settings;
};

// ======================================================================

}	 // namespace logger

// ======================================================================

#endif
