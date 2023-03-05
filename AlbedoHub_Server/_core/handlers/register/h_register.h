#pragma once

#include "../handler.h"

namespace Albedo {
namespace Hub{
namespace server{
namespace handler
{
	
	class HRegister
		:public Handler
	{
	public:
		virtual void handle(std::shared_ptr<net::SignedMessage> message) override;
	private:
		
	};

}}}} // namespace Albedo::Hub::server::handler