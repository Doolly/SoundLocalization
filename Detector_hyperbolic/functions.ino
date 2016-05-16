void Get_angle(void) {
  double a=0, b=0;
  if (flag_now[0] == true && flag_now[1] == true && flag_now[2] == true) {
    time_dif[0] = stamp_now[1] - stamp_now[0];
    time_dif[1] = stamp_now[2] - stamp_now[1];
    time_dif[2] = stamp_now[0] - stamp_now[2];
//    Serial.print("time_dif[0] = "+ String(time_dif[0])+ "\n");
//    Serial.print("time_dif[1] = "+ String(time_dif[1])+ "\n");
//    Serial.print("time_dif[2] = "+ String(time_dif[2])+ "\n");
    if ((stamp_now[1] < stamp_now[0])&&(stamp_now[2] < stamp_now[0])) {
      if((time_dif[1] >0)&&(time_dif[1] < BANDWIDTH)){
        a = (0.34 * time_dif[1])/2;
        b = sqrt(C_SQUARE - a*a);
        angle = atan(b/a) - PI;
      }
      else if((time_dif[1] < 0)&&(time_dif[1] >-BANDWIDTH)){
        time_dif[1] *= -1;
        a = (0.34 * time_dif[1])/2;
        b = sqrt(C_SQUARE - a*a);
        angle = -atan(b/a);
      }
    }
    else if((stamp_now[0] < stamp_now[1])&&(stamp_now[2] < stamp_now[1])){
      if((time_dif[2] > 0)&&(time_dif[2] <BANDWIDTH)){
        a = (0.34 * time_dif[2])/2;
        b = sqrt(C_SQUARE - a*a);
        angle = atan(b/a) - PI/3;
      }
      else if((time_dif[2] < 0)&&(time_dif[2] >-BANDWIDTH)){
        time_dif[2] *= -1;
        a = (0.34 * time_dif[2])/2;
        b = sqrt(C_SQUARE - a*a);
        angle = PI*2/3 - atan(b/a);
      }
    }
    else if((stamp_now[0] < stamp_now[2])&&(stamp_now[1] < stamp_now[2])){
      if((time_dif[0] > 0)&&(time_dif[0] <BANDWIDTH)){
        a = (0.34 * time_dif[0])/2;
        b = sqrt(C_SQUARE - a*a);
        angle = atan(b/a) + PI/3;
      }
      else if((time_dif[2] < 0)&&(time_dif[2] >-BANDWIDTH)){
        time_dif[2] *= -1;
        a = (0.34 * time_dif[2]) /2;
        b = sqrt(C_SQUARE - a*a);
        angle = PI*4/3 - atan(b/a);
      }
    }
    double angle_in_degree = angle * 180 / PI;
    Serial.print("angle_in_degree = " + String(angle_in_degree) + "\n");
    angle_step = (int) map(angle * 1000, -PI*1000, PI*1000, -100, 100);
    
    //Serial.print("angle = ");
    //Serial.print(angle);
    flag_now[0] = false;
    flag_now[1] = false;
    flag_now[2] = false;
  }
  else if (!(flag_now[0] == flag_now[1] == flag_now[2] == 0) && (flag_now[0] == false || flag_now[1] == false || flag_now[2] == false)) {
    if (micros() - main_stamp > 1500) {
      Serial.print("reset flags\n");
      flag_now[0] = false;
      flag_now[1] = false;
      flag_now[2] = false;
      main_stamp = micros();
    }
  }
}

void Move() {
  double angle_dif = angle_step - last_angle_step;
    stepper.step(angle_dif);
    last_angle_step = angle_step;
    PhaseFree();
}

void Mic_0_stamp(void) {
  unsigned long temp;
  temp = micros();
  main_stamp = temp;
  if (((temp - stamp_last[0]) > bounce_delay)) {
    stamp_now[0] = temp;
    if (flag_now[0] == false) {
      flag_now[0] = true;
    }
  }
  stamp_last[0] = stamp_now[0];
}

void Mic_1_stamp(void) {
  unsigned long temp;
  temp = micros();
  main_stamp = temp;
  if (((temp - stamp_last[1]) > bounce_delay)) {
    stamp_now[1] = temp;
    if (flag_now[1] == false) {
      flag_now[1] = true;
    }
  }
  stamp_last[1] = stamp_now[1];
}

void Mic_2_stamp(void) {
  unsigned long temp;
  temp = micros();
  main_stamp = temp;
  if (((temp - stamp_last[2]) > bounce_delay)) {
    stamp_now[2] = temp;
    if (flag_now[2] == false) {
      flag_now[2] = true;
    }
  }
  stamp_last[2] = stamp_now[2];
}

void PhaseFree(void) {
  digitalWrite(MOTER_PIN_1, LOW);
  digitalWrite(MOTER_PIN_2, LOW);
  digitalWrite(MOTER_PIN_3, LOW);
  digitalWrite(MOTER_PIN_4, LOW);
}

void Change_Value_in_Serial(void) { //new line
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

