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
	class ParserController : public api::BasicController, api::Controller {
	public:
		void handleGet(http_request message) ;
		void handlePost(http_request message) ;
		void initRestOpHandlers() override;

	};
}
