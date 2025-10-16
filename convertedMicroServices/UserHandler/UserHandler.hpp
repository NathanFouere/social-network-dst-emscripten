#pragma once

#include <iostream>
#include <string>
#include "../Types/Creator/Creator.hpp"
#include "../SocialGraphHandler/SocialGraphHandler.hpp"
#include <map>

class UserHandler {
    public:
        UserHandler(SocialGraphHandler& socialGraphHandler);
        void RegisterUserWithId(
            int64_t,
            const std::string &,
            const std::string &,
            const std::string &, 
            const std::string &, 
            int64_t
        );
    private:
        SocialGraphHandler& socialGraphHandler;
};
