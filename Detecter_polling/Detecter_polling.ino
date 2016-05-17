#include <Stepper.h>
#include <math.h>
#define STEPS 200 //모터의 스텝수
#define MIC_0 2
#define MIC_1 4
#define MIC_2 6
#define MOTER_PIN_1 8
#define MOTER_PIN_2 9
#define MOTER_PIN_3 10
#define MOTER_PIN_4 11

Stepper stepper(STEPS, MOTER_PIN_1, MOTER_PIN_2, MOTER_PIN_3, MOTER_PIN_4);

void Change_Value_in_Serial(void);
void PhaseFree(void);
void Move(void);
void GetAngle(void);
void TimeStamp(void);

const int moter_speed = 30; // rpm
double angle = 0;
int angle_step = 0;
int last_angle_step = 0;
long time_dif[3] = {0, 0, 0};
//time_dif[0] = 발생지에서 2번 까지 걸린 시간 - 1번 까지 걸린 시간
//time_dif[1] = 발생지에서 1번 까지 걸린 시간 - 0번 까지 걸린 시간
//time_dif[2] = 발생지에서 2번 까지 걸린 시간 - 0번 까지 걸린 시간
bool flag_now[3] = {false, false, false};

void setup() {
  pinMode(MIC_0, INPUT);
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  Serial.begin(9600);
  stepper.setSpeed(moter_speed);
}

void loop() {
  TimeStamp();
  GetAngle();
  Move();
}

//Change_Value_in_Serial();




