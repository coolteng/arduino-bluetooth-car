// L298N 馬達驅動板不含數位邏輯閘(74HC00)，並以 MotorA 為車頭右邊輪以及 MotorB 為車頭左邊輪
// 作者：鄧崇林
#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3    10  //定義 I3 接腳
#define MotorB_I4    11  //定義 I4 接腳
#define MotorA_PWM    5  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWM    6  //宣告 PWMB (PWM調速) 接腳

void advance(int a)    // 前進
{
  analogWrite(MotorA_PWM,200);    //設定馬達 (右) 轉速
  analogWrite(MotorB_PWM,200);    //設定馬達 (左) 轉速
  digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
  digitalWrite(MotorA_I2,LOW);
  digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
  digitalWrite(MotorB_I4,LOW);
  delay(a * 100);
}

void turnR(int a)    // 右前彎
{
  analogWrite(MotorA_PWM,80);     // 設定馬達 (右) 轉速
  analogWrite(MotorB_PWM,200);    // 設定馬達 (左) 轉速
  digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
  digitalWrite(MotorA_I2,LOW);
  digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
  digitalWrite(MotorB_I4,LOW);
  delay(a * 100);
  
}

void roundR(int a)    // 原地右旋轉
{
  analogWrite(MotorA_PWM,80);     //設定馬達轉速
  analogWrite(MotorB_PWM,80);
  digitalWrite(MotorA_I1,LOW);    //馬達（右）逆時針轉動
  digitalWrite(MotorA_I2,HIGH);
  digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
  digitalWrite(MotorB_I4,LOW);
  delay(a * 100);
}

void turnL(int a)    // 左前彎
{
  analogWrite(MotorA_PWM,200);    //設定馬達 (右) 轉速
  analogWrite(MotorB_PWM,80);     //設定馬達 (左) 轉速
  digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
  digitalWrite(MotorA_I2,LOW);
  digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
  digitalWrite(MotorB_I4,LOW);
  delay(a * 100);
}

void roundL(int a)    //原地左旋轉
{
  analogWrite(MotorA_PWM,80);     //設定馬達轉速
  analogWrite(MotorB_PWM,80);
  digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
  digitalWrite(MotorA_I2,LOW);
  digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
  digitalWrite(MotorB_I4,HIGH);
  delay(a * 100);
}    

void stopRL(int a)  //停止
{
  digitalWrite(MotorA_I1,HIGH);   //馬達（右）停止轉動
  digitalWrite(MotorA_I2,HIGH);
  digitalWrite(MotorB_I3,HIGH);   //馬達（左）停止轉動
  digitalWrite(MotorB_I4,HIGH);
  delay(a * 100);
}

void back(int a)    //倒車
{
    analogWrite(MotorA_PWM,200);   //設定直流馬達轉速
    analogWrite(MotorB_PWM,200);
    digitalWrite(MotorA_I1,LOW);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(a * 100);     
}

void setup()
{
  Serial.begin(38400); // 事先已經將HC-06藍牙模組由出廠的9600鮑率改為38400，請務必確認
  pinMode(MotorA_I1,OUTPUT);
  pinMode(MotorA_I2,OUTPUT);
  pinMode(MotorB_I3,OUTPUT);
  pinMode(MotorB_I4,OUTPUT);
  pinMode(MotorA_PWM,OUTPUT);
  pinMode(MotorB_PWM,OUTPUT);
}

void loop()
{
  if (Serial.available()) {
    int cmd = Serial.read();  // 讀取藍芽訊號並於下方進行判斷
    switch(cmd) { // 執行藍芽對應指令
      case 'S':  // 倒車
        back(5);
        break;

      case 'O':  // 原地左旋轉
        roundL(5);
        break;
    
      case 'F':  // 左前彎
        turnL(5);
        break;

      case 'T':  // 右前彎
        turnR(5);
        break;
      
      case 'E':  // 原地右旋轉
        roundR(5);
        break;
      
      case 'N':  // 前進
        advance(5);
        break;
        
      case 'G':  // 停止
        stopRL(5);
        break;
    }
  }
} //Loop End
