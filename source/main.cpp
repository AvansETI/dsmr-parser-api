/*
 * API entry point.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <exception>

#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>
#include <stdlib.h>
#include <parsercontroller.h>

int main(int argc, char** argv)
{
	api::ParserController server;
	server.setEndpoint("http://localhost:5000/parser");

	std::cout << "Starting server!" << std::endl;

	try {
		server.accept().wait();
		api::InterruptHandler::waitForUserInterrupt();
		server.shutdown();
	} catch(std::exception& e) {
		std::cout << "Server error: " << e.what() << std::endl;
	}

	return -EXIT_SUCCESS;
}