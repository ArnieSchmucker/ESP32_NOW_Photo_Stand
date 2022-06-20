*
  ESP-NOW Demo - Receive
  esp-now-demo-rcv.ino
  Reads data from Initiator
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

#define servo1Pin 21
#define servo2Pin 17

Servo myServo1;
Servo myServo2;

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
int i = 90;
int j = 90;

// Create a structured object
struct_message myData;


// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len); 
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

  
  if(myData.e == 0) {
      myServo1.write(i);
      i=i+5;
      if(i>180) {i=180;};
      delay(20);
  } else if(myData.f == 0) {
      myServo1.write(i);
      i=i-5;
      if(i<0) {i=0;};
      delay(20);
  } else if (myData.g == 0) {
      myServo2.write(j);
      j=j+5;
      if(j>180) {j=180;};
      delay(20);    
  } else if (myData.h == 0) {
      myServo2.write(j);
      j=j-5;
      if(j<0) {j=0;};
      delay(20);    
  }
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  //Allocate timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);  
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo1.setPeriodHertz(50);
  myServo1.attach(servo1Pin, 500, 2400);
  myServo1.write(i);
  delay(50);

  myServo2.setPeriodHertz(50);
  myServo2.attach(servo2Pin, 500, 2400);
  myServo2.write(j);
  delay(50);
  
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
}
