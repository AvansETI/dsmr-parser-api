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
	class ParserController : public cfx::BasicController, cfx::Controller {
		void handleGet(http_request message) override;

		void handlePut(http_request message) override;

		void handlePost(http_request message) override;

		void handleDelete(http_request message) override;

		void handlePatch(http_request messge) override;

		void handleHead(http_request message) override;

		void handleOptions(http_request message) override;

		void handleTrace(http_request message) override;

		void handleConnect(http_request message) override;

		void handleMerge(http_request message) override;

	public:
		void initRestOpHandlers() override;

	};
}
