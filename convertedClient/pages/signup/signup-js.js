import di from '../../di.js'


function test(event) {
  event.preventDefault();

  const firstnameInput = document.getElementById("first-name-input").value;
  const lastnameInput = document.getElementById("last-name-input").value;
  const usernameInput = document.getElementById("user-name-input").value;
  const passwordInput = document.getElementById("password-input").value;
  di.userHandler.RegisterUser(firstnameInput, lastnameInput, usernameInput, passwordInput);
}

const loginForm = document.getElementById("userform");

loginForm.addEventListener("submit", test)
