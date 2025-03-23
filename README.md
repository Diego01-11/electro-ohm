# ESP32 Ohm Meter (Electrical Measurement Practice)

This project is a simple **Ohm Meter** built with an **ESP32** microcontroller. It allows you to measure an unknown resistor using a voltage divider circuit and display the result via a WiFi-accessible web page.

## 🔧 What It Does

- Creates a **WiFi Access Point** from the ESP32.
- Reads the analog voltage from a voltage divider circuit.
- Calculates the unknown resistance in ohms using the voltage divider formula.
- Displays the resistance value and raw analog input through a responsive HTML interface.
- Blinks the onboard LED when no input is detected.

## 📷 Example

When accessed from a mobile device or PC connected to the ESP32’s WiFi, you will see a clean interface showing the resistance and live updates every 3 seconds.
![Imagen de WhatsApp 2025-03-23 a las 00 17 36_28de8a98](https://github.com/user-attachments/assets/f76e709e-e213-4289-b4aa-0fc0bf1c06ca)


## ⚙️ Hardware Requirements

- 1x ESP32 Development Board  
- 1x Known resistor (e.g., 10kΩ)
- 1x Unknown resistor to measure
- Jumper wires
- Breadboard
- USB cable

## 🔌 Circuit Diagram

The unknown resistor and known resistor should be connected in a voltage divider configuration. The midpoint of the divider goes to **GPIO 34** (analog input). Example:




## 📡 How to Use

1. Upload the code to your ESP32.
2. Connect your phone or computer to the WiFi named **OHM_METER_ESP32** (password: `12345678`).
3. Open a browser and go to the IP shown in the Serial Monitor (usually `192.168.4.1`).
4. Observe the measured resistance on the web interface.

## 📁 Code Structure

- Sets up WiFi in Access Point mode.
- Continuously reads analog input on pin **34**.
- Calculates output voltage and unknown resistance.
- Generates a simple web page using raw HTML and CSS.
- Updates every 3 seconds with new readings.

## 🧪 Educational Purpose

This project was created by **Diego Polo** as a practical exercise for **electrical measurements**. It serves to demonstrate how voltage dividers and analog-to-digital conversion work, and how to build simple interfaces to visualize real-time sensor data.

## 📄 License

This project is released for educational use. Feel free to modify and improve it!

---

