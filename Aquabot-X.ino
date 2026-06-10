///Choice IB MYP 3 robot///
#include "BTS7960.h"

const uint8_t LM_EN = 4;     //6
const uint8_t LM_L_PWM = 5;  //3
const uint8_t LM_R_PWM = 6;

const uint8_t RM_EN = 9;     //11
const uint8_t RM_L_PWM = 10;  //9
const uint8_t RM_R_PWM = 11;  //10

int c_en = 3;
int cbp = 7;
int cbn = 8;

BTS7960 LM_motorController(LM_EN, LM_L_PWM, LM_R_PWM);
BTS7960 RM_motorController(RM_EN, RM_L_PWM, RM_R_PWM);

int speed_forward = 0;
int speed_backward = 0;
int speed_left = 0;
int speed_right = 0;



int fb = 15;
int lr = 14;
int conv = 16;

int spd;


void setup() {
  Serial.begin(9600);
  pinMode(fb, INPUT);
  pinMode(lr, INPUT);
  pinMode(conv, INPUT);
  pinMode(c_en, OUTPUT);
  pinMode(cbp, OUTPUT);
  pinMode(cbn, OUTPUT);

}

void loop()
{
  long FB, LR, CONV;
  FB = pulseIn(fb, HIGH);
  LR = pulseIn(lr, HIGH);
  CONV = pulseIn(conv, HIGH);

  Serial.print(" FB = ");
  Serial.print(FB);

  Serial.print(" LR = ");
  Serial.print(LR);

  Serial.print(" CONV = ");
  Serial.println(CONV);

  LM_motorController.Enable();
  RM_motorController.Enable();

  


  if (FB > 1650 && LR < 1650 && LR > 1350)
  {
    spd = map(FB, 1650, 2000, 10, 150);
    LM_motorController.TurnLeft(spd);
    RM_motorController.TurnRight(spd);
    Serial.print(" spd = ");
    Serial.print(spd);
    Serial.print(" FORWARD");
  }

  else if (FB < 1350 && LR < 1650 && LR > 1350)
  {
    spd = map(FB, 1350, 950, 10, 150);
    LM_motorController.TurnRight(spd);
    RM_motorController.TurnLeft(spd);
    Serial.print(" spd = ");
    Serial.print(spd);
    Serial.print(" BACKWARD");
  }

  else if (LR > 1650 && FB < 1650 && FB > 1350)
  {
    spd = map(LR, 1650, 2000, 20, 125);
    LM_motorController.TurnRight(spd);
    RM_motorController.TurnRight(spd);
    Serial.print(" spd = ");
    Serial.print(spd);
    Serial.print(" RIGHT");
  }

  else if (LR < 1350 && FB < 1650 && FB > 1350)
  {
    spd = map(LR, 1350, 950, 20, 125);
    LM_motorController.TurnLeft(spd);
    RM_motorController.TurnLeft(spd);
    Serial.print(" spd = ");
    Serial.print(spd);
    Serial.print(" LEFT");
  }
  else if (CONV > 1650 )
  {
    spd = map(CONV, 1650, 2000, 0, 255);
    analogWrite(c_en,spd);
    digitalWrite(cbp,LOW);
    digitalWrite(cbn,HIGH);
  
    Serial.print(" CONV RUN");
  }
  else if (CONV < 1350 )
  {
    
    analogWrite(c_en,0);
    digitalWrite(cbp,LOW);
    digitalWrite(cbn,LOW);
  
    Serial.print(" CONV STOP");
  }

  else
  {
    LM_motorController.Stop();
    RM_motorController.Stop();
    LM_motorController.Disable();
    RM_motorController.Disable();
    analogWrite(c_en,0);
    digitalWrite(cbp,LOW);
    digitalWrite(cbn,LOW);
    Serial.print("STOP");
  }
}