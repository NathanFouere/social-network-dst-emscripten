import di from "../di.js";

let followUsername = () => {
  let username = localStorage.getItem("username");
  document.querySelectorAll(".follow-username").forEach(function (element) {
    element.setAttribute("value", username);
  });
};
function showUsername() {
  if (
    localStorage.getItem("username") != undefined &&
    localStorage.getItem("username") != null
  ) {
    var username = localStorage.getItem("username");
  }
  document.getElementById("username").textContent = username;
  console.log(username);
}

followUsername();

function followHandler(event) {
  event.preventDefault();

  const form = event.currentTarget;
  const submit = event.submitter;
  const formData = new FormData(form, submit);

  const follweeeName = formData.get("followee_name");
  const username = formData.get("user_name");
  const followType = formData.get("follow_type");

  if (followType === "Unfollow") {
    di.socialGraphHandler.UnfollowWithUsername(username, follweeeName);
    return;
  }

  di.socialGraphHandler.FollowWithUsername(username, follweeeName);
}

document.querySelectorAll(".follow-form").forEach((f) => {
  f.addEventListener("submit", followHandler);
});
