import di from './di.js'


function test(event) {
  event.preventDefault();

  console.log(di.uniqueIdHandler.ComposeUniqueId());
}

const loginForm = document.getElementById("userform");

loginForm.addEventListener("submit", test)
