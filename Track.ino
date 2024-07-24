void TracJC(int MotorSpeed,int Time){
    int Status = 0;
    while(Status == 0){
      ReadCalibrate();
      if(F[0] > 550 && F[1]> 550) Status = 1;
      else if(F[2] > 550 && F[3] > 550) Status = 1;
      else if(F[0] > 550) tl(30);
      else if(F[1] > 550) sl(30);
      else if(F[2] > 550) sr(30);
      else if(F[3] > 550) tr(30);
      else ForwardSpeedTime(MotorSpeed, 1);
    }
  TuneJc(MotorSpeed);
}

void TuneJc(int BaseSpeed){

  if(BaseSpeed<=50) ForwardSpeedTime(BaseSpeed,100);
  else if(BaseSpeed<=60) ForwardSpeedTime(BaseSpeed,50);
  else if(BaseSpeed<=70)ForwardSpeedTime(BaseSpeed,80);
  else if(BaseSpeed<=80) ForwardSpeedTime(BaseSpeed,10);
  //else if(BaseSpeed<=90) ForwardSpeedTime(BaseSpeed,150);
  //else if(BaseSpeed<=100) ForwardSpeedTime(BaseSpeed,150);

}
void TrackSelect(int spd, char x) {
  if (x == 's') {
    MotorStop();
  } else if (x == 'p') {
    Motor(spd, spd);
    delay(30);
    while (1) {
      Motor(spd, spd);
      ReadCalibrate();
      if (F[0] < 550 && F[7] < 550) {
        Motor(spd, spd);
        delay(5);
        break;
      }
    }


  } else if (x == 'l') {
    TurnLeft();
  } else if (x == 'r') {
    TurnRight();
  }
}

void TrackCross(int Speed, float Kp, float Kd, char select) {
  while (1) {
    PID(Speed, Kp, Kd);
    ReadCalibrate();
    if ((F[1] > 550 && F[6] > 550) || (F[0] > 550 && F[3] > 550) || (F[4] > 550 && F[7] > 550)) {
      beep(1);
      break;
    }
  }
  TuneJc(Speed);
  TrackSelect(Speed, select);
}

void TrackCrossC(int Speed, float Kp, float Kd, char select) {
  while (1) {
    PID(Speed, Kp, Kd);
    ReadCalibrate();
    if ((F[1] > 550 && F[6] > 550)) {
      beep(1);
      break;
    }
  }
  TuneJc(Speed);
  TrackSelect(Speed, select);
}

void TrackCrossR(int Speed, float Kp, float Kd, char select) {
  while (1) {
    PID(Speed, Kp, Kd);
    ReadCalibrate();
    if ((F[4] > 550 && F[7] > 550)) {
      beep(1);
      break;
    }
  }
  TuneJc(Speed);
  TrackSelect(Speed, select);
}

void TrackCrossL(int Speed, float Kp, float Kd, char select) {
  while (1) {
    PID(Speed, Kp, Kd);
    ReadCalibrate();
    if ((F[0] > 550 && F[3] > 550)) {
      beep(1);
      break;
    }
  }
  TuneJc(Speed);
  TrackSelect(Speed, select);
}

void TrackDistance(int Speed, float Kp, float Kd) {
  while (1) {
    PID(Speed, Kp, Kd);
    ReadCalibrate();
    if (analogRead(8) < 550) {
      MotorStop();
      beep(1);
      break;
    }
  }
}
void TrackDist(int Speed, float Kp, float Kd) {
  while (1) {
    PID(Speed, Kp, Kd);
    ReadCalibrate();
    if (analogRead(8) == distt) {
      MotorStop();
      beep(1);
      break;
    }
  }
}

void TrackTime(int Speed, float Kp, float Kd, int TotalTime) {
  unsigned long StartTime = millis();
  unsigned long EndTime = StartTime + TotalTime;
  while (millis() <= EndTime) {
    PID(Speed, Kp, Kd);
  }
  beep(1);
}

void TrackSumValue(int Speed, float Kp, float Kd, int value, char select) {
  while (1) {
    PID(Speed,Kp,Kd);
       if (Read_sumValue_sensor() >= value) {
      beep(1);
      break;
    }
    
  }
  TuneJc(Speed);
  TrackSelect(Speed, select);
}

int Read_sumValue_sensor(){
	 int value = 0;
   int SumValue = 0;
    if (LineColor == 0) {
   
    for (int i = 0; i < NUM_SENSORS; i++) {
      unsigned int calmin, calmax;
      
      calmin = MinValue[i];
      calmax = MaxValue[i];
      value = map(analog(i), calmin, calmax, 0, 1000);
      if (value < 0) value = 0;
      if (value > 1000) value = 1000;
      SumValue += value;
        }
  } else {
   
    for (int i = 0; i < NUM_SENSORS; i++) {
      unsigned int calmin, calmax;
      
     calmin = MinValue[i];
      calmax = MaxValue[i];
      value = map(analog(i), calmin, calmax, 1000, 0);
      if (value < 0) value = 0;
      if (value > 1000) value = 1000;
      SumValue += value;
      }
     
  } 
  return SumValue;
}

// int Read_sumValue_sensor(){
// 	int value = 0;
// 	for(int i = 0;i<NUM_SENSORS;i++){
// 		if(LineColor == 0){
      
//       value +=  map(analog(i), MinValue[i], MaxValue[i],0, 1000);
	       
// 	    }
// 	    else {
// 	      value +=  map(analog(i), MinValue[i], MaxValue[i], 1000, 0);
// 	    }	
// 	}
	 
//     return value;
// }