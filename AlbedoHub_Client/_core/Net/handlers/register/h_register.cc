#include "h_register.h"
#include "../../net_layer_context.h"

#include <AlbedoLog.hpp>
#include <register_protocol.pb.h>

#include <iostream>

namespace Albedo {
namespace Hub{
namespace client{
namespace layer
{
	
	void HRegister::handle(std::shared_ptr<net::SignedMessage> message)
	{
		auto message_id = message->header.message_id;

		if (message_id == AlbedoProtocol::REGISTER_CLIENT_SEND_VERIFICATION)
		{
			std::cout << message->body.message << '\n';
			std::string buffer;
			std::cout << "[Your VCode ] >>";
			std::cin >> buffer;
			RegisterProtocol::Verification vcode;
			vcode.set_verification_code(buffer);
			message->sender()->send(
				{ AlbedoProtocol::PID::REGISTER_CLIENT_SEND_VERIFICATION, 
				vcode.SerializeAsString()});
		}
		else if (message_id == AlbedoProtocol::REGISTER_SUCCESS)
		{
			log::info("REG SUCEESS: {}", message->body.message);
		}
		else if (message_id == AlbedoProtocol::REGISTER_FAILED)
		{
			log::info("REG FAILED: {}", message->body.message);
		}
		else throw std::runtime_error("Failed to handle register! - Unknow Protocol");
	}

}}}} // namespace Albedo::Hub::client::layer