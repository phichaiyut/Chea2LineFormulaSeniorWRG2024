void ShowCalibate(){
oled.clear();
  oled.text(0,0,"     Press OK  ");
  oled.text(2,0,"        to ");
  oled.text(3,0,"start caribrate Front Sensor");
 
  oled.show();}
  
  void ShowStart(){
  oled.clear();                 //เคลียร์หน้าจอ
  oled.mode(0);                 //หมุนหน้าจอ 0 องศา
  oled.textSize(1);             //กำหนดขนาดตัวอักษร
  oled.text(0,0,"Chea 2 Robotics"); //กำหนดข้อความที่จะแสดง
  oled.text(1,0,"WRG 2024 Senior");
  oled.text(2,0,"OK : Normal");  
  oled.text(3,0,"OK>2s Caribrate");
  oled.text(4,0,"A : AutoCaribrate");
  oled.text(5,0,"A>2s : ShowCaribrate");
  oled.text(6,0,"B : AutoCaribrate");
  oled.text(7,0,"B>2s : ShowAnalog");
  oled.show();  
  }

 void Show9Analog() {
    beep(0);
    while(1) {
        oled.clear();
        oled.text(0, 0, "Read A0:A8 Sensor");
        oled.text(1, 0, "A0 : %d", analog(0));        
        oled.text(2, 0, "A1 : %d", analog(1));
        oled.text(3, 0, "A2 : %d", analog(2));
        oled.text(4, 0, "A3 : %d", analog(3));
        oled.text(5, 0, "A4 : %d", analog(4));
        oled.text(6, 0, "A5 : %d", analog(5));
        oled.text(7, 0, "A6 : %d", analog(6));
        oled.text(1, 10, "A7 : %d", analog(7));
        oled.text(2, 10, "A8 : %d", analog(8));
        oled.show();
        delay(100);  // เพิ่มการหน่วงเวลา 1 วินาที
    }
}


void ShowReadCalibrate(){
beep(0);
while(1){
  ReadCalibrate();
  oled.clear();
  oled.text(0, 0, "Read Sensor Calibrate");
  oled.text(1,0,"A0 : %d", F[0]);
  oled.text(2,0,"A1 : %d", F[1]);
  oled.text(3,0,"A2 : %d", F[2]);
  oled.text(4,0,"A3 : %d", F[3]);
  oled.text(5,0,"A4 : %d", F[4]);
  oled.text(6,0,"A5 : %d", F[5]);
  oled.text(7,0,"A6 : %d", F[6]);
  oled.text(1,10,"A7 : %d", F[7]);
  oled.text(2,10,"A8 : %d", F[8]);
  oled.show();    
}
}

void ShowCaliberateRobotSensor(){
  beep(0);
  oled.clear();
  oled.text(0,0,"Press OK caribrate");
  oled.show();
  SW_OK_press();        // รอจนกว่าจะกดปุ่ม OK
  beep(0);
  CalibrateSensor(20, 200);
  beep(0);
  oled.clear();
  oled.text(0,0,"Min Sensor");
  oled.text(1,0,"%d", MinValue[0]);
  oled.text(2,0,"%d", MinValue[1]);
  oled.text(3,0,"%d", MinValue[2]);
  oled.text(4,0,"%d", MinValue[3]);
  oled.text(5,0,"%d", MinValue[4]);
  oled.text(6,0,"%d", MinValue[5]);
  oled.text(7,0,"%d", MinValue[6]);
  oled.text(1,10,"%d", MinValue[7]);

  oled.show();

   SW_OK_press();        // รอจนกว่าจะกดปุ่ม OK
  oled.clear();
  oled.text(1,0,"%d", MaxValue[0]);
  oled.text(1,1,"%d", MaxValue[0]);
  oled.text(2,1,"%d", MaxValue[1]);
  oled.text(3,1,"%d", MaxValue[2]);
  oled.text(4,1,"%d", MaxValue[3]);
  oled.text(5,1,"%d", MaxValue[4]);
  oled.text(6,1,"%d", MaxValue[5]);
  oled.text(7,1,"%d", MaxValue[6]);
  oled.text(1,10,"%d", MaxValue[7]);
  oled.show();    

}

void ShowRead_sumValue_sensor(){
beep(0);
while(1){
  ReadCalibrate();
  oled.clear();
  oled.text(0, 0, "Read_sumValue_sensor");
  oled.text(1,0,"Sum :  : %d", Read_sumValue_sensor());
  oled.show();    
}
}

char Read_sw_OK()  {
  if (SW_OK()) return(1);     //press sw OK
  //else if(digitalRead(18)==0) {digital_sw = 1; return(1);}  //press digital sw 
  else return(0);
}
void sw_ok_unpress()  {
  while(Read_sw_OK()) {delay(10);}
}
void Wait_sw_ok_press()  {
  while(Read_sw_OK()==0) {delay(10);}
}
