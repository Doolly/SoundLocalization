#include <Stepper.h>
#include <math.h>
#include <Servo.h>
#include "MatrixMath.h"

#define STEPS 200 //모터의 스텝수
#define MIC_0 14
#define MIC_1 15
#define MIC_2 16
#define MIC_3 17
//#define STEP_PIN_1 3
//#define STEP_PIN_2 4
//#define STEP_PIN_3 5
//#define STEP_PIN_4 6
#define SERVO_PIN 7
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6

#define N  (2)

float A[N][N];
float B[N] ;
float C[N] ;
float x, y;

Servo servo;

void Change_Value_in_Serial(void);
void PhaseFree(void);
void Move(void);
void GetAngle(void);
void TimeStamp(void);


const int moter_speed = 50; // rpm
String command; //debuging 용 변수
double angle = 0;
int angle_step = 0;
int last_angle_step = 0;

long time_dif[4] = {0, 0, 0, 0};
bool flag_now[4] = {false, false, false, false};

void setup() {
  pinMode(MIC_0, INPUT);
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  pinMode(MIC_3, INPUT);

  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}

void loop() {
  while (Serial.available()) {
  //TimeStamp();
  //GetAngle();
  //  Move();
  Change_Value_in_Serial();

    motorctrl(100, angle_step);
    //PhaseFree();
  }
}






