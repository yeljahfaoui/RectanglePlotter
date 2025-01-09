#include "Servo.h"
#include <math.h>

Servo servoR;
Servo servoL;

int angles[2];

const float d = 3.1f; // Distance between 2 servos
const float l = 4.5f; // Small leg length
const float L = 8.7f; // Long leg length
const float X[2] = { -2.4f, 2.4f };
const float Y[2] = { 16.6f , 16.6f };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servoR.attach(5);
  servoL.attach(6);

  angles[0] = 90;
  angles[1] = 90;

  servoR.write(angles[0]);
  servoL.write(angles[1]);

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int x = -2 ; x <= 2 ; x++) {
    IK(x, 6);
  }
  for(int y = 6 ; y >= 5 ; y--) {
    IK(2, y);
  }
  for(int x = 2 ; x >= -2 ; x--) {
    IK(x, 5);
  }
  for(int y = 5 ; y <= 6 ; y++) {
    IK(-2, y);
  }

}

void IK(float x, float y) {
  // todo
  float theta1, theta2, theta3, theta4, theta5, theta6, a, b;

  b = sqrt(pow(Y[1] - y, 2) + pow(X[1] - x, 2));
  a = sqrt(pow(Y[0] - y, 2) + pow(x - X[0], 2));

  theta2 = acos((pow(d, 2) + pow(b, 2) - pow(a, 2)) / (2 * d * b));
  theta3 = acos((pow(l, 2) + pow(b, 2) - pow(L, 2)) / (2 * l * b));

  theta4 = theta2 + theta3;

  theta5 = acos((pow(l, 2) + pow(a, 2) - pow(L, 2)) / (2 * l * a));
  theta6 = acos((pow(d, 2) + pow(a, 2) - pow(b, 2)) / (2 * d * a));

  theta1 = PI - (theta5 + theta6);

  angles[0] = theta4 * 180 / PI;
  angles[1] = theta1 * 180 / PI;

  servoR.write(angles[0]);
  servoL.write(angles[1]);
  delay(100);
}
