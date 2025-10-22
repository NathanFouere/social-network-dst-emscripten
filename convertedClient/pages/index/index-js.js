import di from '../../di.js'


function loginHandler(event) {
  event.preventDefault();

  const usernameInput = document.getElementById("username-input").value;
  const passwordInput = document.getElementById("password-input").value;
  di.userHandler.Login(usernameInput, passwordInput)
}

const loginForm = document.getElementById("userform");

loginForm.addEventListener("submit", loginHandler)
