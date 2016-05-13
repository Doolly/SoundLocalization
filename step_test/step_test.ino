#include <Stepper.h>
#define STEPS 200

Stepper stepper(STEPS, 8, 9, 10, 11);

void TimeStamp(unsigned long *a);
int angle = 0;
int pre_angle = 0;
unsigned long time_dif  = 0;
String command;
unsigned long time_stamp[3] = {0, 0, 0};
unsigned long pre_stamp[3] = {0, 0, 0};
bool flag[3] = {false, false, false};
bool pre_flag[3] = {false, false, false};

void setup() {
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  stepper.setSpeed(120);
}

void loop() {
  TimeStamp(time_stamp);
  //Change_Value_in_Serial();
  angle = CalAng(time_stamp);
  Move(angle);
  //stepper.step(angle);
  PhaseFree();
  Serial.println(angle);
  //  Serial.println("TimeStamp[0] = ");
  //  Serial.println(time_stamp[0]);
  //  Serial.println("TimeStamp[1] = ");
  //  Serial.println(time_stamp[1]);
  //  Serial.println("TimeStamp[2] = ");
  //  Serial.println(time_stamp[2]);
  //  Serial.print("PF[0] = ");
  //  Serial.println(pre_flag[0]);
  //  Serial.print("PF[1] = ");
  //  Serial.println(pre_flag[1]);
  //  Serial.print("PF[2] = ");
  //  Serial.println(pre_flag[2]);
  //  Serial.print("F[0] = ");
  //  Serial.println(flag[0]);
  //  Serial.print("F[1] = ");
  //  Serial.println(flag[1]);
  //  Serial.print("F[2] = ");
  //  Serial.println(flag[2]);
}

void Change_Value_in_Serial() //new line
{
  char c;

  if ( Serial.available()) {
    c = Serial.read();
    if (c == '\n') {
      String part1;
      String part2;

      part1 = command.substring(0, command.indexOf(" "));
      part2 = command.substring(command.indexOf(" ") + 1);

      if (part1.equalsIgnoreCase("angle"))
        angle = part2.toInt();

      //      else if (part1.equalsIgnoreCase("off_time"))
      //        off_time = part2.toInt();

      command = "";
    }

    else
      command += c;

  }
}

void TimeStamp(unsigned long* a) {
  if (digitalRead(2) == 1)
    flag[0] = true;
  else
    flag[0] = false;
  if (digitalRead(4) == 1)
    flag[1] = true;
  else
    flag[1] = false;
  if (digitalRead(6) == 1)
    flag[2] = true;
  else
    flag[2] = false;

  for (int i = 0; i < 3 ; i++) {
    if ((pre_flag[i] == false) && (flag[i] == true)) {
      a[i] = micros();
    }
    pre_flag[i] = flag[i];
  }
  //  if(digitalRead(2) == 1)
  //    a[0] = micros();
  //  if(digitalRead(4) == 1)
  //    a[1] = micros();
  //  if(digitalRead(6) == 1)
  //    a[2] = micros();

}

void PhaseFree(void) {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

int CalAng(unsigned long * a) {
  bool change_f = false;
  double radian = 0;
  for (int i = 0 ; i < 3 ; i++) {
    if (pre_stamp[i] != time_stamp[i]) {
      pre_stamp[i] = time_stamp[i];
      change_f = true;
    }
  }
  if (change_f == true) {
    time_dif = a[0] - a[1];
    radian = acos(0.34 * time_dif / 300);
    angle = map(radian, 0, PI, 0, 200);
  }
  else {
    angle = 0;
  }
  //  pre_angle = angle;
  return angle;
}

void Move(int a) {
  int num_step = a - pre_angle;
  stepper.step(num_step);
  pre_angle = a;
}

