#pragma once

#include "../../service/mail/mail_service.h"

#include <AlbedoNet.hpp>
#include <dock_protocol.pb.h>

#include <unordered_map>
#include <memory>
#include <chrono>
#include <string>

namespace Albedo {
namespace Hub{
namespace Server{
namespace Handler
{
	
	class HDock
		:public net::Handler
	{
		using User = net::SPSession;
	public:
		virtual void handle(std::shared_ptr<net::Envelope> message) override;
		virtual ~HDock() override  = default;
	};

}}}} // namespace Albedo::Hub::Server::Handler