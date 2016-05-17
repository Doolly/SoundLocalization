void TimeStamp() {
  for (int i = 0; i < 3 ; i++) {
    time_dif[i] = 0;
    stamp_now[i] = 0;
  }

  if (digitalRead(MIC_0) == 1 || digitalRead(MIC_1) == 1 || digitalRead(MIC_2)) {
    for (int i = 0; i < 3 ; i++) {
      stamp_now[i] = 0;
    }
 for (int i = 0; i < 3 ; i++) {
        flag[i] = 0;
      }
    while ((flag[0] + flag[1] + flag[2]) < 3) {
     

      if (digitalRead(MIC_0) == 1 && flag[0] == false) {
        stamp_now[0] = micros_timer;
        flag[0] = true;
      }
      if (digitalRead(MIC_1) == 1 && flag[1] == false) {
        stamp_now[1] = micros_timer;
        flag[1] = true;
      }
      if (digitalRead(MIC_2) == 1 && flag[2] == false) {
        stamp_now[2] = micros_timer;
        flag[2] = true;
      }
     // delayMicroseconds(delay_time);
    }//while

    time_dif[1] = stamp_now[1] - stamp_now[0];
    time_dif[2] = stamp_now[2] - stamp_now[0];
    Serial.print("time_dif[1] = "); Serial.println(time_dif[1]);
    Serial.print("time_dif[2] = "); Serial.println(time_dif[2]);


    if (abs(time_dif[1]) > limit || abs(time_dif[2]) > limit ) {
      Serial.println("diffrence is too big");
    }
  }//if
}//함수

//void Get_angle(void) {
//  if (flag_now[0] == true && flag_now[1] == true && flag_now[2] == true) {
//    time_dif[1] = stamp_now[1] - stamp_now[0];
//    time_dif[2] = stamp_now[2] - stamp_now[0];
//    Serial.print("time_dif[1] = "); Serial.println(time_dif[1]);
//    Serial.print("time_dif[2] = "); Serial.println(time_dif[2]);
//
//    if (abs(time_dif[1]) < 1200 && abs(time_dif[2]) < 1200) {
//      double tangential = (-60 * time_dif[2] + 300 * time_dif[1]) / (-52 * time_dif[1]) ;
//      angle = atan(tangential);
//
//      double angle_in_degree = angle * 180 / PI;
//
//      Serial.print("tangential = "); Serial.println(tangential);
//      Serial.print("angle = "); Serial.print(angle);
//      Serial.print("    angle_in_degree = "); Serial.println(angle_in_degree);
//    }
//    else {
//      Serial.println("Error!! ");
//    }
//    flag_now[0] = false;
//    flag_now[1] = false;
//    flag_now[2] = false;
//  }
//  else if (!(flag_now[0] == flag_now[1] == flag_now[2] == 0) && (flag_now[0] == false || flag_now[1] == false || flag_now[2] == false)) {
//    if (micros() - main_stamp > 1500) {
//      Serial.print("reset flags\n");
//      flag_now[0] = false;
//      flag_now[1] = false;
//      flag_now[2] = false;
//      main_stamp = micros();
//    }
//
//  }
//}

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
