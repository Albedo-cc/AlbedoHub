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
 	
     struct RegisterEvent
     {
         static void trigger(bool result, std::string feedback);
         static bool isTriggered() { return sm_result.has_value(); }
         static EventResult getResult();

         static void sendUserInfo(std::string name, std::string account, std::string password);
         static void sendVerificationCode(std::string verification_code);

     private:
         static std::optional<bool> sm_result;
         static std::string sm_feed_back;
     };

 }}}} // namespace Albedo::Hub::Client::Runtime