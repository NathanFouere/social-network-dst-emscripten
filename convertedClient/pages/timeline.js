import di from '../di.js'

export default function showTimeline(type) {
  const loggedUser = di.sessionStorageUserService.getLoggedUser();

    if(type == "main") {
    const posts = di.homeTimelineHandler.ReadHomeTimeline(loggedUser.userid, 1, 10);
    console.log(posts.get(0))

    const post_cards = document.getElementsByClassName("post-card");
    const post_texts = document.getElementsByClassName("post-text");
    const post_times = document.getElementsByClassName("post-time");
    const post_creators = document.getElementsByClassName("post-creator");
    const post_footer = document.getElementsByClassName("post-footer");
    for (var i = 0; i < posts.size(); i++) {
      if (i == post_cards.length - 1) {
          var itm = post_cards[i];
          var cln = itm.cloneNode(true); //clone the post_card[i]
          document.getElementById("card-block").appendChild(cln);
      }
      post_cards[i].style.display = "block";
      post_texts[i].innerHTML = posts.get(i).text;
      post_times[i].innerText = new Date(Number(posts.get(i).timestamp) * 1000);
      post_creators[i].innerText = posts.get(i).creator.username;
    }
  }
}

showTimeline("main");
