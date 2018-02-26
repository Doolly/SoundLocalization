void TimeStamp(void) {
  int loop_elapse = 20; //while 문 처리시간 micro sec
  for (int i = 0 ; i < 4; i++) {
    time_dif[i] = 0;
    flag_now[i] = false;
  }
  if ((digitalRead(MIC_0) == HIGH ) | ( digitalRead(MIC_1) == HIGH ) | (digitalRead(MIC_2) == HIGH) | (digitalRead(MIC_3) == HIGH)) { //먼저 하나 받으면 while 진입

    //time_dif[1] = 발생지에서 1번 까지 걸린 시간 - 0번 까지 걸린 시간
    //time_dif[2] = 발생지에서 2번 까지 걸린 시간 - 0번 까지 걸린 시간
    //time_dif[3] = 발생지에서 3번 까지 걸린 시간 - 0번 까지 걸린 시간

    while ((flag_now[0] + flag_now[1] + flag_now[2] + flag_now[3]) < 4) {

      if (digitalRead(MIC_0) == HIGH) {
        if (digitalRead(MIC_1) == LOW) {
          time_dif[1] += loop_elapse;
        }
        if (digitalRead(MIC_2) == LOW) {
          time_dif[2] += loop_elapse;
        }
        if (digitalRead(MIC_3) == LOW) {
          time_dif[3] += loop_elapse;
        }
        flag_now[0] = true;
      }

      if (digitalRead(MIC_1) == HIGH) {
        if (digitalRead(MIC_0) == LOW) {
          time_dif[1] -= loop_elapse;
        }
        flag_now[1] = true;
      }

      if (digitalRead(MIC_2) == HIGH) {
        if (digitalRead(MIC_0) == LOW) {
          time_dif[2] -= loop_elapse;
        }
        flag_now[2] = true;
      }
      if (digitalRead(MIC_3) == HIGH) {
        if (digitalRead(MIC_0) == LOW) {
          time_dif[3] -= loop_elapse;
        }
        flag_now[3] = true;
      }
      delayMicroseconds(3);
    }
  }
}


void GetAngle(void) {
  if (flag_now[0] == true && flag_now[1] == true && flag_now[2] == true && flag_now[3] == true) {
    delay(1000);
    Serial.print("time_dif[0] = " + String(time_dif[0]) + "\n");
    Serial.print("time_dif[1] = " + String(time_dif[1]) + "\n");
    Serial.print("time_dif[2] = " + String(time_dif[2]) + "\n");
    Serial.print("time_dif[3] = " + String(time_dif[3]) + "\n");
    //
    //    if ((abs(time_dif[1]) < 500) && (abs(time_dif[2]) < 500) && (time_dif[1] != 0)) {
    //      double tangential = (double) (30 * time_dif[2] - 15 * time_dif[1]) / (26 * time_dif[1]);
    //      double angle_in_degree = 0;
    //
    //      if (tangential >= 0) {
    //        if (time_dif[2] < 0) {
    //          angle = atan(tangential);
    //          angle_in_degree = angle * 180 / PI;
    //          Serial.println("quadrant = 1");
    //        }
    //        else {
    //          angle = atan(tangential) - PI;
    //          angle_in_degree = angle * 180 / PI;
    //          Serial.println("quadrant = 3");
    //        }
    //      }
    //
    //      if (tangential < 0) { //else 보다 보기편함
    //        if (time_dif[1] > 0) {
    //          angle = atan(tangential) + PI;
    //          angle_in_degree = angle * 180 / PI;
    //          Serial.println("quadrant = 2");
    //        }
    //        else if (time_dif[0] > 0) {
    //          angle = atan(tangential);
    //          angle_in_degree = angle * 180 / PI;
    //          Serial.println("quadrant = 4");
    //        }
    //      }
    //      angle_step = (int) map(angle * 1000, -PI * 1000, PI * 1000, -100, 100);
    //      Serial.print("angle = " + String(angle) + "\n");
    //      Serial.print("angle_in_degree = " + String(angle_in_degree) + "\n");
    //      Serial.print("angle_in_step = " + String(angle_step) + "\n");
    flag_now[0] = false;
    flag_now[1] = false;
    flag_now[2] = false;
    flag_now[3] = false;
    //    }
    //
    //    else {
    //      Serial.println("Error! time diffrence is too big or exact 90 dgree");
    //    }
  }
  else if (!(flag_now[0] == flag_now[1] == flag_now[2] == flag_now[3] == 0) && (flag_now[0] == false || flag_now[1] == false || flag_now[2] == false) || flag_now[0] == false) {
    flag_now[0] = false;
    flag_now[1] = false;
    flag_now[2] = false;
    flag_now[3] = false;
  }
}

//void Move() {
//  double angle_dif = angle_step - last_angle_step;
//  stepper.step(angle_dif);
//  last_angle_step = angle_step;
//  PhaseFree();
//}

void PhaseFree(void) {
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

void motorctrl(int servo_angle, int angle_step ) {
  servo.write(servo_angle);

  int angle_dif = angle_step - last_angle_step;

  if (angle_step > 0) {
    digitalWrite(dir, LOW);
    for (int x = 0; x <= angle_dif ; x++)
    {
      digitalWrite(stp, HIGH);
      delay(7);
      digitalWrite(stp, LOW);
      delay(7);
    }
  }
  else {
    digitalWrite(dir, HIGH);
    for (int x = -1; x > angle_dif ; x--)
    {
      digitalWrite(stp, HIGH);
      delay(7);
      digitalWrite(stp, LOW);
      delay(7);
    }
  }
  last_angle_step = angle_step;
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
        angle_step = part2.toInt();
      //      else if (part1.equalsIgnoreCase("off_time"))
      //        off_time = part2.toInt();

      command = "";
    }
    else
      command += c;
  }
}

