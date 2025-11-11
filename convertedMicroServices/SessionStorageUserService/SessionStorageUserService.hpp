#pragma once

#include <memory>
#include "../Types/User/User.hpp"

class SessionStorageUserService {
    public:
        SessionStorageUserService();
        User getLoggedUser();
        User* getUserInLocalStorage();
        void setLoggedUser(User user);
    private:
        std::unique_ptr<User> loggedUser;
};
