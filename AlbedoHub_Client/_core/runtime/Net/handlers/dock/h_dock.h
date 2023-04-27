#pragma once

#include <AlbedoNet.hpp>

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime{
namespace Handler
{

	class HDock:
		public net::Handler
	{
	public:
		virtual void handle(std::shared_ptr<net::Envelope> message) override;
		virtual ~HDock() override = default;
	};

}}}}} // namespace Albedo::Hub::Client::Runtime::Handler