double Get_angle(void) {
  while ((flag_now[0] == false) || (flag_now[1] == false) || (flag_now[2] == false));
  time_dif[1] = stamp_now[1] - stamp_now[0];
  time_dif[2] = stamp_now[2] - stamp_now[0];
  Serial.print("time_dif[1] = "); Serial.println(time_dif[1]);
  Serial.print("time_dif[2] = "); Serial.println(time_dif[2]);
  double tangential = 1.15 * time_dif[2] / time_dif[1] - 0.58;
  if (tangential > 0 ) {
    if (time_dif[2] < 0) {
      angle = atan(tangential);
      Serial.print("angle 1sabun = "); Serial.println(angle);
    }
    else {
      angle = atan(tangential) - PI / 2;
      Serial.print("angle 3sabun = "); Serial.println(angle);
    }
  }
  else  {
    if ((stamp_now[2] > stamp_now[0]) && (stamp_now[2] > stamp_now[1])) {
      angle = atan(tangential);
      Serial.print("angle 2sabun = "); Serial.println(angle);
    }
    else {
      angle = atan(tangential) + PI / 2;
      Serial.print("angle 4sabun = "); Serial.println(angle);
    }
  }
  double angle_in_degree = angle * 180 / PI;
  Serial.print("angle = ");
  Serial.print(angle);
  Serial.print("    angle_in_degree = ");
  Serial.println(angle_in_degree);

  flag_now[0] = false;
  flag_now[1] = false;
  flag_now[2] = false;

  return angle;
}

void Move(int Angle_now) {
  // int angle_dif = Angle_now - last_angle;
  //if (angle_dif != 0) {
  int num_step = map(Angle_now, -PI, PI, -200, 200);
  stepper.step(num_step);
  last_angle = Angle_now;
  PhaseFree();
  Serial.print("num_step = ");
  Serial.println(num_step);
  Serial.println("/////////////////////////////////////////////////////////////////////////////");
  // }
}

void Mic_0_stamp(void) {
  unsigned long temp;
  temp = micros();
  if (((temp - stamp_last[0]) > bounce_delay)) {
    stamp_now[0] = temp;
    flag_now[0] = true;
  }
  stamp_last[0] = stamp_now[0];
  Serial.print("Mic_0 stamp = ");
  Serial.print(stamp_now[0]);
  Serial.print("   flag_now[0] = ");
  Serial.println(flag_now[0]);
}

void Mic_1_stamp(void) {
  unsigned long temp;
  temp = micros();
  if (((temp - stamp_last[1]) > bounce_delay)) {
    stamp_now[1] = temp;
    flag_now[1] = true;
  }
  stamp_last[1] = stamp_now[1];
  Serial.print("Mic_1 stamp = ");
  Serial.print(stamp_now[1]);
  Serial.print("   flag_now[1] = ");
  Serial.println(flag_now[1]);
}

void Mic_2_stamp(void) {
  unsigned long temp;
  temp = micros();
  if (((temp - stamp_last[2]) > bounce_delay)) {
    stamp_now[2] = temp;
    flag_now[2] = true;
  }
  stamp_last[2] = stamp_now[2];
  Serial.print("Mic_2 stamp = ");
  Serial.print(stamp_now[2]);
  Serial.print("   flag_now[2] = ");
  Serial.println(flag_now[2]);
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

