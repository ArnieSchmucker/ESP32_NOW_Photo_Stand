/*
  ESP-NOW Demo - Transmit
  esp-now-demo-xmit.ino
  Sends data to Responder
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#define switchAPin 19
#define switchBPin 16
#define switchCPin 17
#define switchDPin 21
#define switchEPin 13
#define switchFPin 12
#define switchGPin 27
#define switchHPin 33
#define potPin A2

// Variables for test data
//int int_value;
//float float_value;
//bool bool_value = true;
bool switchAValue = true;
bool switchBValue = true;
bool switchCValue = true;
bool switchDValue = true;
bool switchEValue = true;
bool switchFValue = true;
bool switchGValue = true;
bool switchHValue = true;
int potValue = 0;

// MAC Address of responder - edit as required
//uint8_t broadcastAddress[] = {0x94, 0x3C, 0xC6, 0x97, 0x67, 0x48};
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Define a data structure
typedef struct struct_message {
  bool a;
  bool b;
  bool c;
  bool d;
  bool e;
  bool f;
  bool g;
  bool h;
  int i;
} struct_message;

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
  pinMode(switchAPin, INPUT_PULLUP);
  pinMode(switchBPin, INPUT_PULLUP);
  pinMode(switchCPin, INPUT_PULLUP);
  pinMode(switchDPin, INPUT_PULLUP);
  pinMode(switchEPin, INPUT_PULLUP);
  pinMode(switchFPin, INPUT_PULLUP);
  pinMode(switchGPin, INPUT_PULLUP);
  pinMode(switchHPin, INPUT_PULLUP);  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

  // Create test data
  switchAValue = digitalRead(switchAPin);
  switchBValue = digitalRead(switchBPin);
  switchCValue = digitalRead(switchCPin);
  switchDValue = digitalRead(switchDPin);
  switchEValue = digitalRead(switchEPin);
  switchFValue = digitalRead(switchFPin);
  switchGValue = digitalRead(switchGPin);
  switchHValue = digitalRead(switchHPin);
  potValue = analogRead(potPin);

  Serial.print("Data:");
  Serial.write(9);
  Serial.print(switchAValue);
  Serial.write(9);
  Serial.print(switchBValue);
  Serial.write(9);
  Serial.print(switchCValue);
  Serial.write(9);
  Serial.print(switchDValue);
  Serial.write(9);
  Serial.print(switchEValue);
  Serial.write(9);
  Serial.print(switchFValue);
  Serial.write(9);
  Serial.print(switchGValue);
  Serial.write(9);
  Serial.print(switchHValue);
  Serial.write(9);
  Serial.println(potValue);


  myData.a = switchAValue;
  myData.b = switchBValue;
  myData.c = switchCValue;
  myData.d = switchDValue;
  myData.e = switchEValue;
  myData.f = switchFValue;
  myData.g = switchGValue;
  myData.h = switchHValue;
  myData.i = potValue;  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(100);
}
