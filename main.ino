#include <WiFi.h>
#include <esp_rainmaker.h>
#include <IRremote.h>

// Define Pins
#define RELAY_1 25
#define RELAY_2 26
#define IR_PIN 27

// WiFi Credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Setup IR Receiver
IRrecv irrecv(IR_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  
  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // RainMaker Setup
  esp_rainmaker_init("ESP Home Automation");
  esp_rainmaker_node_t *node = esp_rainmaker_node_init("ESP Home Node");
  esp_rainmaker_param_t *relay1 = esp_rainmaker_param_create("Relay1", PARAM_TYPE_TOGGLE, &RELAY_1);
  esp_rainmaker_node_add_param(node, relay1);

  // Initialize Relays
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);

  // Initialize IR Receiver
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(10);
}
