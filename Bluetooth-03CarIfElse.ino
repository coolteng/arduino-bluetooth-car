// L298N 馬達驅動板不含數位邏輯閘(74HC00)，並以 MotorA 為車頭右邊輪以及 MotorB 為車頭左邊輪
// 作者：鄧崇林
int enA = 5;   // 指定 MotorA PWM (PWM調速) 接腳
int in1 = 8;   // 指定 MotorA_I1 
int in2 = 9;   // 指定 MotorA_I2
int in3 = 10;  // 指定 MotorB_I1
int in4 = 11;  // 指定 MotorB_I2
int enB = 6;   // 指定 MotorB PWM (PWM調速) 接腳

void setup()
{  
  Serial.begin(38400); // 事先已經將HC-06藍牙模組由出廠的9600鮑率改為38400，請務必確認
  pinMode(enA, OUTPUT);  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3,  OUTPUT);
  pinMode(in4,  OUTPUT);
  pinMode(enB, OUTPUT);
}
        
void loop()
{
  if (Serial.available()) {
    int cmd = Serial.read();  // 讀取藍芽訊號並於下方進行判斷
    if ('N' == cmd) {       // 前進
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);;
      analogWrite(enA, 200);
      analogWrite(enB, 200);
      delay(200);      
    } else if ('O' ==cmd) { // 原地左旋轉
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      analogWrite(enA, 80);
      analogWrite(enB, 80); 
      delay(200);
    } else if ('E' == cmd) { // 原地右旋轉
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(enA, 80);
      analogWrite(enB, 80);
      delay(200);
    } else if ('S' == cmd) { // 倒車
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      analogWrite(enA, 200);
      analogWrite(enB, 200);
      delay(200);
    } else if ('G' == cmd) {  // 停車
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      delay(200);
    } else {
      //其他作業;
      delay(500);
    }
  }
} //Loop End
