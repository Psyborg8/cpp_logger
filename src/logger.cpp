// ======================================================================

#include "logger.h"

// ----------------------------------------------------------------------

#include <cstdio>
#include <ctime>
#include <curses.h>
#include <filesystem>
#include <fmt/format.h>
#include <fstream>

// ======================================================================

namespace logger {

// ======================================================================

enum class LogType { CONSOLE = 0, FILE };

// ======================================================================

Settings g_defaults{ Settings() };
size_t g_longest_name{ 0u };

// ----------------------------------------------------------------------

std::string get_time_string( std::string format );
std::string color_string( std::string str, Color col );
std::string create_log_string( std::string msg,
							   const Settings& settings,
							   LogType type,
							   Depth depth,
							   size_t indentation );
void write_to_file( std::string str, const Settings& settings );

// ======================================================================

void set_defaults( const Settings& defaults ) {
	g_defaults = defaults;
}

// ----------------------------------------------------------------------

const Settings& get_defaults() {
	return g_defaults;
}

// ----------------------------------------------------------------------

void reset() {
	g_longest_name = 0u;
}

// ======================================================================
// String helper functions
// ======================================================================

void indent_string( std::string& str, size_t indent ) {
	std::string indent_str;
	indent_str.resize( indent, ' ' );
	str = indent_str + str;
}

// ======================================================================

Logger::Logger() : m_settings( g_defaults ) {
	if( m_settings.name.length() > g_longest_name )
		g_longest_name = m_settings.name.length();
}

// ----------------------------------------------------------------------

Logger::Logger( Settings settings ) : m_settings( settings ) {
	if( m_settings.name.length() > g_longest_name )
		g_longest_name = m_settings.name.length();
}

// ----------------------------------------------------------------------

void Logger::set_settings( Settings settings ) {
	m_settings = settings;

	if( settings.name.length() > g_longest_name )
		g_longest_name = settings.name.length();
}

// ----------------------------------------------------------------------

void Logger::log( std::string message, Depth depth, size_t indentation ) const {
	if( static_cast< uint8_t >( depth ) < static_cast< uint8_t >( m_settings.visible_depth ) )
		return;


	// Print console message
	if( m_settings.console_enabled ) {
		std::string console_str = create_log_string(
			message, m_settings, LogType::CONSOLE, depth, indentation );
		printf( "%s\n", console_str.c_str() );
	}

	// Write file message
	if( m_settings.file_enabled ) {
		std::string file_str = create_log_string(
			message, m_settings, LogType::FILE, depth, indentation );
		write_to_file( file_str, m_settings );
	}
}

// ----------------------------------------------------------------------

void Logger::log_separator( std::string str, Depth depth ) const {
	if( static_cast< uint8_t >( depth ) < static_cast< uint8_t >( m_settings.visible_depth ) )
		return;

	// Print console separator
	if( m_settings.console_enabled ) {
		std::string console_str = str;
		if( m_settings.console_color_enabled )
			console_str = color_string( console_str, to_color( depth ) );

		printf( "%s\n", console_str.c_str() );
	};

	// Write file separator
	if( m_settings.file_enabled ) {
		std::string file_str = str;
		write_to_file( file_str, m_settings );
	}
}

// ----------------------------------------------------------------------

void Logger::log_separator( char character, Depth depth ) const {
	if( static_cast< uint8_t >( depth ) < static_cast< uint8_t >( m_settings.visible_depth ) )
		return;

	// Print console separator
	if( m_settings.console_enabled ) {
		std::string console_str;
		console_str.resize( m_settings.console_separator_length, character );
		printf( "%s\n", console_str.c_str() );
	}

	// Write file separator
	if( m_settings.file_enabled ) {
		std::string file_str;
		file_str.resize( m_settings.file_separator_length, character );
		write_to_file( file_str, m_settings );
	}
}

// ======================================================================

std::string get_time_string( std::string format ) {
	time_t t	  = std::time( nullptr );
	tm* localtime = std::localtime( &t );

	char* time_str = new char[1024u];
	std::strftime( time_str, 1024u, format.c_str(), localtime );

	return std::string( time_str );
}

// ----------------------------------------------------------------------

std::string color_string( std::string str, Color col ) {
	return fmt::format( "\033[1m\033[{}m{}\033[0m", static_cast< int >( col ), str );
}

// ----------------------------------------------------------------------

std::string create_log_string( std::string msg,
							   const Settings& settings,
							   LogType type,
							   Depth depth,
							   size_t indentation ) {
	std::string out;
	out.reserve( 1024u );
	out.resize( indentation, ' ' );

	// Timestamp
	if( type == LogType::FILE )
		out += get_time_string( settings.date_time_format ) + " - ";

	// Name
	std::string name = settings.name;
	size_t diff		 = 0u;
	if( name.length() < g_longest_name )
		diff = g_longest_name - name.length();
	else
		g_longest_name = name.length();

	name = fmt::format( "[{}]", name );
	name.resize( name.length() + diff, ' ' );
	out += fmt::format( "{} | ", name );

	// Depth
	if( depth != Depth::NONE ) {
		std::string depth_str = to_string( depth );

		if( type == LogType::CONSOLE && settings.console_color_enabled )
			depth_str = color_string( depth_str, to_color( depth ) );

		out += fmt::format( "{} - ", depth_str );
	}

	// Message
	out += msg;

	return out;
}

// ----------------------------------------------------------------------

void write_to_file( std::string str, const Settings& settings ) {
	std::filesystem::path path{ std::filesystem::current_path() };
	path /= settings.file_directory;
	path /= settings.file_name;

	if( path.has_parent_path() && !std::filesystem::exists( path.parent_path() ) )
		std::filesystem::create_directories( path.parent_path() );

	std::ofstream ofs( path );
	if( !ofs.is_open() ) {
		printf( "WARNING - logger::write_to_file : Cannot open log file '%s'\n",
				path.c_str() );
		return;
	}

	ofs << str.c_str();
	ofs.close();
}

// ======================================================================

}	 // namespace logger

// ======================================================================
