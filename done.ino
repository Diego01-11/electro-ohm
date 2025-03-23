#include <WiFi.h>

// Name and password of the WiFi network created by the ESP32
const char* ssid = "OHM_METER_ESP32";      
const char* password = "12345678";       

WiFiServer server(80);

// Analog pin connected to the voltage divider
const int analogPin = 34;
const int ledPin = 2;  // Built-in LED pin

int x = 0;
float Vout = 0;
float R_known = 10000.0; // Known resistor (10K)
float R_unknown = 0;
float buffer = 0;

void setup() {
  Serial.begin(115200);

  // Set ESP32 to Access Point mode
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point ready. Connect to this network: ");
  Serial.println(IP);

  server.begin();

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn off LED at start
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("A client just connected");

    while (client.connected()) {
      if (client.available()) {
        client.read();  // Read client data (even if not used)

        // Read analog value
        x = analogRead(analogPin);

        // Turn on LED if no input is detected
        if (x == 0) {
          digitalWrite(ledPin, HIGH); // Turn LED on
        } else {
          digitalWrite(ledPin, LOW); // Turn LED off
        }

        // Build the HTML with style
        String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        html += "<title>ESP32 Ohm Meter</title>";
        html += "<style>";
        html += "body { font-family: Arial, sans-serif; background: #1e1e1e; color: #f2f2f2; text-align: center; padding: 40px; }";
        html += "h1 { font-size: 3em; margin-bottom: 20px; }";
        html += "h2 { color: #00ff99; font-size: 2em; margin-bottom: 10px; }";
        html += "p { font-size: 1.2em; color: #cccccc; }";
        html += ".card { background: #333; padding: 30px; border-radius: 15px; box-shadow: 0 0 15px rgba(0, 255, 153, 0.2); display: inline-block; }";
        html += "</style>";
        html += "</head><body>";
        html += "<div class='card'>";
        html += "<h2>------ OHM METER ------</h2>";

        // Display "no input" or calculate resistance
        if (x < 10) {
          html += "<h1>There's no input</h1>";
        } else {
          // Calculate Vout based on analog reading
          Vout = (x * 3.3) / 4095.0;  // Adjusted for 3.3V reference

          // Calculate unknown resistance using voltage divider formula
          if (Vout > 0) {
            R_unknown = (Vout / (3.3 - Vout)) * R_known;
            html += "<h1>" + String(R_unknown, 2) + " Ω</h1>";
          } else {
            html += "<h1>Invalid reading</h1>";
          }

          html += "<p>Analog Read: " + String(x) + "</p>";
        }

        html += "</div>";
        html += "<meta http-equiv='refresh' content='3'>"; // Refresh every 3 seconds
        html += "</body></html>";

        // Send HTTP response with the HTML
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type: text/html");
        client.println("Connection: close");
        client.println();
        client.println(html);
        break;
      }
    }

    delay(10);
    client.stop();
    Serial.println("Client disconnected");
  }
}

