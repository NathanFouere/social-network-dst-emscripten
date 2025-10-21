#pragma once
#include <cstdint>
#include <iostream>

class Creator {
    public:
        Creator() noexcept
                : user_id(0),
                username() {
        }
        int64_t getUserId() const;
        void setUserId(int64_t _user_id);
        int64_t user_id;
        std::string getUsername() const;
        void setUsername(std::string _username);
        std::string username;
};
