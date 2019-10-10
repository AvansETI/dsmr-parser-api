/*
 * Parser controller implementation.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#include <stdlib.h>
#include <iostream>

#include <std_micro_service.hpp>
#include <parsercontroller.h>
#include <basic_controller.hpp>

#include <dsmr/defaultparser.h>

namespace api
{
	using namespace logging::trivial;

	void ParserController::handleGet(http_request message)
	{
		auto response = json::value::object();
		BOOST_LOG_SEV(lg, info) << "Version request received from: " << message.remote_address();

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
				BOOST_LOG_SEV(lg, info) << "Parse request received from: " << message.remote_address();
				message.reply(status_codes::OK, result);
			});
		} catch(std::exception& e) {
			std::cout << "Unable to handle request: " << e.what();
			message.reply(status_codes::InternalError);
		} catch(...) {
			message.reply(status_codes::InternalError);
		}
	}


	void ParserController::handlePatch(http_request message)
	{
		BOOST_LOG_SEV(lg, info) << "HTTP PATCH request received from: " << message.remote_address();
		message.reply(status_codes::MethodNotAllowed);
	}

	void ParserController::handlePut(http_request message)
	{
		BOOST_LOG_SEV(lg, info) << "HTTP PUT request received from: " << message.remote_address();
		message.reply(status_codes::MethodNotAllowed);
	}

	void ParserController::handleDelete(http_request message)
	{
		BOOST_LOG_SEV(lg, info) << "HTTP DELETE request received from: " << message.remote_address();
		message.reply(status_codes::MethodNotAllowed);
	}

	void ParserController::initRestOpHandlers()
	{
		BasicController::initRestOpHandlers();

		this->_listener.support(methods::GET, std::bind(&ParserController::handleGet, this, std::placeholders::_1));
		this->_listener.support(methods::POST, std::bind(&ParserController::handlePost, this, std::placeholders::_1));
		this->_listener.support(methods::PUT, std::bind(&ParserController::handlePut, this, std::placeholders::_1));
		this->_listener.support(methods::PATCH, std::bind(&ParserController::handlePatch, this, std::placeholders::_1));
		this->_listener.support(methods::DEL, std::bind(&ParserController::handleDelete, this, std::placeholders::_1));
	}
}