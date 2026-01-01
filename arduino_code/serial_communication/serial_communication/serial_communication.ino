#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 125  // Minimum pulse length (0 degrees)
#define SERVOMAX 625  // Maximum pulse length (180 degrees)



void setup() {
// Serial communication initialization
  Serial.begin(9600);
  
  board1.begin();
  board1.setPWMFreq(60); // Servos operate at ~60 Hz

  // Reset servo to default position
  reset();
  
}


void loop() {  
  
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int servo, angle;
  
    if (parseServoCommand(input, servo, angle)) {
      

      // Fix Joint_1 (servo0) 0 --> 130
      if (servo == 0) {
        angle += 100;  
        angle = clamp(angle, 40, 160);
      }

      // Fix Joint_2 (servo1) 0 --> 90
      if (servo == 1) {

        angle -= 45;
        angle *= -1;
//        // Clamp angle to [55, 175]
//        angle = clamp(angle, -85, 35);
        
      }

      if (servo == 2) {
        angle *= -1;  
      }

      if (servo == 3) {
        angle *= -1;
        angle += 45;
      }

      board1.setPWM(servo, 0, angleToPulse(angle));
    
      Serial.print("Servo ");
      Serial.print(servo);
      Serial.print(" set to ");
      Serial.print(angle);
      Serial.println("°");
    } else {
      Serial.println("Invalid command. Format: servo3=45");
    }

  }
  
}

int clamp(int angle, int min_val, int max_val) {
  if (angle < min_val) {
      angle = min_val;
  } 
  else if (angle > max_val) {
      angle = max_val;
  }
  return angle;

  
}

void reset() {
//  board1.setPWM(0, 0, angleToPulse(0)); // Servo 0 (Base)
//  board1.setPWM(1, 0, angleToPulse(0)); // Servo 1 (Bottom Arm)
//  board1.setPWM(2, 0, angleToPulse(0)); // Servo 2 (Mid Arm)
//  board1.setPWM(3, 0, angleToPulse(0)); // Servo 3 (Wrist)
  board1.setPWM(4, 0, angleToPulse(0)); // Servo 4 (Hand Rotation)
  board1.setPWM(5, 0, angleToPulse(45)); // Servo 5 (Grip) Range for grip is 45-90 degrees without overstraining servo
}

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}


bool parseServoCommand(String cmd, int &servo, int &angle) {
  cmd.trim();

  // Must start with "servo"
  if (!cmd.startsWith("servo")) return false;

  // Must contain '='
  int eqIndex = cmd.indexOf('=');
  if (eqIndex == -1) return false;

  // Extract parts
  String servoStr = cmd.substring(5, eqIndex);
  String angleStr = cmd.substring(eqIndex + 1);

  // Servo must be digits only (no negative servos)
  for (char c : servoStr) {
    if (!isDigit(c)) return false;
  }

  // Angle may be negative
  int start = 0;
  if (angleStr.startsWith("-")) {
    if (angleStr.length() == 1) return false; // "-" only is invalid
    start = 1;
  }

  for (int i = start; i < angleStr.length(); i++) {
    if (!isDigit(angleStr[i])) return false;
  }

  servo = servoStr.toInt();
  angle = angleStr.toInt();

  return true;
}
