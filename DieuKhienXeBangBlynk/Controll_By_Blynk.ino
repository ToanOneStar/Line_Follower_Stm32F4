#define BLYNK_TEMPLATE_ID "test"      // Thay bằng template ID của bạn
#define BLYNK_TEMPLATE_NAME "test"  // Thay bằng tên template của bạn

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define ENA 5   // Điều khiển tốc độ động cơ bên trái GPIO5(D1)
#define ENB 12  // Điều khiển tốc độ động cơ bên phải GPIO12(D6)
#define IN1 3   // L298N in1 Động cơ trái quay GPIO4(D2)
#define IN2 1   // L298N in2 Động cơ trái quay ngược lại GPIO0(D3)
#define IN3 22   // L298N in3 Động cơ phải quay GPIO2(D4)
#define IN4 23  // L298N in4 Động cơ phải quay ngược lại GPIO14(D5)
#define IN5 4
char auth[] = "xkKvqPd3fjqSA6GhtIJtf3kvIbnSyRxB"; // Blynk Auth Token
char ssid[] = "MANDevices Laboratory"; // WiFi SSID
char pass[] = "MANDevices"; // WiFi Password

int tocdoxe = 200;  // Tốc độ động cơ 400 - 1023

/********************************************* Tiến tới *****************************************************/
void lui() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, tocdoxe);
}

void tien() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, tocdoxe );
}

/********************************** Dừng lại ******************************************/
void dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void quay() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, tocdoxe );
}
/**********************************************************/
// Điều khiển bằng nút nhấn trên Blynk - V1 cho đi thẳng
BLYNK_WRITE(V0) {
  int buttonState = param.asInt(); // Đọc trạng thái nút (1 = bật, 0 = tắt)

  if (buttonState == 1) {
    // Nút bật - cho xe đi thẳng
    
  } else {
    // Nút tắt - dừng xe
    dung();
    Serial.println("Xe đã dừng");
  }
}
BLYNK_WRITE(V1) {
  int buttonState = param.asInt(); // Đọc trạng thái nút (1 = bật, 0 = tắt)

  if (buttonState == 1) {
    // Nút bật - cho xe đi thẳng
    tien(); 
    Serial.println("Xe đang đi thẳng");
  } else {
    // Nút tắt - dừng xe
    dung();
    Serial.println("Xe đã dừng");
  }
}
BLYNK_WRITE(V2) {
  int buttonState = param.asInt(); // Đọc trạng thái nút (1 = bật, 0 = tắt)

  if (buttonState == 1) {
    // Nút bật - cho xe đi thẳng
    digitalWrite(IN5, HIGH);
  } else {
    // Nút tắt - dừng xe
    digitalWrite(IN5, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
