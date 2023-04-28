#pragma once

#include <AlbedoPattern.hpp>

#include <dock_protocol.pb.h>

#include <string>
#include <vector>
#include <string_view>
#include <unordered_map>

namespace Albedo {
namespace Hub{
namespace Server
{

	class Harbor :
		public pattern::Singleton<Harbor>
	{
		friend class pattern::Singleton<Harbor>;
		Harbor() = default;

	public:
		using Docker = DockProtocol::ShakeHand;
		void AddDocker(Docker& docker)
		{
			auto target = m_dockers.find(docker.name());
			if (target == m_dockers.end())
			{
				m_dockers.emplace(docker.name(), std::move(docker));
				m_need_update = true;
			}
			else log::warn("Failed to add a docker named {}", docker.name());
		}

		const std::string& MakeDockerListString()
		{
			static std::string dockerList;
			if (m_need_update)
			{
				DockProtocol::DockerList dockers;
				for (const auto& [name, docker] : m_dockers)
				{
					auto pDocker = dockers.add_dockers();
					pDocker->set_name(docker.name());
					pDocker->set_intro(docker.intro());
					pDocker->set_pass(docker.pass());
					pDocker->set_limit(docker.limit());
					pDocker->set_address(docker.address());
					pDocker->set_port(docker.port());
				}
				dockers.SerializeToString(&dockerList);
				m_need_update = false;
			}
			return dockerList;
		}

	private:
		bool m_need_update = true;
		std::unordered_map<std::string_view, Docker> m_dockers;
	};

}}} // namespace Albedo::Hub::Server