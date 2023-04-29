#pragma once

#include <AlbedoLog.hpp>

#include <optional>
#include <string>
#include <string_view>
#include <tuple>

namespace Albedo {
 namespace Hub{
 namespace Client{
 namespace Runtime
 {
     using EventResult = std::tuple<bool, std::string>;

     class RuntimeEvent
     {
     public:
         static void trigger(bool result, std::string feedback);
         static bool isTriggered() { return sm_result.has_value(); }
         static EventResult getResult();

     protected:
         inline static std::optional<bool> sm_result;
         inline static std::string sm_feed_back;
     };
 	
     class RegisterEvent : public RuntimeEvent
     {
     public:
         static void sendUserInfo(std::string name, std::string account, std::string password);
         static void sendVerificationCode(std::string verification_code);
     };

     class SignIOEvent : public RuntimeEvent
     {
     public:
         static void sendSignInInfo(std::string account, std::string password);
     };

 }}}} // namespace Albedo::Hub::Client::Runtime