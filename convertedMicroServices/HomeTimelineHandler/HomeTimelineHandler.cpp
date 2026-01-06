#include "HomeTimelineHandler.hpp"
#include <emscripten/bind.h>
#include <unordered_set>

using namespace emscripten;

HomeTimelineHandler::HomeTimelineHandler(PostStorageHandler &postStorageHandler,
                                         SocialGraphHandler &socialGraphHandler)
    : postStorageHandler(postStorageHandler),
      socialGraphHandler(socialGraphHandler) {};

std::vector<Post> HomeTimelineHandler::ReadHomeTimeline(int64_t user_id,
                                                        int start_idx,
                                                        int stop_idx,
                                                        bool only_friends) {
  // Ideally, filtering happens at the DB level or we fetch more posts to fill
  // the page, but for this MVP, we fetch a range and then filter. Note: This
  // might result in fewer than (stop-start) posts returned. A better approach
  // would be to GetData and filter until we satisfy the count, but let's keep
  // it simple.

  // NOTE: We fetch ALL posts here to ensure we have enough after filtering for
  // the demo. In production, this is bad practice.
  std::vector<Post> posts = this->postStorageHandler.GetAllPosts();

  std::cout << "ReadHomeTimeline called. only_friends: " << only_friends
            << std::endl;
  std::cout << "ReadHomeTimeline: Total posts fetched from storage: "
            << posts.size() << std::endl;

  if (only_friends) {
    std::vector<int64_t> followees =
        this->socialGraphHandler.GetFollowees(user_id);
    std::vector<int64_t> friends = this->socialGraphHandler.GetFriends(user_id);

    std::unordered_set<int64_t> allowed_ids;
    allowed_ids.insert(followees.begin(), followees.end());
    allowed_ids.insert(friends.begin(), friends.end());
    allowed_ids.insert(user_id); // Include self

    std::cout << "ReadHomeTimeline: Filtering. Allowed IDs count: "
              << allowed_ids.size() << std::endl;

    std::vector<Post> filtered_posts;
    filtered_posts.reserve(posts.size()); // Optimize allocation

    for (const auto &post : posts) {
      if (allowed_ids.find(post.creator.user_id) != allowed_ids.end()) {
        filtered_posts.push_back(post);
      }
    }

    std::cout << "ReadHomeTimeline: Posts after filtering: "
              << filtered_posts.size() << std::endl;

    // Handle pagination manually on the filtered list
    std::vector<Post> paged_posts;
    for (size_t i = start_idx;
         i < filtered_posts.size() && i < (size_t)stop_idx; ++i) {
      paged_posts.push_back(filtered_posts[i]);
    }
    return paged_posts;
  }

  // If not filtering, we still respect the generic "GetPostsBetweenIdx"
  // usually, but since we switched to GetAllPosts above for consistency in this
  // snippet:
  std::vector<Post> paged_posts;
  for (size_t i = start_idx; i < posts.size() && i < (size_t)stop_idx; ++i) {
    paged_posts.push_back(posts[i]);
  }
  return paged_posts;
};

void HomeTimelineHandler::WriteHomeTimeline(
    int64_t post_id, int64_t user_id, int64_t timestamp,
    const std::vector<int64_t> &user_mentions_id) {
  std::cout << "WriteHomeTimeline appelé" << std::endl;
};

EMSCRIPTEN_BINDINGS(home_timeline_module) {
  class_<HomeTimelineHandler>("HomeTimelineHandler")
      .constructor<PostStorageHandler &, SocialGraphHandler &>()
      .function("ReadHomeTimeline", &HomeTimelineHandler::ReadHomeTimeline)
      .function("WriteHomeTimeline", &HomeTimelineHandler::WriteHomeTimeline);
}
