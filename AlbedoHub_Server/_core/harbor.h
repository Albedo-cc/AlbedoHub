#pragma once

#include <AlbedoPattern.hpp>

#include <dock_protocol.pb.h>

#include <string>
#include <vector>

namespace Albedo {
namespace Hub{
namespace Server
{

	class Harbor :
		public pattern::Singleton<Harbor>
	{
		friend class pattern::Singleton<Harbor>;
		Harbor()
		{
			m_dockers.emplace_back("Test", "A server for debugging", "ALBEDO", 1);
		};

	public:
		struct Docker
		{
			std::string name;
			std::string intro;
			std::string pass;
			int32_t limit = 0;
		};

		void AddDocker(Docker docker)
		{
			m_dockers.emplace_back(std::move(docker));
			m_need_update = true;
		}

		const std::string& MakeDockerListString()
		{
			static std::string dockerList;
			if (m_need_update)
			{
				DockProtocol::DockerList dockers;
				for (auto& docker : m_dockers)
				{
					auto pDocker = dockers.add_dockers();
					pDocker->set_name(docker.name);
					pDocker->set_intro(docker.intro);
					pDocker->set_pass(docker.pass);
					pDocker->set_limit(docker.limit);
				}
				dockers.SerializeToString(&dockerList);
				m_need_update = false;
			}
			return dockerList;
		}

	private:
		bool m_need_update = true;
		std::vector<Docker> m_dockers;
	};

}}} // namespace Albedo::Hub::Server