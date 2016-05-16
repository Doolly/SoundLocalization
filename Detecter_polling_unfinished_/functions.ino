void Change_Value_in_Serial() //new line
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

void TimeStamp(unsigned long *a) {
  bool flag[3] = {0, 0, 0};
  flag[0] = digitalRead(MIC_0);
  flag[1] = digitalRead(MIC_1);
  flag[2] = digitalRead(MIC_2);

  for (int i = 0; i < 3 ; i++) {
    if (flag[i] != flag_last[i] )
      last_bounce_time[i] = millis(); //flag가 바뀐 순간 기록
  }

  for (int i = 0; i < 3 ; i++) {
    if ((millis() - last_bounce_time[i])  > debounce_time) { //현재에서 전에 바뀐 순간까지가 0.05.초 이상이면
      if (flag[i] != flag_now[i]) { //0.05초가 지난후 바껴있으면
        flag_now[i] = flag[i];

        if (flag_now[i] == HIGH) //그 바뀐게 HIGH 이면
          stamp_now[i] = micros(); //스탬프를 찍는다
      }
    }
    flag_last[i] = flag[i];
  }
//  Serial.print("stamp_now[0] = ");
//  Serial.println(stamp_now[0]);
//  Serial.print("stamp_now[1] = ");
//  Serial.println(stamp_now[1]);
}

int CalAng(unsigned long *a) {
  bool change_f = false;
  double radian = 0;

  if ( (flag_last[0] != flag_now[0]) && (flag_last[1] != flag_now[1]) ) { //셋다 다르면 계산시작
    change_f = true;
  }
  if (change_f == true) {
    time_dif = a[0] - a[1];
    radian = acos(0.34 * time_dif / 300);
    //angle = map(radian, 0, PI, 0, 100);
    Serial.print("time_dif = ");
    Serial.println(time_dif);
    Serial.print("radian = ");
    Serial.println(radian);
  }
//  else {
//    angle = 0;
//  }

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
