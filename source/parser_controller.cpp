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
			auto query = uri::split_query(message.request_uri().query());

			// [] Returns empty string if not present
			bool bulk = query["bulk"] == "true";

			if(bulk) {
				this->handleBulkParseRequest(message);
				BOOST_LOG_SEV(lg, info) << "Bulk parse request received from: " << message.remote_address();
			} else {
				this->handleParseRequest(message);
				BOOST_LOG_SEV(lg, info) << "Parse request received from: " << message.remote_address();
			}

		} catch(std::exception& e) {
			BOOST_LOG_SEV(lg, info) << "Parse request failed from: " << message.remote_address();
			BOOST_LOG_SEV(lg, info) << e.what();
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

	void ParserController::handleParseRequest(http_request& message) const
	{
		message.extract_json().then([&](json::value json) {
			dsmr::DefaultParser parser;
			auto data = json.at("datagram").as_string();

			auto result = parser.parse(data);
			message.reply(status_codes::OK, result, "application/json");
		}).get();
	}

	void ParserController::handleBulkParseRequest(http_request &message) const
	{
		message.extract_json().then([&](json::value json) {
			dsmr::DefaultParser parser;
			auto data = json.as_array();
			std::vector<std::string> datagrams;

			for(auto& entry : data) {
				std::cout << entry.at("datagram") << std::endl;
				datagrams.emplace_back(entry.at("datagram").as_string());
			}

			auto result = parser.parse(datagrams);
			message.reply(status_codes::OK, result, "application/json");
		}).wait();
	}
}