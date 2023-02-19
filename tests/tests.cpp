// ======================================================================

#include <filesystem>
#include <fmt/format.h>
#include <logger.h>

// ======================================================================

void write_test( const logger::Logger& logger );

// ======================================================================

int main( int argc, char** argv ) {
	// Test One
	logger::Logger test_one;
	logger::Logger test_two;
	logger::Logger test_three;
	logger::Logger test_four;

	logger::Settings settings;
	{
		settings		   = test_one.get_settings();
		settings.name	   = "TEST ONE";
		settings.file_name = "test_one.log";
		test_one.set_settings( settings );
	}
	{
		settings					   = test_two.get_settings();
		settings.name				   = "TEST TWO";
		settings.visible_depth		   = logger::Depth::TRACE;
		settings.console_color_enabled = true;
		settings.file_name			   = "test_two.log";
		test_two.set_settings( settings );
	}
	{
		settings					   = test_three.get_settings();
		settings.name				   = "TEST THREE";
		settings.file_enabled		   = false;
		settings.console_color_enabled = false;
		test_three.set_settings( settings );
	}
	{
		settings				 = test_four.get_settings();
		settings.name			 = "TEST FOUR";
		settings.console_enabled = false;
		settings.file_name		 = "test_four.log";
		test_four.set_settings( settings );
	}


	test_one.log_separator( '=' );
	printf( "LOGGER TESTS\n" );
	test_one.log_separator( '=' );

	test_one.log( "name: \"TEST ONE\"" );
	write_test( test_one );

	test_two.log( "name: \"TEST TWO\", visible_depth: TRACE" );
	write_test( test_two );

	test_three.log( "name: \"TEST THREE\", file_enabled = false, console_color_enabled = false" );
	write_test( test_three );

	test_four.log( "name: \"TEST FOUR\", console_enabled = false" );
	write_test( test_four );

	logger::reset();

	// Example
	logger::Logger example;
	logger::Logger example_2;

	{
		settings		   = example.get_settings();
		settings.file_name = "example.log";
		example.set_settings( settings );
	}
	{
		settings		   = example_2.get_settings();
		settings.name	   = "MODULE";
		settings.file_name = "example.log";
		example_2.set_settings( settings );
	}

	example.log_separator( "==== EXAMPLE" );
	example.log_separator( '-' );

	example.log( "Time to do some stuff" );
	example.log( "Generating example messages" );
	example.log( "Scary warning, you can probably ignore it", logger::Depth::WARNING );
	example.log( "Another scary warning, you can probably ignore it", logger::Depth::WARNING );
	example.log( "That's a lot of warnings", logger::Depth::WARNING );
	example.log( "AH! An error!", logger::Depth::ERROR );
	example_2.log( "Stuff's breaking over here too!", logger::Depth::ERROR );
	example_2.log( "We have warnings too", logger::Depth::WARNING );
	example.log( "Something's not right", logger::Depth::WARNING );
	example.log( "Oops.", logger::Depth::CRITICAL );
	example.log( "Successful!" );

	example.log_separator( '=' );

	return 0;
}

// ======================================================================

void write_test( const logger::Logger& logger ) {
	logger.log_separator( '=' );

	for( logger::Depth depth = logger::Depth::TRACE; depth < logger::Depth::NONE;
		 depth = static_cast< logger::Depth >( static_cast< uint8_t >( depth ) + 1 ) ) {
		logger.log( fmt::format( "depth: {}", logger::to_string( depth ) ), depth );
	}

	logger.log_separator( "====== String Separator =======" );
	logger.log_separator( '=' );
}

// ======================================================================
