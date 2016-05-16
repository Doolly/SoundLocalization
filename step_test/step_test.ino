#include <Stepper.h>
#include <math.h>
#define STEPS 200 //모터의 스텝수
#define MIC_0 2
#define MIC_1 3
#define MIC_2 21
#define MOTER_PIN_1 8
#define MOTER_PIN_2 9
#define MOTER_PIN_3 10
#define MOTER_PIN_4 11

Stepper stepper(STEPS, MOTER_PIN_1, MOTER_PIN_2, MOTER_PIN_3, MOTER_PIN_4);

void Change_Value_in_Serial(void);
void PhaseFree(void);
void Move(int ang);
void Get_angle(void);
void Mic_0_stamp(void);
void Mic_1_stamp(void);
void Mic_2_stamp(void);

const int moter_speed = 240; //240rpm
const int bounce_delay = 20000; //0.2us

//int sound_vel = 345000; //   sound velocity in mm/s
//double mic_X_cor[3]={};
//double mic_Y_cor[3]={};

double angle = 0;
double last_angle = 0;
String command;
long time_dif[3] = {0, 0, 0};
unsigned long main_stamp = 0;
unsigned long stamp_now[3] = {0, 0, 0};
unsigned long stamp_last[3] = {0, 0, 0};
volatile bool flag_now[3] = {false, false, false};

void setup() {
  pinMode(MIC_0, INPUT);
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(MIC_0), Mic_0_stamp, RISING);
  attachInterrupt(digitalPinToInterrupt(MIC_1), Mic_1_stamp, RISING);
  attachInterrupt(digitalPinToInterrupt(MIC_2), Mic_2_stamp, RISING);
  Serial.begin(9600);
  stepper.setSpeed(moter_speed);
}

void loop() {
  Get_angle();
  Move(angle);
  //Change_Value_in_Serial();
}




