# ESP32 INMP441 WiFi Audio Streaming

A simple project that streams live audio from an **INMP441 I2S microphone** connected to an **ESP32** to a **web browser** over WiFi.

The ESP32 captures audio using the **I2S peripheral**, converts it to PCM data, and sends it over **WebSockets**. The browser receives the audio stream and plays it in real time.

This project was created to experiment with **ESP32 audio capture, I2S microphones, and browser-based playback** without requiring any additional software on the computer.

---

# Features

* Live audio streaming from ESP32
* Uses **INMP441 digital I2S microphone**
* Audio playback directly in a **web browser**
* Uses **WebSockets** for real-time transmission
* Multiple experimental versions included
* No PC software required (just a browser)

DEMO VIDEO ON YOUTUBE:

https://youtu.be/v_W0UrSFPy4

---

# Repository Structure

```
1/
 └── version1.ino

2/
 ├── version2.ino
 └── index.html

3/
 ├── version3.ino
 └── index.html
```

### Version Overview

**Version 1**

* Basic I2S microphone test
* Prints microphone values to the Serial Monitor
* Used to verify wiring and microphone functionality

**Version 2**

* First working WebSocket audio streaming attempt
* Browser receives PCM data and plays it
* Audio works but may contain heavy noise ("volcano noise")

**Version 3**

* Improved buffering and data handling
* Reduced noise and more stable audio playback
* Recommended version for use

---

# Hardware Requirements

* ESP32 development board
* INMP441 I2S microphone
* Jumper wires
* WiFi network
* Computer with a browser

---

# Wiring

Connect the **INMP441 microphone** to the ESP32 as follows:

| INMP441 Pin | ESP32 Pin        | Description   |
| ----------- | ---------------- | ------------- |
| VCC / VDD   | 3.3V             | Power supply  |
| GND         | GND              | Ground        |
| SCK / BCLK  | GPIO 26          | Bit clock     |
| WS / LRCL   | GPIO 25          | Word select   |
| SD          | GPIO 22          | Data output   |
| L/R         | Floating or 3.3V | Right channel |

**Important:**
Many INMP441 modules default to **Right Channel** when L/R is floating.

If you connect **L/R to GND**, make sure the code listens to the **left channel**.

---

# Libraries Required

Install these libraries in Arduino IDE:

* **WebSocketsServer** by Markus Sattler
* ESP32 Arduino Core (if not already installed)

---

# How to Use

## Step 1 – Upload the ESP32 Code

1. Open the folder for the version you want to test.
2. Open the `.ino` file in Arduino IDE.
3. Update the WiFi credentials in the code:

```
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASS "YOUR_PASSWORD"
```

4. Select your ESP32 board.
5. Upload the code.

---

## Step 2 – Get the ESP32 IP Address

Open the **Serial Monitor**.

You should see something like:

```
192.168.x.x
```

Copy this IP address.

---

## Step 3 – Configure the Web Page

Open `index.html`.

Find the line:

```
const ESP_IP = "192.168.0.18";
```

Replace it with your ESP32 IP address.

Save the file.

---

## Step 4 – Start Audio Streaming

1. Open `index.html` in your browser.
2. Click the **Start** button.
3. The browser will connect to the ESP32.
4. Audio from the microphone should start playing.

---

# Common Issues and Fixes

## No Audio

Possible causes:

* Incorrect wiring
* Wrong GPIO pins in the code
* Wrong audio channel

Check the wiring table and verify the GPIO pins.

---

## Audio is Very Noisy ("Volcano Noise")

Cause:

* Raw I2S data not properly buffered or converted.

Fix:

Use **Version 3**, which has improved buffering.

---

## Microphone Works Only When L/R is Floating

Cause:

Some INMP441 modules default to the **Right Channel**.

Fix:

Either:

* Leave L/R floating and listen to **RIGHT channel** in code
  or
* Connect L/R to GND and use **LEFT channel**

* BASICALLY, You got to try trial and error cuz all the modules might work differently

---

## WebSocket Error: `ws://:81 invalid URL`

Cause:

The browser cannot determine the ESP32 IP automatically.

Fix:

Manually set the IP address in `index.html`.

---

## Browser Connects but No Sound

Possible causes:

* Browser blocked audio autoplay
* Audio context not initialized

Fix:

Click the **Start** button to activate the AudioContext.

---

# Future Improvements

Possible upgrades for this project:

* Noise filtering
* Automatic gain control
* Web interface hosted directly on ESP32
* Audio recording to SD card
* WiFi walkie-talkie mode
* Multi-client audio streaming

I hope I recieve help from all of you guys on bringing these improvements to life!

---

# License

This project is provided for learning and experimentation purposes.

---

# Author

Parthib Banerjee
Robotics enthusiast and student developer.

---

If any more help is required, feel free to contact me on my e-mail:
banerjeeparthib63@gmail.com
