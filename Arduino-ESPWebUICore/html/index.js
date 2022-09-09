console.log("open");

var iframe = document.querySelector(".mainiframe");
var nav = document.querySelector(".mainnav");
var header = document.querySelector(".mainheader");

function displayWindowSize() {
  var w = document.documentElement.clientWidth;
  var h = document.documentElement.clientHeight;

  iframe.style.width = w - nav.offsetWidth + "px";
  iframe.style.height = h - header.offsetHeight + "px";
  nav.style.height = h - header.offsetHeight + "px";
}
window.addEventListener("resize", displayWindowSize);

displayWindowSize();

var t = setInterval(displayWindowSize, 1000);

var navico1 = document.getElementById("navico1");
var navico2 = document.getElementById("navico2");
var navico3 = document.getElementById("navico3");

function navicopress(adress) {
  iframe.src = adress;
  console.log("press");
  console.log(adress);
}

navico1.onclick = () => {
  navicopress("menu.home.html");
};

navico2.onclick = () => {
  navicopress("http://google.com/");
};

navico3.onclick = () => {
  navicopress("https://github.com/");
};
