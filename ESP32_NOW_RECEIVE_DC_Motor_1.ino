/*
  ESP-NOW Demo - Receive
  esp-now-demo-rcv.ino
  Reads data from Initiator
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#define en1Pin 16
#define dir1Pin 21
#define dir2Pin 17
#define en2Pin 15
#define dir3Pin 32
#define dir4Pin 14
#define leftLimitPin 12
#define rightLimitPin 27

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

int pwmValue;

bool leftLimitValue = 1;
bool rightLimitValue = 1;

// Create a structured object
struct_message myData;


// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("LeftLimit: ");
  Serial.print(leftLimitValue);
  Serial.write(9);
  Serial.print("RightLimit: ");
  Serial.println(rightLimitValue);
  Serial.print("Switch A: ");
  Serial.println(myData.a);
  Serial.print("Switch B: ");
  Serial.println(myData.b);
  Serial.print("Switch C: ");
  Serial.println(myData.c);
  Serial.print("Switch D: ");
  Serial.println(myData.d);
  Serial.print("Switch E: ");
  Serial.println(myData.e);
  Serial.print("Switch F: ");
  Serial.println(myData.f);
  Serial.print("Switch G: ");
  Serial.println(myData.g);
  Serial.print("Switch H: ");
  Serial.println(myData.h);
  Serial.print("Pot: ");
  Serial.println(myData.i);
  pwmValue = map(myData.i, 0, 4096, 0, 255);
  if(myData.a == 0 && leftLimitValue == 1) {
    digitalWrite(dir1Pin, HIGH);
    digitalWrite(dir2Pin, LOW);
    ledcWrite(0, pwmValue);
  } else if(myData.b == 0 && rightLimitValue == 1) {
      digitalWrite(dir1Pin, LOW);
      digitalWrite(dir2Pin, HIGH);
      ledcWr  Serial.print("LeftLimit: ");
  Serial.println(leftLimitValue);ite(0, pwmValue);
  } else if(myData.c == 0) {
      digitalWrite(dir3Pin, HIGH);
      digitalWrite(dir4Pin, LOW);
      ledcWrite(1, pwmValue);    
  } else if(myData.d == 0) {
      digitalWrite(dir3Pin, LOW);
      digitalWrite(dir4Pin, HIGH);
      ledcWrite(1, pwmValue);    
  }
  else {
    ledcWrite(0, 0);
    digitalWrite(dir3Pin, HIGH);
    digitalWrite(dir4Pin, HIGH);
    ledcWrite(1, 0);
  }

}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  pinMode(en1Pin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
  pinMode(en2Pin, OUTPUT);
  pinMode(dir3Pin, OUTPUT);
  pinMode(dir4Pin, OUTPUT);
  pinMode(leftLimitPin, INPUT_PULLUP);
  pinMode(rightLimitPin, INPUT_PULLUP);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(en1Pin, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(en2Pin, 1);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
 leftLimitValue = digitalRead(leftLimitPin);
 rightLimitValue = digitalRead(rightLimitPin);

}
