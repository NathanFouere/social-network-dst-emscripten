import di from '../di.js'

let postTemplate = null;

export default function showTimeline(type) {
  const loggedUser = di.sessionStorageUserService.getLoggedUser();

  if (type == "main") {
    const cardBlock = document.getElementById("card-block");
    if (!cardBlock) return;

    // Use cached template
    if (!postTemplate) return;

    const onlyFriendsToggle = document.getElementById('only-friends-toggle');
    const onlyFriends = onlyFriendsToggle ? onlyFriendsToggle.checked : false;

    // Fetch posts (synchronous for now based on current impl)
    const posts = di.homeTimelineHandler.ReadHomeTimeline(loggedUser.userid, 0, 10, onlyFriends);

    // Clear current posts
    cardBlock.innerHTML = "";

    for (var i = 0; i < posts.size(); i++) {
      const p = posts.get(i);
      const date = new Date(Number(p.timestamp) * 1000);

      const clone = postTemplate.cloneNode(true);
      clone.style.display = "block";

      // Fill data
      clone.querySelector(".post-text").innerText = p.text;
      clone.querySelector(".post-time").innerText = date.toString();

      const creatorEl = clone.querySelector(".post-creator");
      if (creatorEl) creatorEl.innerText = p.creator.username;

      // Hook buttons
      const deleteBtn = clone.querySelector(".delete-post-btn");
      if (deleteBtn) {
        deleteBtn.addEventListener('click', () => {
          $('#deletePostModal').data('post-id', p.post_id).modal('show');
        });
      }

      const editBtn = clone.querySelector(".edit-post-btn");
      if (editBtn) {
        editBtn.addEventListener('click', () => {
          $('#editPostModal').data('post-id', p.post_id);
          const editPostTextarea = document.getElementById('editPostTextarea');
          editPostTextarea.value = p.text;
          $('#editPostModal').modal('show');
        });
      }

      cardBlock.appendChild(clone);
    }
  }
}

// Global exposure
window.showTimeline = showTimeline;

function initTimeline() {
  const allCards = document.getElementsByClassName("post-card");
  if (allCards.length > 0) {
    console.log("timeline.js: Template captured.");
    postTemplate = allCards[0].cloneNode(true);
    allCards[0].remove();
  } else {
    console.error("timeline.js: No post-card template found!");
  }

  showTimeline("main");

  const toggle = document.getElementById('only-friends-toggle');
  if (toggle) {
    toggle.addEventListener('change', () => {
      showTimeline("main");
    });
  }

  $('#confirmDeletePostBtn').on('click', () => {
    const postId = $('#deletePostModal').data('post-id');
    if (postId) {
      di.postStorageHandler.DeletePost(postId);
      $('#deletePostModal').modal('hide');
      showTimeline("main");
      //setTimeout(() => { showTimeline("main"); }, 500);
    }
  });

  $('#confirmEditPostBtn').on('click', () => {
    const postId = $('#editPostModal').data('post-id');
    if (postId) {
      const editPostTextarea = document.getElementById('editPostTextarea');
      di.postStorageHandler.EditPostText(postId, editPostTextarea.value);
      $('#editPostModal').modal('hide');
      showTimeline("main");
      //setTimeout(() => { showTimeline("main"); }, 500);
    }
  });
}

if (document.readyState === "loading") {
  document.addEventListener("DOMContentLoaded", initTimeline);
} else {
  initTimeline();
}
