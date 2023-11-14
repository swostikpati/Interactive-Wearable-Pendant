document.getElementById("toggleButton").addEventListener("click", () => {
  fetch("http://[RASPBERRY_PI_IP_ADDRESS]:3000/toggle")
    .then((response) => response.text())
    .then((data) => console.log(data))
    .catch((error) => console.error("Error:", error));
});
