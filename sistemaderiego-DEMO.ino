#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// ThingSpeak credentials
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char* myWriteAPIKey = "YOUR_API_KEY";

void setup() {
  // Initialize serial, WiFi, sensor input, and control outputs
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(S1_AO, INPUT);
  pinMode(U2_IN1, OUTPUT);
  pinMode(U2_IN2, OUTPUT);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }

  ThingSpeak.begin(client);
}

void loop() {
  // Read moisture
  int moisture = analogRead(S1_AO);

  // Check soil condition
  if (moisture < DRY_SOIL_THRESHOLD) {
    // Activate water pump
    digitalWrite(U2_IN1, HIGH);
    digitalWrite(U2_IN2, LOW);
    // Add delay for water pump operation as needed
  } else {
    // Deactivate water pump or maintain previous state
  }

  // Send data to ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 1, moisture, myWriteAPIKey);

  // Delay to limit data sending rate
  delay(20000); // Adjust based on your needs
}
