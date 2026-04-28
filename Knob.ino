#include <Servo.h>

Servo myservo;

// Correct Pin Definitions for Shield Ports
const int potPin = A0;      // Rotary Angle Sensor
const int pirPin = 2;       // PIR Motion Sensor
const int servoPin = 8;     // Servo Motor
const int trigPin = 9;      // Ultrasonic Trigger
const int echoPin = 10;     // Ultrasonic Echo

void setup() {
  Serial.begin(115200); // Standard for R4 WiFi
  
  myservo.attach(servoPin);
  
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT); // Sends the pulse
  pinMode(echoPin, INPUT);  // Receives the echo

  Serial.println("R4 WiFi System Online");
}

void loop() {
  // 1. Motor follows Rotary Sensor
  int potVal = analogRead(potPin);
  int angle = map(potVal, 0, 1023, 0, 180);
  myservo.write(angle);

  // 2. Ultrasonic Sensor Pulse Logic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Calculate Distance
  long duration = pulseIn(echoPin, HIGH); // Measure time in microseconds
  float distance = (duration * 0.0343) / 2; // Convert to cm

  // 4. Motion Sensor Check
  int motionDetected = digitalRead(pirPin);

  // 5. Output to Serial Monitor
  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print("cm | Motion: ");
  Serial.println(motionDetected == HIGH ? "YES" : "NO");

  delay(50); // Small delay for sensor stability
}



