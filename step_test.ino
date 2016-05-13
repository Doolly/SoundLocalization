#include <Stepper.h>
#define STEPS 200

Stepper stepper(STEPS, 8, 9, 10, 11);

void Change_Value_in_Serial();

char c;
int angle;
String command;


void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");
  stepper.setSpeed(60);
}

void loop() {

  Change_Value_in_Serial();
   stepper.step(angle);
   delay(1000);
  Serial.println(angle);

}

void Change_Value_in_Serial() //new line
{
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

