#pragma once

#include "../../service/mail/mail_service.h"

#include <AlbedoNet.hpp>
#include <signio_protocol.pb.h>

#include <unordered_map>
#include <memory>
#include <random>
#include <chrono>
#include <string>

namespace Albedo {
namespace Hub{
namespace Server{
namespace Handler
{
	
	class HSignIO
		:public net::Handler
	{
	public:
		virtual void handle(std::shared_ptr<net::Envelope> message) override;
		virtual ~HSignIO() override  = default;
	};

}}}} // namespace Albedo::Hub::Server::Handler