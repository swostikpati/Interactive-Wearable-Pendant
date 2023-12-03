const express = require("express");
const app = express();
const port = 3000;

// GPIO setup for Raspberry Pi
const GPIO = require("onoff").Gpio;
const led = new GPIO(17, "out"); // Use the appropriate GPIO pin

let ledState = false;

app.get("/toggle", (req, res) => {
  ledState = !ledState;
  led.writeSync(ledState ? 1 : 0); // Turn LED on or off
  console.log(`The light is turned ${ledState ? "on" : "off"}`);
  res.send(`LED is now ${ledState ? "ON" : "OFF"}`);
});

app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});
