/*
 * DSMR parser controller endpoint.
 *
 * @author Michel Megens
 * @email  michel@michelmegens.net
 */

#pragma once

#include <basic_controller.hpp>
#include <controller.hpp>

namespace api
{
	using namespace logging::trivial;

	class ParserController : public api::BasicController, api::Controller {

	public:
		void handleGet(http_request message) override ;
		void handlePost(http_request message) override ;
		void handlePatch(http_request message) override;
		void handlePut(http_request message) override;
		void handleDelete(http_request message) override;

		void initRestOpHandlers() override;

	private:
		src::severity_logger<severity_level> lg;

		/* Methods */
		void handleBulkParseRequest(http_request& message) const;
		void handleParseRequest(http_request& message) const;
	};
}
