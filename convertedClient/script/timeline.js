import di from '../di.js'

export default function showTimeline(type) {
  const loggedUser = di.sessionStorageUserService.getLoggedUser();

  if (type == "main") {
    const onlyFriends = document.getElementById('only-friends-toggle').checked;
    const posts = di.homeTimelineHandler.ReadHomeTimeline(loggedUser.userid, 0, 10, onlyFriends);

    const cardBlock = document.getElementById("card-block");
    // Find the template card. 
    // Careful: if we ran this before, there might be multiple cards. 
    // We assume the first one is the template or we kept a reference.
    // For simplicity in this existing codebase, let's assume the first .post-card is our template.
    const allCards = document.getElementsByClassName("post-card");
    if (allCards.length === 0) return; // No template found

    const template = allCards[0].cloneNode(true);

    // Clear the container but we must ensure we don't lose the ability to clone if we clear everything.
    // Actually, simpler approach: Remove all *except* the first one, then hide the first one, then append new ones?
    // OR: clone the template, clear innerHTML, then append new ones. 
    cardBlock.innerHTML = "";

    for (var i = 0; i < posts.size(); i++) {
      const p = posts.get(i);
      const date = new Date(Number(p.timestamp) * 1000);

      const clone = template.cloneNode(true);
      clone.style.display = "block"; // Ensure it's visible

      // Fill data
      clone.querySelector(".post-text").innerText = p.text;
      clone.querySelector(".post-time").innerText = date.toString();
      clone.querySelector(".post-creator").innerText = p.creator.username;

      // Hook buttons
      const deleteBtn = clone.querySelector(".delete-post-btn");
      if (deleteBtn) {
        deleteBtn.onclick = () => {
          di.postStorageHandler.DeletePost(p.post_id);
          window.location.reload();
        };
      }

      const editBtn = clone.querySelector(".edit-post-btn");
      if (editBtn) {
        editBtn.onclick = () => {
          di.postStorageHandler.EditPostText(p.post_id, "edited post");
          window.location.reload();
        };
      }

      cardBlock.appendChild(clone);
    }
  }
}

showTimeline("main");

// Checkbox Listener
const toggle = document.getElementById('only-friends-toggle');
if (toggle) {
  toggle.addEventListener('change', () => {
    // Refresh the page or just clear and redraw.
    // Since the logic currently appends clones, a full reload or clear is needed.
    // But the current loop logic relies on existing elements in DOM. 
    // Ideally we should reload to keep it simple with pure HTML/JS structure provided.
    window.location.reload();
  });
}
