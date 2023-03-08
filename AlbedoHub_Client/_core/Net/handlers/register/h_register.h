#pragma once

#include <AlbedoNet.hpp>
#include <AlbedoProtocol.pb.h>

#include <memory>
#include <exception>

namespace Albedo {
namespace Hub{
namespace client{
namespace layer
{
	struct RegisterResult
	{
		RegisterResult() = delete;
		RegisterResult(AlbedoProtocol::PID pid) : pid{ pid }{}
		AlbedoProtocol::PID pid = AlbedoProtocol::PID::REGISTER_FAILED;
	};
	
	class HRegister:
		public net::Handler
	{
	public:
		virtual void handle(std::shared_ptr<net::SignedMessage> message) override;
	private:

	};

}}}} // namespace Albedo::Hub::client::layer