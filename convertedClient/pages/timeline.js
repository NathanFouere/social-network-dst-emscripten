import di from '../di.js'

export default function showTimeline(type) {
  const loggedUser = di.sessionStorageUserService.getLoggedUser();

    if(type == "main") {
    const posts = di.homeTimelineHandler.ReadHomeTimeline(loggedUser.userid, 0, 10);

    const post_cards = document.getElementsByClassName("post-card");
    const post_texts = document.getElementsByClassName("post-text");
    const post_times = document.getElementsByClassName("post-time");
    const post_creators = document.getElementsByClassName("post-creator");
    const post_deletes_button = document.getElementsByClassName("delete-post-btn");
    const post_edits_button = document.getElementsByClassName("edit-post-btn");

    for (var i = 0; i < posts.size(); i++) {

      if (i == post_cards.length - 1) {
          var itm = post_cards[i];
          var cln = itm.cloneNode(true); //clone the post_card[i]
          document.getElementById("card-block").appendChild(cln);
      }

      const p = posts.get(i);
      const date = new Date(Number(p.timestamp) * 1000);

      post_cards[i].style.display = "block";
      post_texts[i].innerText = p.text;
      post_times[i].innerText = date.toString();
      post_creators[i].innerText = p.creator.username;

      post_deletes_button[i].onclick = () => {
        di.postStorageHandler.DeletePost(p.post_id);
        window.location.reload();
      };

      post_edits_button[i].onclick = () => {
        di.postStorageHandler.EditPostText(p.post_id, "edited post");
        window.location.reload();
      };
    }
  }
}

showTimeline("main");
