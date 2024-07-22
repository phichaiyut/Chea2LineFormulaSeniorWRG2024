#include <POP32.h>
#define NUM_SENSORS 8 //จำนวนเซนเซอร์
#define MaxSpeed 100
#define MinSpeed -100

#define No 0
#define Yes 1
#define SwitchTime  200 //เวลาในการตรวจสอบการกดสวิชในหน่วย ms
int LastError;
int MinValue[NUM_SENSORS];
int MaxValue[NUM_SENSORS];
//uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int LTurnSpdL, LTurnSpdR, TurnDelayL;
int RTurnSpdL, RTurnSpdR, TurnDelayR;
int LineColor = 0;
unsigned short distt = 0;
long Timer, Timer2, Timer3;
int LeftBaseSpeed, RightBaseSpeed,BackLeftBaseSpeed,BackRightBaseSpeed,SW_OK_Status;
void setup() {
  beep(1);
 Serial.begin(9600);
  SW_OK_Status = No;                                                                 // Setup หุ่นยนต์
  //SensorValue(462, 445, 447, 470, 443, 445, 448, 456, 2828, 2777, 2757, 2854, 2807, 2823, 2828, 2854);  //ค่าแสง

  SensorValueMin(462, 445, 447, 470, 443, 445, 448, 456); //ค่าแสงต่ำสุด
  SensorValueMax(2828, 2777, 2757, 2854, 2807, 2823, 2828, 2854); //ค่าแสงสูงสุด
  TurnSpeedLeft(60, 30, 50);                                                          // ค่าเลี้ยวซ้าย TurnSpeedLeft(มอเตอร์ซ้าย, มอเตอร์ขวา, เวลาเลี้ยว);
  TurnSpeedRight(30, 60, 50);                                                         // ค่าเลี้ยวขวา TurnSpeedRight(มอเตอร์ซ้าย, มอเตอร์ขวา, เวลาเลี้ยว);
  TrackLineColor(1);                                                                    //สีของเส้น 1 = ขาว , 0 = ดำ
  
  

  //CaliberateRobotSensor() ;  //Serial Caliberate
  // SerialSensor();  // Serial Monitor ค่าของ Sensor
  // SerialCalibrate();  // Serial Monitor ค่าของ Sensor ที่ Calibrate แล้ว

   ShowStart(); //แสดงหน้าจอ

    while(SW_OK_Status == No)  {  // waiting "OK" button
      if(Read_sw_OK()) {
        StartTimer();
        //Mode=Mode0; 
        SW_OK_Status = Yes;
        beep(1);
        while(Read_sw_OK())  {  //wait unpress OK button
        if(ReadTimer() >= 2000) {
          beep(2);
          ShowCaliberateRobotSensor();
          SW_OK_Status = No;
          }
        }
       }
       //else //CheckKnobMode();  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่
       if(SW_A()) 
       {
          StartTimer();
          beep(1);
          while(SW_A())  {}  //wait unpress SW A button
          if(ReadTimer() >= SwitchTime) {ShowReadCalibrate();} //Mode=Mode1;
          else {CalibrateSensor(20, 200); SW_OK_press();beep(1);} //Mode=Mode2;
          SW_OK_Status = Yes;
       }
       if(SW_B()) 
       {
          StartTimer();
          beep(1);
          while(SW_B())  {}  //wait unpress SW A button
          if(ReadTimer() >= SwitchTime) {Show9Analog();} //Mode=Mode3;
          else {ShowRead_sumValue_sensor();} //Mode=Mode4;
          SW_OK_Status = Yes;
       }
      }
  //SW_OK_press();        // รอจนกว่าจะกดปุ่ม OK
  delay(300);
  StartTimer2();
  

              //ฟังก์ชันทั่วไป
  //TestMotor(); //ทดสอบมอเตอร์วิ่งถูกต้องหรือไม่ โดยการวิ่งไปข้างหน้า
  //ForwardSpeedTime(70, 1000); //เดินหน้าตรง ForwardSpeedTime(ความเร็วมอเตอร์,เวลาที่ใช้);
  //BackwardSpeedTime(70, 1000); //ถอยหลังตรง BackwardSpeedTime(ความเร็วมอเตอร์,เวลาที่ใช้);
  //Left(70 ,250); //เลี้ยวซ้าย (ความเร็วมอเตอร์,เวลาที่ใช้);
  //Right(70 , 250); //เลี้ยวขวา (ความเร็วมอเตอร์,เวลาที่ใช้);
  //TurnLeft(70, 100); //โค้งซ้าย (ความเร็วมอเตอร์,เวลาที่ใช้)
  //TurnRight(70 , 100);  //โค้งขวา (ความเร็วมอเตอร์,เวลาที่ใช้)
  //TurnLeft(); // เลี้ยวซ้ายจนกว่าจะเจอเส้น
  //TurnRight(); //เลี้ยวขวาจนกว่าจะเจอเส้น
 
 // Show9Analog();  //โชว์ค่าเซนเซอร์ A0:A8
// ShowReadCalibrate(); //โชว์ที่ค่า คาลิเบทแล้ว
// ShowCaliberateRobotSensor(); //แสดงหน้าจอพร้อมทำการคาลิเบทเซนเซอร์
// ShowRead_sumValue_sensor();  //แสดงหน้าจอผลรวมเซนเซอร์ที่เจอเส้น


              //คำสั่งเจอแบบต่างๆ >> 'l'=เลี้ยวซ้าย ,'r'=เลี้ยวขวา ,'p'=ตรง ,'s'=หยุด  
  //TracJC(int MotorSpeed,int Time); //TracJC(speed,เวลาที่ใช้ข้ามแยก); //โค้ดสำหรับ Junior
  // TrackCrossL(40, 0.034, 0.34, 'r');  // ใช้เซนเซอร์คู่ซ้ายในการนับแยก
  // TrackCrossR(40, 0.034, 0.34, 'r');  // ใช้เซนเซอร์คู่ขวาในการนับแยก
  // TrackCrossC(40, 0.034, 0.34, 'r');  // ใช้เซนเซอร์คู่กลางในการนับแยก
  // TrackCross(40, 0.034, 0.34, 'r');   // PID จนกว่าจะเจอแยก TrackCross(Speed, Kp , Kd , 'คำสั่งเจอแยก'); 
    TrackTime(70, 0.055, 2.30, 10000);                                                   // PID ด้วยเวลา TrackTime(Speed, Kp , Kd, เวลา); >> 1000 = 1 วินาที
    //TrackSumValue(70, 0.055, 2.30, 4000, 's');                                           //TrackSumValue(speed, kp, kd, ค่าของเซนเซอร์, เงื่อนไข);




// >>>>>>>>>>>>>>>>>>>>>>>>>วางโค้ดใหม่หลังจากนี้บรรทัดนี้ทั้งหมด<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<





}

void loop() {
  Finish(); // หยุดการทำงานมอเตอร์
 // PID(30, 0.009 ,0.0);  // หยุดการทำงานมอเตอร์
}
