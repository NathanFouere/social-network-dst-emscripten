#include "UserHandler.hpp"
#include <cstdint>
#include <cstdio>
#include <emscripten/bind.h>

using namespace emscripten;

UserHandler::UserHandler(
    SocialGraphHandler& socialGraphHandler,
    UniqueIdHandler& uniqueIdHandler
): socialGraphHandler(socialGraphHandler), uniqueIdHandler(uniqueIdHandler) {
}


void UserHandler::RegisterUserWithId(
    const std::string &first_name,
    const std::string &last_name, const std::string &username,
    const std::string &password, const int64_t user_id) {

    // TODO: Intégré persistence
    this->socialGraphHandler.InsertUser(user_id);
}

void UserHandler::RegisterUser(
    const std::string &first_name,
    const std::string &last_name,
    const std::string &username,
    const std::string &password
) {
    int64_t user_id = this->uniqueIdHandler.ComposeUniqueId();

     // TODO: Intégré persistence
     this->socialGraphHandler.InsertUser(user_id);
}



// Dans le userHandler original, trouve un creator par son username
Creator UserHandler::ComposeCreatorWithUsername(
    const std::string &username
) {
    Creator creator;
    creator.username = username;
    creator.user_id = 2; // TODO temporaire


    return creator;
}

// Dans le userHandler original, renvoie juste un creator
Creator UserHandler::ComposeCreatorWithUserId(
    int64_t user_id,
    const std::string &username
) {
    Creator creator;
    creator.username = username;
    creator.user_id = user_id;


    return creator;
}

// Dans le userHandler original, cherche d'abord dans le cache, puis dans mongo
// un user avec l'username donné et vérifie le password
std::string UserHandler::Login(
    const std::string &username,
    const std::string &password
) {
    std::cout << "UserHandler donné with username: " << username << std::endl;

    // TODO => renvoie un jwt

    return "jwt qui marche pas";
}

// Dans le UserHandler original, renvoie le user id correspondant au username
int64_t UserHandler::GetUserId(
    const std::string &username
) {
    // TODO => aller chercher en base le username correspondant
    return 4;
}

EMSCRIPTEN_BINDINGS(user_handler_module) {
    class_<UserHandler>("UserHandler")
    .constructor<SocialGraphHandler&, UniqueIdHandler&>()
    .function("RegisterUserWithId", &UserHandler::RegisterUserWithId)
    .function("ComposeCreatorWithUserId", &UserHandler::ComposeCreatorWithUserId)
    .function("ComposeCreatorWithUsername", &UserHandler::ComposeCreatorWithUsername)
    .function("GetUserId", &UserHandler::GetUserId)
    .function("Login", &UserHandler::Login)
    .function("RegisterUser", &UserHandler::RegisterUser);
}
