/*
 * Parser controller implementation.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <stdlib.h>
#include <iostream>

#include <parsercontroller.h>
#include <basic_controller.hpp>

#include <dsmr/defaultparser.h>

namespace api
{
	void ParserController::handleGet(http_request message)
	{
		auto response = json::value::object();

		response["status"] = json::value::string("OK");
		response["version"] = json::value::string("v0.0.1");

		message.reply(status_codes::OK, response);
	}

	void ParserController::handlePost(http_request message)
	{
		try {

			message.extract_json().then([&](json::value json) {
				dsmr::DefaultParser parser;
				auto data = json.at("datagram").as_string();

				auto result = parser.parse(data);
				std::cout << result << std::endl;
				message.reply(status_codes::OK, result);
			});
		} catch(std::exception& e) {
			std::cout << "Unable to handle request: " << e.what();
			message.reply(status_codes::InternalError);
		} catch(...) {
			message.reply(status_codes::InternalError);
		}
	}

	void ParserController::initRestOpHandlers()
	{
		BasicController::initRestOpHandlers();

		this->_listener.support(methods::GET, std::bind(&ParserController::handleGet, this, std::placeholders::_1));
		this->_listener.support(methods::POST, std::bind(&ParserController::handlePost, this, std::placeholders::_1));
	}
}