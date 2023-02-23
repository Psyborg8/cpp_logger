#ifndef _LOGGER_H
#define _LOGGER_H

// ======================================================================

#include <string>
#include <vector>

// ----------------------------------------------------------------------

#include "enums.h"

// ======================================================================

namespace logger {

// ======================================================================
// Settings

struct Settings {
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
// String helper functions

std::string indent_string( std::string str, size_t indent );
std::vector< std::string > split_string( std::string str, std::string delim );

// ======================================================================

class Logger {
public:
	Logger( std::string name = "CORE" );
	Logger( Settings settings, std::string name = "CORE" );

public:
	void log( std::string message, Depth depth = Depth::NONE, size_t indentation = 0u ) const;
	void log_separator( std::string str, Depth depth = Depth::NONE ) const;
	void log_separator( char character, Depth depth = Depth::NONE ) const;

	void set_settings( Settings settings );
	inline Settings get_settings() const { return m_settings; }
	inline Settings& get_settings() { return m_settings; }

private:
	std::string get_time_string() const;
	std::string color_string( std::string str, Color col ) const;
	std::string create_console_string( std::string msg, Depth depth ) const;
	std::string create_file_string( std::string msg, Depth depth ) const;
	void write_to_file( std::string str ) const;

private:
	std::string m_name;
	Settings m_settings;
};

// ======================================================================

}	 // namespace logger

// ======================================================================

#endif
