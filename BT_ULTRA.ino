#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int echo = A5;
int trg = A4;

#define carSpeed1 110 // the speed is different as car was not moving straight it as getting slightly deviated
#define carSpeed2 160
int rightDistance = 0, leftDistance = 0, middleDistance = 0;
int ena = 5;
int enb = 6;
int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 10;
//int left_sen = 11;
//int center_sen =12;
//int right_sen = 4;
int centre_sensor = A0;
int left_sensor = A2;
int right_sensor = A3;
float d;
int degRot;
float dist;
char cmd;
int IRpin = 3;
int servoPin = A1;
float v;
int wv;
int t;
int rv;
char cmd1;
char cmd2;
Servo myServo;
int servoPos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trg, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(4, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  digitalWrite(ena, HIGH);
  digitalWrite(enb, HIGH);
  pinMode(left_sensor, INPUT);
  pinMode(centre_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  myServo.attach(servoPin);
  myServo.write(70);
}

void loop() {
  //  v=2.35;
  degRot = 60;
  //  d = 4;
  wv = (v - 1.0422) / 0.0076;
  int left = wv;
  int right = wv;
  //  int right = wv-50;
  //  if(right<100){
  //    right =100;
  //  }

  setSpeed(left, right);

  while (Serial.available() == 0) {
  }
  cmd = Serial.read();

  if (cmd == 'B' || cmd == 'b') {
    backward(d, v);
  }
  if (cmd == 'F' || cmd == 'f') {
    forward(d, v);
    Serial.println("Forward");
  }

  if (cmd == 'L' || cmd == 'l') {
    turnLeft(degRot, wv);
  }
  if (cmd == 'R' || cmd == 'r') {
    turnRight(degRot, wv);
  }


  if (cmd == 'v' || cmd == 'V') {
    Serial.println("Set Velocity");
    while (Serial.available() == 0) {
    }
    delay(1000);
    cmd1 = Serial.read();
    if (cmd1 == '0') {
      rv = 0;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 0");
    }
    if (cmd1 == '1') {
      rv = 1;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 1");
    }
    if (cmd1 == '2') {
      rv = 2;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 2");
    }
    if (cmd1 == '3') {
      rv = 3;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 3");
    }
    if (cmd1 == '4') {
      rv = 4;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 4");
    }
    if (cmd1 == '5') {
      rv = 5;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 5");
    }
    if (cmd1 == '6') {
      rv = 6;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 6");
    }
    if (cmd1 == '7') {
      rv = 7;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 7");
    }
    if (cmd1 == '8') {
      rv = 8;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 8");
    }
    if (cmd1 == '9') {
      rv = 9;
      v = (1.20 / 9) * rv + 1.72;
      Serial.println("Speed = 9");
    }

  }

  if (cmd == 'D' || cmd == 'd') {
    Serial.println("Set Distance");
    while (Serial.available() == 0) {
    }
    delay(1000);
    cmd2 = Serial.read();
    if (cmd2 == '0') {
      d = 0;
      Serial.println("Distance = 0");
    }
    if (cmd2 == '1') {
      d = 1;
      Serial.println("Distance = 1");
    }
    if (cmd2 == '2') {
      d = 2;
      Serial.println("Distance = 2");
    }
    if (cmd2 == '3') {
      d = 3;
      Serial.println("Distance = 3");
    }
    if (cmd2 == '4') {
      d = 4;
      Serial.println("Distance = 4");
    }
    if (cmd2 == '5') {
      d = 5;
      Serial.println("Distance = 5");
    }
    if (cmd2 == '6') {
      d = 6;
      Serial.println("Distance = 6");
    }
    if (cmd2 == '7') {
      d = 7;
      Serial.println("Distance = 7");
    }
    if (cmd2 == '8') {
      d = 8;
      Serial.println("Distance = 8");
    }
    if (cmd2 == '9') {
      d = 9;
      Serial.println("Distance = 9");
    }
  }
  if (cmd == 'U' || cmd == 'u') {
    ultrasonic();
    delay(360);
    //      if(cmd == 'S' || cmd =='s'){     //Interrupt so that we can change the mode of the car
    //        stop();
    //        }
  }
  if (cmd == 'T' || cmd == 't') {
    lineTracking();
    //      if(cmd == 'S' || cmd =='s'){       //Interrupt so that we can change the mode of the car
    //        stop();
    //        }
  }
}
void setSpeed(int leftVal, int rightVal) {
  analogWrite(ena, rightVal);
  analogWrite(enb, leftVal);
}

void forward(float d, float v) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  t = d / v * 1000;
  delay(t);
  stop();
}


void backward(float d, float v) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  t = d / v * 1000;
  delay(t);
  stop();
}

void turnRight(int deg, int wv) {
  stop();
  delay(100);
  analogWrite(ena, 180);
  analogWrite(enb, 180);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  t = (deg + 19.733) / 221.66 * 1000.;
  Serial.println("90");
  delay(t);
  stop();
  analogWrite(ena, wv);
  analogWrite(enb, wv);
}

void turnLeft(int deg, int wv) {
  float t;
  stop();
  delay(100);
  analogWrite(ena, 180);
  analogWrite(enb, 180);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  t = (deg + 19.733) / 221.66 * 1000.;
  Serial.println("90");
  delay(t);
  stop();
  analogWrite(ena, wv);
  analogWrite(enb, wv);
}
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


//Ultrasonic distance measurement Sub function
float Distance_test() {
  digitalWrite(trg, LOW);
  delayMicroseconds(2);
  digitalWrite(trg, HIGH);
  delayMicroseconds(20);
  digitalWrite(trg, LOW);
  float Fdistance = pulseIn(echo, HIGH);
  Fdistance = Fdistance / 58. ;
  return (float)Fdistance;
}

void calF() {
  analogWrite(ena, 150);
  analogWrite(enb, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void calB() {
  analogWrite(ena, 110);
  analogWrite(enb, 160);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void calR() {
  stop();
  analogWrite(ena, 150);
  analogWrite(enb, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void calL() {
  stop();
  analogWrite(ena, 150);
  analogWrite(enb, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void ultrasonic() {
  while (1 == 1) {
    myservo.write(70);  //setservo position according to scaled value
    delay(500);
    middleDistance = Distance_test();


    if (middleDistance <= 40) {
      stop();
      delay(500);
      myServo.write(1);
      delay(1000);
      rightDistance = Distance_test();

      delay(500);
      myServo.write(70);
      delay(1000);
      myServo.write(180);
      delay(1000);
      leftDistance = Distance_test();

      delay(500);
      myServo.write(70);
      delay(1000);
      if (rightDistance > leftDistance) {
        turnRight(degRot, wv);
        delay(360);
      }
      else if (rightDistance < leftDistance) {
        turnLeft(degRot, wv);
        delay(360);
      }
      //      else if((rightDistance <= 40) || (leftDistance <= 40)) {
      //        calB();
      //        delay(180);
      //      }
      else {
        calF();
      }
    }
    else {
      calF();
    }
  }
}

void lineTracking() {
  while (1 == 1) {
    int right = analogRead(right_sensor);
    int centre = analogRead(centre_sensor);
    int left = analogRead(left_sensor);
    //  Serial.print(right);
    //  Serial.print(centre);
    //  Serial.print(left);
    //    while(Serial.available() == 0){
    //    }
    //     cmd = Serial.read();
    if (left < 700 && right < 700 && centre > 700)
    {
      calF();
    }
    if (left > 700 && right < 700 && centre < 700)
    {
      calL();
    }
    if (left < 700 && centre < 700 && right > 700) {
      calR();
    }
    //  if (cmd== 'S' || cmd == 's'){
    //  break;
  }
}
}
