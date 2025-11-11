import di from '../di.js'

function clickEventHandler() {
    if (document.getElementById('media').value != "") {
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
        uploadPost()
    }
}

function uploadPost(media_json) {
    if (document.getElementById('post-content').value !== "") {
        var body = document.getElementById('post-content').value

        di.composePostHandler.ComposePost(
          "username mock",
          1,
          body,
          di.module.PostType.POST
        );

      console.log(di.inMemoryPersistenceService.GetAllPosts().get(0).post_id);
      console.log(di.inMemoryPersistenceService.GetAllPosts().get(0).text);
      di.inMemoryPersistenceService.SaveAllInLocalStorage()
      console.log(JSON.parse(localStorage.getItem("posts")))


        // window.location.reload();
    }
}
document.getElementById('create-post')
  .addEventListener('click', clickEventHandler);

var hide = document.getElementById('hide-post');
var show = document.getElementById('show-post');

$("#compose").hide(); // cache par défaut la création de post

hide.addEventListener("click", function () {
    $("#compose").hide();
})

show.addEventListener("click", function () {
    $("#compose").toggle();
})
