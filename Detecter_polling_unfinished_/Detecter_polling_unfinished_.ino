#include <Stepper.h>
#define STEPS 200
#define MIC_0 2
#define MIC_1 4
#define MIC_2 6
#define MOTER_PIN_1 8
#define MOTER_PIN_2 9
#define MOTER_PIN_3 10
#define MOTER_PIN_4 11

Stepper stepper(STEPS, MOTER_PIN_1, MOTER_PIN_2, MOTER_PIN_3, MOTER_PIN_4);

void TimeStamp(unsigned long *a);
void Change_Value_in_Serial();
void PhaseFree(void);
void Move(int ang);
int CalAng(unsigned long *a);

int angle = 0;
int last_angle = 0;
String command;
long time_dif  = 0;
unsigned long stamp_now[3] = {0, 0, 0};
unsigned long stamp_last[3] = {0, 0, 0};
unsigned long last_bounce_time[3] = {0, 0, 0};
unsigned long debounce_time = 50; //debounce time in ms
bool flag_now[3] = {false, false, false};
bool flag_last[3] = {false, false, false};


void setup() {
  pinMode(MIC_0, INPUT);
  pinMode(MIC_1, INPUT);
  pinMode(MIC_2, INPUT);
  Serial.begin(9600);
  stepper.setSpeed(120); //120rpm
}

void loop() {
  TimeStamp(stamp_now);
  Change_Value_in_Serial();
  angle = CalAng(stamp_now);
  Move(angle);
}




