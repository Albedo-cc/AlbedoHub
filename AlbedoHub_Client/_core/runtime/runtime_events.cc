#pragma once

#include "runtime_events.h"
#include "../global_context.h"

#include <AlbedoProtocol.pb.h>
#include <register_protocol.pb.h>
#include <signio_protocol.pb.h>

namespace Albedo {
 namespace Hub{
 namespace Client{
 namespace Runtime
 {
        static auto& g_context = GlobalContext::instance();
        static auto& g_context_net = g_context.g_context_Net;

        void SignIOEvent::sendSignInInfo(std::string account, std::string password)
        {
            if (!isTriggered())
            {
                if (!g_context_net.isOnline) return RuntimeEvent::trigger(false, "Offline");

                SignIOProtocol::SignInInfo signinInfo;
                signinInfo.set_account(std::move(account));
                signinInfo.set_password(std::move(net::Hash::SHA256(password)));
                g_context_net.sendMessage
                (
                    net::Message{ AlbedoProtocol::PID::SIGNIN_REQUEST, signinInfo.SerializeAsString() }
                );
            }
            else throw std::runtime_error("Failed to start a triggered event before call getResult()!");
        }

        void RegisterEvent::sendUserInfo(std::string name, std::string account, std::string password)
        {
            if (!isTriggered())
            {
                if (!g_context_net.isOnline) return RuntimeEvent::trigger(false, "Offline");

                RegisterProtocol::UserInfo userinfo;
                userinfo.set_name(std::move(name));
                userinfo.set_account(std::move(account));
                userinfo.set_password(std::move(net::Hash::SHA256(password)));
                g_context_net.sendMessage
                (
                    net::Message{ 
                    AlbedoProtocol::PID::REGISTER_CLIENT_SEND_REQUEST,
                    userinfo.SerializeAsString()}
                );
            }
            else throw std::runtime_error("Failed to start a triggered event before call getResult()!");
        }

        void RegisterEvent::sendVerificationCode(std::string verification_code)
        {
            if (!isTriggered())
            {
                if (!g_context_net.isOnline) return RuntimeEvent::trigger(false, "Offline");

                RegisterProtocol::Verification verfication;
                verfication.set_verification_code(std::move(verification_code));
                g_context.g_context_Net.sendMessage
                (
                    net::Message{
                    AlbedoProtocol::PID::REGISTER_CLIENT_SEND_VERIFICATION,
                    verfication.SerializeAsString() }
                );
            }
            else throw std::runtime_error("Failed to start a triggered event before call getResult()!");
        }

        void RuntimeEvent::trigger(bool result, std::string feedback)
        {
            if (isTriggered())
                throw std::runtime_error("Failed to trigger a triggered event!");

            sm_result = result;
            sm_feed_back = std::move(feedback);
        }

        EventResult RuntimeEvent::getResult()
        { 
            if (!isTriggered())
                throw std::runtime_error("Failed to get an empty result! - Untriggered");

            EventResult result { sm_result.value() ,sm_feed_back};
            sm_result.reset();
            return result;
        }

 }}}} // namespace Albedo::Hub::Client::Runtime