/*
 * Base controller.
 *
 * @maintainer Michel Megens
 * @email michel@michelmegens.net
 */

#pragma once

#include <string>

#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

#include "controller.hpp"

using namespace web;
using namespace http::experimental::listener;

namespace api
{
    class BasicController {
    protected:
        http_listener _listener;

    public:
        BasicController() = default;
        virtual ~BasicController() = default;

        void setEndpoint(const std::string & value);
        std::string endpoint() const;
        pplx::task<void> accept();
        pplx::task<void> shutdown();

        virtual void initRestOpHandlers()
        {
        }

        std::vector<utility::string_t> requestPath(const http_request & message);
    };
}