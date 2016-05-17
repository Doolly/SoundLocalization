#include <Stepper.h>
#include "TimerThree.h"

#define STEPS 200
#define MIC_0 2
#define MIC_1 4
#define MIC_2 6
#define MOTER_PIN_1 8
#define MOTER_PIN_2 9
#define MOTER_PIN_3 10
#define MOTER_PIN_4 11

Stepper stepper(STEPS, MOTER_PIN_1, MOTER_PIN_2, MOTER_PIN_3, MOTER_PIN_4);

void TimeStamp(void);
void Change_Value_in_Serial();
void PhaseFree(void);
void Move(int ang);
void Get_angle(void);

int angle = 0;
int last_angle = 0;
String command;

const int limit = 450;
const int moter_speed = 240; //240rpm
const int delay_time = 5; // 3us

long time_dif[3] = {0, 0, 0};
unsigned long stamp_now[3] = {0, 0, 0};
unsigned long micros_timer = 0;
bool flag[3] = {0, 0, 0};
bool flag_now[3] = {false, false, false};
bool flag_last[3] = {false, false, false};

void callback() {
  micros_timer++;

}

void setup() {
  pinMode(MIC_0, INPUT);
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  Serial.begin(9600);
  stepper.setSpeed(120); //120rpm
  Timer3.initialize(1);
  //TimerThree.setPeriod(1);
  Timer3.attachInterrupt(callback);
}

void loop() {
  TimeStamp();

  //  Change_Value_in_Serial();
  //  angle = CalAng(stamp_now);
  //  Move(angle);
}




