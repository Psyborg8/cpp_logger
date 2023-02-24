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

Settings _defaults{ Settings() };
size_t _longest_name{ 0u };

// ======================================================================
// Defaults
// ======================================================================

void set_defaults( const Settings& defaults ) {
	_defaults = defaults;
}

// ----------------------------------------------------------------------

const Settings& get_defaults() {
	return _defaults;
}

// ----------------------------------------------------------------------

void reset() {
	_longest_name = 0u;
}

// ======================================================================
// String helper functions
// ======================================================================

std::string indent_string( std::string str, size_t indent ) {
	std::vector< std::string > lines = split_string( str, "\n" );
	std::string indent_str;
	indent_str.resize( indent, ' ' );

	std::string out;

	for( size_t i = 0u; i < lines.size(); ++i ) {
		out += indent_str;
		out += lines.at( i );

		if( i < lines.size() - 1u )
			out += '\n';
	}

	return out;
}

// ----------------------------------------------------------------------

std::vector< std::string > split_string( std::string str, std::string delim ) {
	std::vector< std::string > out;

	std::string str_cpy = str;
	size_t pos			= str_cpy.find( delim );

	while( pos != std::string::npos ) {

		out.push_back( str_cpy.substr( 0, pos ) );
		str_cpy.erase( 0, pos + delim.size() );
		pos = str_cpy.find( delim );
	}

	if( !str_cpy.empty() )
		out.push_back( str_cpy );

	return out;
}

// ======================================================================
// CLASS: Logger
// ======================================================================

Logger::Logger( std::string name ) : m_name( name ), m_settings( _defaults ) {
	if( name.length() > _longest_name )
		_longest_name = name.length();
}

// ----------------------------------------------------------------------

Logger::Logger( Settings settings, std::string name ) :
	m_name( name ), m_settings( settings ) {
	if( name.length() > _longest_name )
		_longest_name = name.length();
}

// ----------------------------------------------------------------------

void Logger::set_settings( Settings settings ) {
	m_settings = settings;
}

// ----------------------------------------------------------------------

void Logger::log( std::string message, Depth depth, size_t indentation ) const {
	if( static_cast< uint8_t >( depth ) < static_cast< uint8_t >( m_settings.visible_depth ) )
		return;

	std::vector< std::string > lines = split_string( message, "\n" );

	for( std::string line : lines ) {
		if( m_settings.console_enabled )
			printf( "%s\n",
					create_console_string( indent_string( line, indentation ), depth )
						.c_str() );

		if( m_settings.file_enabled )
			printf(
				"%s\n",
				create_file_string( indent_string( line, indentation ), depth ).c_str() );
	}
}

// ----------------------------------------------------------------------

void Logger::log_separator( std::string str, Depth depth ) const {
	if( static_cast< uint8_t >( depth ) < static_cast< uint8_t >( m_settings.visible_depth ) )
		return;

	if( str.find( '\n' ) ) {}

	// Print console separator
	if( m_settings.console_enabled ) {
		printf( "%s\n", str.c_str() );
	};

	// Write file separator
	if( m_settings.file_enabled ) {
		std::string file_str = str;
		write_to_file( file_str );
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
		write_to_file( file_str );
	}
}

// ----------------------------------------------------------------------

std::string Logger::get_time_string() const {
	time_t t	  = std::time( nullptr );
	tm* localtime = std::localtime( &t );

	char* time_str = new char[1024u];
	std::strftime( time_str, 1024u, m_settings.date_time_format.c_str(), localtime );

	return std::string( time_str );
}

// ----------------------------------------------------------------------

std::string Logger::create_console_string( std::string msg, Depth depth ) const {
	std::string out;
	out.reserve( 1024u );

	size_t whitespace = ( _longest_name + longest_depth_length() ) - m_name.length();

	std::string depth_str;
	if( depth != Depth::NONE ) {
		whitespace -= to_string( depth, false ).length();

		if( m_settings.console_color_enabled )
			depth_str = to_string( depth );
		else
			depth_str = to_string( depth, false );
	}

	std::string title_str;
	if( depth_str.empty() )
		title_str = fmt::format( "[{}]", m_name );
	else
		title_str = fmt::format( "[{}|{}]", m_name, depth_str );

	title_str.resize( title_str.length() + whitespace, ' ' );
	out += title_str + " | ";

	// Message
	out += msg;

	return out;
}

// ----------------------------------------------------------------------

std::string Logger::create_file_string( std::string msg, Depth depth ) const {
	std::string out;
	out.reserve( 1024u );

	// Time string
	out += fmt::format( "{} - ", get_time_string() );

	if( depth != Depth::NONE ) {
		// Depth
		std::string depth_str = to_string( depth );

		// Name
		std::string name_str = fmt::format( "[{} | {}]", m_name, depth_str );
		name_str.resize( _longest_name + to_string( Depth::CRITICAL ).length() + 2, ' ' );
		out += name_str;
	}
	else {
		// Name
		std::string name = fmt::format( "[{}]", m_name );
		name.resize( _longest_name + 2u, ' ' );
		out += fmt::format( "{} | ", name );
	}

	// Message
	out += msg;

	return out;
}

// ----------------------------------------------------------------------

void Logger::write_to_file( std::string str ) const {
	std::filesystem::path path{ std::filesystem::current_path() };
	path /= m_settings.file_directory;
	path /= m_settings.file_name;

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
