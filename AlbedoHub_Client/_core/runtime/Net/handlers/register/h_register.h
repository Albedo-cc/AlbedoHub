#pragma once

#include <AlbedoNet.hpp>
#include <AlbedoProtocol.pb.h>

#include <memory>
#include <string>
#include <exception>

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime{
namespace Handler
{

	class HRegister:
		public net::Handler
	{
	public:
		virtual void handle(std::shared_ptr<net::Envelope> message) override;
	private:

	};

}}}}} // namespace Albedo::Hub::Client::Runtime::Handler