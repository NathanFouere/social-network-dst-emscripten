#include "UserHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

UserHandler::UserHandler(
    SocialGraphHandler& socialGraphHandler
): socialGraphHandler(socialGraphHandler) {
}


void UserHandler::RegisterUserWithId(
    const int64_t req_id, const std::string &first_name,
    const std::string &last_name, const std::string &username,
    const std::string &password, const int64_t user_id) {

        // TODO: Le code lié à mongo est commenté pour le moment, il faudra voir comment s'en passer
        // Store user info into mongodb
        // mongoc_client_t *mongodb_client =
        //     mongoc_client_pool_pop(_mongodb_client_pool);
        // if (!mongodb_client) {
        //   ServiceException se;
        //   se.errorCode = ErrorCode::SE_MONGODB_ERROR;
        //   se.message = "Failed to pop a client from MongoDB pool";
        //   throw se;
        // }
        // auto collection =
        //     mongoc_client_get_collection(mongodb_client, "user", "user");

        // // Check if the username has existed in the database
        // bson_t *query = bson_new();
        // BSON_APPEND_UTF8(query, "username", username.c_str());
        // mongoc_cursor_t *cursor =
        //     mongoc_collection_find_with_opts(collection, query, nullptr, nullptr);
        // const bson_t *doc;
        // bson_error_t error;
        // bool found = mongoc_cursor_next(cursor, &doc);
        // if (mongoc_cursor_error(cursor, &error)) {
        //   LOG(warning) << error.message;
        //   bson_destroy(query);
        //   mongoc_cursor_destroy(cursor);
        //   mongoc_collection_destroy(collection);
        //   mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
        //   ServiceException se;
        //   se.errorCode = ErrorCode::SE_MONGODB_ERROR;
        //   se.message = error.message;
        //   throw se;
        // } else if (found) {
        //   LOG(warning) << "User " << username << " already existed.";
        //   ServiceException se;
        //   se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
        //   se.message = "User " + username + " already existed";
        //   bson_destroy(query);
        //   mongoc_cursor_destroy(cursor);
        //   mongoc_collection_destroy(collection);
        //   mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
        //   throw se;
        // } else {
        //   bson_t *new_doc = bson_new();
        //   BSON_APPEND_INT64(new_doc, "user_id", user_id);
        //   BSON_APPEND_UTF8(new_doc, "first_name", first_name.c_str());
        //   BSON_APPEND_UTF8(new_doc, "last_name", last_name.c_str());
        //   BSON_APPEND_UTF8(new_doc, "username", username.c_str());
        //   std::string salt = GenRandomString(32);
        //   BSON_APPEND_UTF8(new_doc, "salt", salt.c_str());
        //   std::string password_hashed = picosha2::hash256_hex_string(password + salt);
        //   BSON_APPEND_UTF8(new_doc, "password", password_hashed.c_str());

        //   bson_error_t error;
        //   if (!mongoc_collection_insert_one(collection, new_doc, nullptr, nullptr,
        //                                     &error)) {
        //     LOG(error) << "Failed to insert user " << username
        //                << " to MongoDB: " << error.message;
        //     ServiceException se;
        //     se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
        //     se.message =
        //         "Failed to insert user " + username + " to MongoDB: " + error.message;
        //     bson_destroy(query);
        //     mongoc_cursor_destroy(cursor);
        //     mongoc_collection_destroy(collection);
        //     mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
        //     throw se;
        //   } else {
        //     LOG(debug) << "User: " << username << " registered";
        //   }
        //   user_insert_span->Finish();
        //   bson_destroy(new_doc);
        // }
        // bson_destroy(query);
        // mongoc_cursor_destroy(cursor);
        // mongoc_collection_destroy(collection);
        // mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);

        // if (!found) {
        //   auto social_graph_client_wrapper = _social_graph_client_pool->Pop();
        //   if (!social_graph_client_wrapper) {
        //     ServiceException se;
        //     se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
        //     se.message = "Failed to connect to social-graph-service";
        //     throw se;
        //   }
        //   auto social_graph_client = social_graph_client_wrapper->GetClient();
        //   try {
        //     social_graph_client->InsertUser(req_id, user_id, writer_text_map);
        //   } catch (...) {
        //     _social_graph_client_pool->Remove(social_graph_client_wrapper);
        //     LOG(error) << "Failed to insert user to social-graph-client";
        //     throw;
        //   }
        //   _social_graph_client_pool->Keepalive(social_graph_client_wrapper);
        // }

        // TODO => pour le moment appelé avec rien
        this->socialGraphHandler.InsertUser(req_id, user_id);
    }



EMSCRIPTEN_BINDINGS(user_handler_module) {
    class_<UserHandler>("UserHandler")
    .constructor<SocialGraphHandler&>()
    .function("RegisterUserWithId", &UserHandler::RegisterUserWithId);
}
