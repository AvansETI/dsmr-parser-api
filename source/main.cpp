/*
 * API entry point.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <exception>

#include <usr_interrupt_handler.hpp>
#include <std_micro_service.hpp>
#include <runtime_utils.hpp>
#include <stdlib.h>
#include <parsercontroller.h>

#include <boost/log/expressions.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

static constexpr const char *filename = "parser-api_%N.log";
static constexpr const char *format   = "[%TimeStamp%]: %Message%";
static constexpr uint32_t rotation_size = 1024*1024*10;

using namespace logging::trivial;

void setup_logging()
{
	auto core = logging::core::get();

	logging::add_file_log
	(
		keywords::file_name = filename,
		keywords::rotation_size = rotation_size,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = format,
		keywords::auto_flush = true
	);

	boost::log::add_console_log(std::cout, keywords::format = format, keywords::auto_flush = true);

 	core->set_filter(logging::trivial::severity >= logging::trivial::info);
 	logging::add_common_attributes();
}

int main(int argc, char** argv)
{
 	setup_logging();

	api::ParserController server;
	server.setEndpoint("http://localhost:5000/parser");

	src::severity_logger<severity_level> lg;

	BOOST_LOG_SEV(lg, warning) << "Starting server!";

	try {
		server.accept().wait();
		api::InterruptHandler::waitForUserInterrupt();
		BOOST_LOG_SEV(lg, warning) << "Stopping server..";
		server.shutdown();
		BOOST_LOG_SEV(lg, warning) << "Server stopped!";
	} catch(std::exception& e) {
		std::cout << "Server error: " << e.what() << std::endl;
	}

	return -EXIT_SUCCESS;
}