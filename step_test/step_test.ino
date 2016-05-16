#include <Stepper.h>
#define STEPS 200
#define MIC_0 2
#define MIC_1 3
#define MIC_2 21
#define MOTER_PIN_1 8
#define MOTER_PIN_2 9
#define MOTER_PIN_3 10
#define MOTER_PIN_4 11

Stepper stepper(STEPS, MOTER_PIN_1, MOTER_PIN_2, MOTER_PIN_3, MOTER_PIN_4);

int TimeStamp(void);
void Change_Value_in_Serial(void);
void PhaseFree(void);
void Move(int ang);
int CalAng(void);
void Mic_0(void);
void Mic_1(void);
void Mic_2(void);

int angle = 0;
int last_angle = 0;
String command;
long time_dif[3]  = {0,0,0};
unsigned long stamp_now[3] = {0, 0, 0};
unsigned long stamp_last[3] = {0, 0, 0};
bool flag_now[3] = {false, false, false};
bool flag_last[3] = {false, false, false};


void setup() {
  pinMode(MIC_0, INPUT);
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(MIC_0), Mic_0, RISING);
  attachInterrupt(digitalPinToInterrupt(MIC_1), Mic_1, RISING);
  attachInterrupt(digitalPinToInterrupt(MIC_2), Mic_2, RISING);
  Serial.begin(9600);
  stepper.setSpeed(240); //120rpm
}

void loop() {
  TimeStamp();
  //Change_Value_in_Serial();
  //angle = CalAng();
  Move(angle);
  //stepper.step(angle);
//  for (int i = 0 ; i < 3 ; i++) {
//    stamp_last[i] = stamp_now[i];
//    flag_last[i] = flag_now[i];
//  }
}




