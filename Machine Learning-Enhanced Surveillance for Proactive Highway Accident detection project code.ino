#include <Wire.h>
#include <PubSubClient.h>
#include <WiFi.h>

#define WIFI_AP "JARVIS 011"
#define WIFI_PASSWORD "AKAVI7428"
#define TOKEN "V8GU4epgoxuMJfXANZ0O"

const char* thingsboardServer = "demo.thingsboard.io";
const int thingsboardPort = 1883;

#define GSM_RX_PIN 2  // brown
#define GSM_TX_PIN 15  // blue

HardwareSerial gsmSerial(1); // Use Serial1 on ESP32

float latitude = 12.901039; // Replace with actual latitude
float longitude = 79.934824; // Replace with actual longitude

float latitude1 = 12.8439; // Initial latitude1
float longitude1 =79.9481; // Initial longitude1
int percentage;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

bool isAlertTriggered; // Set this based on your alert condition

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600, SERIAL_8N1, GSM_RX_PIN, GSM_TX_PIN);

  initGSM();

  connectWiFi();

  mqtt.setServer(thingsboardServer, thingsboardPort);

  Serial.println("Send latitude and longitude to ThingsBoard when 'c' command received");
}

void loop() {
  if (!mqtt.connected()) {
    reconnect();
  }
  mqtt.loop();

  checkCommands();

  sendToThingsBoard();

  delay(1000); // Send data every 60 seconds (adjust as needed)
}

void initGSM() {
  Serial.println("Initializing GSM...");
  delay(1000);

  gsmSerial.println("AT"); // Send AT command to check if the module is responding
  delay(1000);

  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }

  gsmSerial.println("AT+CPIN?"); // Check if SIM card is ready
  delay(500);
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }

  Serial.println("GSM initialized");
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
}

void reconnect() {
  while (!mqtt.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (mqtt.connect("ESP32Client", TOKEN, "")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void checkCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'c':
        makeCall();
        break;
      case 'q':
        checkSignalStrength();
        break;
    }
  }
}
void checkSignalStrength() {
  Serial.println("Checking Signal Strength - Not applicable for this scenario");
}

void makeCall() {
  Serial.println("Making a call");

  // Replace "yourPhoneNumber" with the actual phone number you want to call
  const char phoneNumber[] = "8838665867";

  Serial.println("Calling...");

  gsmSerial.print("ATD"); // ATD command to dial a number
  gsmSerial.print(phoneNumber);
  gsmSerial.println(";");

  // Wait for the call to be connected
  while (!gsmSerial.available()) {
    delay(1000); // Wait for 1 second, adjust as needed
  }

  // Set isAlertTriggered to true when the call is connected
  isAlertTriggered = true;
  Serial.println("Call connected");
  delay(4000);
  Serial.print("isAlertTriggered: ");
  Serial.println(isAlertTriggered);
  
  unsigned long callStartTime = millis(); // Record the start time of the call

  // Wait for the call to complete (adjust the duration as needed)
  while (millis() - callStartTime < 40000) { // 40 seconds
    Serial.print("Waiting... ");
    Serial.println(40 - ((millis() - callStartTime) / 1000));

    // Send payload every second
    if ((millis() - callStartTime) > 36000) {
      percentage = 100;
    } else if ((millis() - callStartTime) > 34000) {
      percentage = 90;
    } else if ((millis() - callStartTime) > 31000) {
      percentage = 85;
    } else if ((millis() - callStartTime) > 28000) {
      percentage = 75;
    } else if ((millis() - callStartTime) > 20000) {
      percentage = 50;
    } else if ((millis() - callStartTime) > 13000) {
      percentage = 30;
    } else {
      percentage = 10;
    }

    Serial.println(percentage);
    sendToThingsBoard();
    delay(1000); 
  }

  // Set isAlertTriggered back to false when the call is completed
  isAlertTriggered = false;
  
  // Change latitude1 and longitude1 after the call is completed
  latitude1 = 12.901039;
  longitude1 = 79.934824;

  Serial.println("Call completed");
  Serial.print("isAlertTriggered: ");
  Serial.println(isAlertTriggered);
}


void sendToThingsBoard() {
  String topic = "v1/devices/me/telemetry";
  String payload;

  if (isAlertTriggered) {
    payload = "{\"latitude\":" + String(latitude) + ",\"longitude\":" + String(longitude) + ",\"Alert\":\"100\",\"Status\":\"Active\",\"Latitude1\":" + String(latitude1) + ",\"Longitude1\":" + String(longitude1) + ",\"percentage\":" + String(percentage) +"}";
  } else {
    payload = "{\"latitude\":" + String(latitude) + ",\"longitude\":" + String(longitude) + ",\"Alert\":\"0\",\"Status\":\"InActive\",\"Latitude1\":" + String(latitude1) + ",\"Longitude1\":" + String(longitude1) + "}";
  }

  Serial.print("Sending payload to ThingsBoard: ");
  Serial.println(payload);

  if (mqtt.publish(topic.c_str(), payload.c_str())) {
    Serial.println("Payload sent to ThingsBoard");
  } else {
    Serial.println("Failed to send payload to ThingsBoard");
  }
}