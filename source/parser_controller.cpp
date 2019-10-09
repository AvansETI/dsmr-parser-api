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

	void ParserController::handlePut(http_request message)
	{
	}

	void ParserController::handlePost(http_request message)
	{
		std::string datagram;
		dsmr::DefaultParser parser;

		message.extract_json().then([&](json::value json) {
			auto& data = json.at("datagram").as_string();
			datagram.append(data);
			auto result = parser.parse(datagram);
			message.reply(status_codes::OK, result);
		});
	}

	void ParserController::handleDelete(http_request message)
	{
	}

	void ParserController::handlePatch(http_request messge)
	{
	}

	void ParserController::handleHead(http_request message)
	{
	}

	void ParserController::handleOptions(http_request message)
	{
	}

	void ParserController::handleTrace(http_request message)
	{
	}

	void ParserController::handleConnect(http_request message)
	{
	}

	void ParserController::handleMerge(http_request message)
	{
	}

	void ParserController::initRestOpHandlers()
	{
		BasicController::initRestOpHandlers();

		this->_listener.support(methods::GET, std::bind(&ParserController::handleGet, this, std::placeholders::_1));
		this->_listener.support(methods::POST, std::bind(&ParserController::handlePost, this, std::placeholders::_1));
	}
}