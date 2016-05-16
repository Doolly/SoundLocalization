void Change_Value_in_Serial(void) //new line
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

int TimeStamp(void) {
  if ((flag_now[0] == true) && (flag_now[1] == true) && (flag_now[2] == true)) {
    time_dif[0] = stamp_now[1] - stamp_now[0];
    time_dif[1] = stamp_now[2] - stamp_now[1];
    time_dif[2] = stamp_now[0] - stamp_now[2];
    for (int i = 0; i < 3 ; i++) {
      if (time_dif[i] < 0) {
        time_dif[i] *= -1;
      }
    }
    if ((stamp_now[0] < stamp_now[1]) && (stamp_now[0] < stamp_now[2])) {
      angle = 0; //+ 34 * time_dif[2] / 1000 - 34 * time_dif[0] / 1000;
      if(time_dif[0] <300){
        angle = 34;
      }
      else if(time_dif[2] < 300){
        angle = -34;
      }
    }
    else if ((stamp_now[1] < stamp_now[0]) && (stamp_now[1] < stamp_now[2])) {
      angle = 67;// + 33 * time_dif[0] / 1500 - 33 * time_dif[1] / 1000;
      if(time_dif[0] <300){
        angle = 34;
      }
      else if(time_dif[1] < 300){
        angle = 100;
      }
    }
    else if ((stamp_now[2] < stamp_now[0]) && (stamp_now[2] < stamp_now[1])) {
      angle = -67;// + 33 * time_dif[2] / 1500 - 33 * time_dif[1] / 1500;
      if(time_dif[1] <300){
        angle = -100;
      }
      else if(time_dif[2] < 300){
        angle = -34;
      }
    }
    flag_now[0] = false;
    flag_now[1] = false;
    flag_now[2] = false;
    
  }
  
  
    Serial.print("stamp_now[0] = ");
    Serial.println(stamp_now[0]);
    Serial.print("stamp_now[1] = ");
    Serial.println(stamp_now[1]);
    Serial.print("stamp_now[2] = ");
    Serial.println(stamp_now[2]);
    Serial.print("angle = ");
    Serial.println(angle);
  return angle;
}

void Move(int ang) {
  int num_step = ang - last_angle;
  stepper.step(num_step);
  last_angle = ang;
  PhaseFree();
}

void PhaseFree(void) {
  digitalWrite(MOTER_PIN_1, LOW);
  digitalWrite(MOTER_PIN_2, LOW);
  digitalWrite(MOTER_PIN_3, LOW);
  digitalWrite(MOTER_PIN_4, LOW);
}

void Mic_0(void) {
  unsigned long temp;
  temp = micros();
  if (((temp - stamp_last[0]) > 20000)) {
    stamp_now[0] = temp;
    flag_now[0] = true;
  }
  stamp_last[0] = stamp_now[0];
}
void Mic_1(void) {
  unsigned long temp;
  temp = micros();
  if (((temp - stamp_last[1]) > 20000)) {
    stamp_now[1] = temp;
    flag_now[1] = true;
  }
  stamp_last[1] = stamp_now[1];
}
void Mic_2(void) {
  unsigned long temp;
  temp = micros();
  if (((temp - stamp_last[2]) > 20000)) {
    stamp_now[2] = temp;
    flag_now[2] = true;
  }
  stamp_last[2] = stamp_now[2];
}

