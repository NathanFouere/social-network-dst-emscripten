import di from '../../di.js'

function followHandler(event) {
  event.preventDefault();

  const form = event.currentTarget;
  const formData = new FormData(form);

  const follweeeName = formData.get("followee_name");
  const username = formData.get("user_name");

  di.socialGraphHandler.FollowWithUsername(username, follweeeName);
}


document.querySelectorAll('.follow-form').forEach(f => {
  f.addEventListener('submit', followHandler);
});
