int Get_angle(void) {
  while ((flag_now[0] == false) || (flag_now[1] == false) || (flag_now[2] == false)); 
  
    time_dif[0] = stamp_now[1] - stamp_now[0];
    time_dif[1] = stamp_now[2] - stamp_now[1];
    time_dif[2] = stamp_now[0] - stamp_now[2];
  
  flag_now[0] = false;
  flag_now[1] = false;
  flag_now[2] = false;

  return angle;
}

void Move(int Angle_now) {
  int angle_dif = Angle_now - last_angle;
  if (angle_dif != 0) {
    int num_step = map(Angle_now, -PI,PI,-200,200); //수정할지도
    stepper.step(num_step);
    last_angle = Angle_now;
    PhaseFree();
    Serial.print("num_step = ");
    Serial.println(num_step);
  }
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

