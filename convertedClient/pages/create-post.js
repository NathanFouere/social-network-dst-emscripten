import di from "../di.js";
import showTimeline from "./timeline.js";

function clickEventHandler() {
  if (document.getElementById("media").value != "") {
    // console.log(document);
    // var formData = new FormData(document.getElementById('media-form'));
    // const Http = new XMLHttpRequest();
    // const url = 'http://' + window.location.hostname + ':8081/upload-media';
    // Http.onreadystatechange = function () {
    //     if (this.readyState == 4 && this.status == 200) {
    //         var resp = JSON.parse(Http.responseText);
    //         uploadPost(resp);
    //     }
    // };
    // Http.open("POST", url, true);
    // Http.send(formData);
  } else {
    uploadPost();
  }
}

function uploadPost(media_json) {
  if (document.getElementById("post-content").value !== "") {
    var body = document.getElementById("post-content").value;
    const loggedUser = di.sessionStorageUserService.getLoggedUser();
    di.composePostHandler.ComposePost(
      loggedUser.username,
      loggedUser.userid,
      body,
      di.module.PostType.POST,
    );
    showTimeline("main");
    // window.location.reload();
  }
}

document
  .getElementById("create-post")
  .addEventListener("click", clickEventHandler);

var hide = document.getElementById("hide-post");
var show = document.getElementById("show-post");

$("#compose").hide(); // cache par défaut la création de post

hide.addEventListener("click", function () {
  $("#compose").hide();
});

show.addEventListener("click", function () {
  $("#compose").toggle();
});
