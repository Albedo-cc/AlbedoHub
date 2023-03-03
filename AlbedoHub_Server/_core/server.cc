#include <AlbedoLog.hpp>
#define ALBEDONET_SERVER
#include <AlbedoNet.hpp>

#include "database/database.h"
#include "database/tables/authentication.h"

#include <register.pb.h>

#include <iostream>
#include <string>
#include <thread>

#include "handlers/register/register.mail.h"

int main(int argc, char* argv[])
{
	using namespace Albedo;
	Register::UserInfo user_info;
	
	
	try
	{
        net::SMTP smtp{ "hub@albedo.cc" , "@albedo741", "smtps://smtpout.secureserver.net", 465 };

		register_mail::set_name("Frozen"); // ANSI ! future > UTF-8
		register_mail::set_vcode("123456");

        net::Mail mail{
			"Albedo Hub <hub@albedo.cc>", 
			{"745574309@qq.com", "ljyc.me@gmail.com"},
			{},
			"[Albedo Hub] Register Verification Code", 
			register_mail::get()};
		smtp.send(mail);

	/*	net::Server server{ 5200 };
		server.start();
		while (true)
		{
			server.handle();
		}*/
	}
	catch (std::runtime_error& e)
	{
		log::error("Albedo Hub (Server): {}", e.what());
	}


	return 0;
}
//
////AuthenTable::insert("745574309@qq.com", net::Hash::SHA256("123321"));
//
//auto p = AuthenTable::search("Account = '745574309@qq.com' ");
//auto result = p->get_result();
//if (!result || result->empty()) log::error("Result empty!");
//else
//{
//	auto user = result->fetch_first();
//	if (user.empty()) log::error("Result empty!");
//	else log::info("UID:{}\nAccount:{}\nPassword:{}", user["UID"], user["Account"], user["Password"]);
//}