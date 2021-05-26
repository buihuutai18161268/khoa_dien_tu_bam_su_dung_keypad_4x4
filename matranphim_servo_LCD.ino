#include <Keypad.h>
#include <LiquidCrystal_I2C.h>      // Khai báo thư viện LCD sử dụng I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 địa chỉ LCD, 16 cột và 2 hàng

#include <Servo.h> // Khai báo thư viện sử dụng cho động cơ
//Bạn có thể tham khảo thêm tại: https://github.com/Chris--A/Keypad/blob/master/examples/HelloKeypad/HelloKeypad.ino

Servo myServo;
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
char STR[4] = {'2', '0', '2', '1'}; // Cài đặt mật khẩu tùy ý
char str[4] = {' ', ' ', ' ', ' '};
int i, j, count = 0;
 
//Định nghĩa các giá trị trả về
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
 
byte rowPins[rows] = {5, 6, 7, 8}; //Cách nối chân với Arduino
byte columnPins[columns] = {9, 10, 11, 12};
 
//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
void setup() {
  Serial.begin(9600);//bật serial, baudrate 9600
  myServo.attach(3); // Khai báo chân điều khiển động cơ
  lcd.init();        // Khai báo sử dụng LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print(" Enter Password");
}
void loop() {  
  char temp = keypad.getKey();
 
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
    }
  }
  if ((int)keypad.getState() ==  HOLD) {
    state++;
    state = constrain(state, 1, n-1);
    delay(holdDelay);
  }
 
  if ((int)keypad.getState() ==  RELEASED) {
    key += state;
    state = 0;
    //Xuất lên Máy tính để xem kết quả
    Serial.println(key);
    // Nhập mật khẩu
    if (i == 0) {
      str[0] = key;
      lcd.setCursor(6, 1);
      lcd.print(str[0]);
      delay(1000); // Ký tự hiển thị trên màn hình LCD trong 1s
      lcd.setCursor(6, 1);
      lcd.print("*"); // Ký tự được che bởi dấu *
    }
    if (i == 1) {
      str[1] = key;
      lcd.setCursor(7, 1);
      lcd.print(str[1]);
      delay(1000);
      lcd.setCursor(7, 1);
      lcd.print("*");
    }
    if (i == 2) {
      str[2] = key;
      lcd.setCursor(8, 1);
      lcd.print(str[2]);
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("*");
    }
    if (i == 3) {
      str[3] = key;
      lcd.setCursor(9, 1);
      lcd.print(str[3]);
      delay(1000);
      lcd.setCursor(9, 1);
      lcd.print("*");
      count = 1;
    }
    i = i + 1;
  }
 
  if (count == 1) {
    if (str[0] == STR[0] && str[1] == STR[1] && str[2] == STR[2] &&
        str[3] == STR[3]) {
      lcd.clear();
      lcd.print("    Correct!");
      delay(3000);
      myServo.write(180); // Mở cửa
      lcd.clear();
      lcd.print("      Opened!");
      i = 0;
      count = 0;
    } else {
      lcd.clear();
      lcd.print("   Incorrect!");
      delay(3000);
      lcd.clear();
      lcd.print("   Try Again!");
      delay(3000);
      lcd.clear();
      lcd.print(" Enter Password");
      i = 0;
      count = 0;
    }
  }
 
  switch (key) {
  case '#':
    lcd.clear();
    myServo.write(90); // Đóng cửa 
    lcd.print("     Closed!");
    delay(5000);
    lcd.clear();
    lcd.print(" Enter Password");
    i = -1;
    break;
  }
  delay(50);
}
