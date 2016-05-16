void Get_angle(void) {
  if (flag_now[0] == true && flag_now[1] == true && flag_now[2] == true) {
    time_dif[1] = stamp_now[1] - stamp_now[0];
    time_dif[2] = stamp_now[2] - stamp_now[0];
    Serial.print("time_dif[1] = "); Serial.println(time_dif[1]);
    Serial.print("time_dif[2] = "); Serial.println(time_dif[2]);

    if (abs(time_dif[1]) < 1200 && abs(time_dif[2]) < 1200) {
      double tangential = (-60 * time_dif[2] + 300 * time_dif[1]) / (-52 * time_dif[1]) ;
      angle = atan(tangential);

      double angle_in_degree = angle * 180 / PI;

      Serial.print("tangential = "); Serial.println(tangential);
      Serial.print("angle = "); Serial.print(angle);
      Serial.print("    angle_in_degree = "); Serial.println(angle_in_degree);
    }
    else {
      Serial.println("Error!! ");
    }
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
void Move(int Angle_now) {
  int angle_dif = Angle_now - last_angle;
  if (angle_dif != 0) {
    int num_step = map(Angle_now, -PI, PI, -100, 100);
    stepper.step(num_step);
    last_angle = Angle_now;
    PhaseFree();
    Serial.print("num_step = ");
    Serial.println(num_step);
    Serial.println("/////////////////////////////////////////////////////////////////////////////");
  }
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

