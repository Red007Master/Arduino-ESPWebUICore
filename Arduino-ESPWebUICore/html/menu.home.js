var button = document.getElementById("pressbutton");
var infop = document.getElementById("infop");

button.innerText = loadContent("http://192.168.0.151/relay_status_text");

function loadContent(theURL) {
  var result = "";
  if (window.XMLHttpRequest) {
    xmlhttp = new XMLHttpRequest();
  } else {
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }
  xmlhttp.onreadystatechange = function () {
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      result = xmlhttp.responseText;
    }
  };
  xmlhttp.open("GET", theURL, false);
  xmlhttp.send();

  return result;
}
function button_pressed() {
  var request = new XMLHttpRequest();
  request.open("GET", "/relay_switch", false);
  request.send();

  button.innerText = loadContent("http://192.168.0.151/relay_status_text");
}
button.addEventListener("click", button_pressed);

var infopdata = getInfopData();
infop.innerHTML = infopdata;

function getInfopData() {
  return loadContent("http://192.168.0.151/relay_status_full");
}
