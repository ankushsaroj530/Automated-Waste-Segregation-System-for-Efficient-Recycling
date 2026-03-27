#include <Servo.h>

Servo myServo;

// Pin definitions
int moisturePin = A0;
int metalPin = 2;

// Threshold for wet waste (adjust based on testing)
int moistureThreshold = 500;

void setup() {
  Serial.begin(9600);

  pinMode(metalPin, INPUT);
  
  myServo.attach(9);
  myServo.write(90); // Neutral position

  Serial.println("Waste Segregation System Started");
}

void loop() {
  int moistureValue = analogRead(moisturePin);
  int metalValue = digitalRead(metalPin);

  Serial.print("Moisture: ");
  Serial.print(moistureValue);
  Serial.print(" | Metal: ");
  Serial.println(metalValue);

  // Check for Metal Waste
  if (metalValue == LOW) {   // depends on sensor (LOW = detected)
    Serial.println("Metal Waste Detected");
    myServo.write(0);        // Move to Metal bin
    delay(3000);
  }
  // Check for Wet Waste
  else if (moistureValue > moistureThreshold) {
    Serial.println("Wet Waste Detected");
    myServo.write(180);      // Move to Wet bin
    delay(3000);
  }
  // Else Dry Waste
  else {
    Serial.println("Dry Waste Detected");
    myServo.write(90);       // Move to Dry bin
    delay(3000);
  }

  // Return to neutral
  myServo.write(90);
  delay(2000);
}
