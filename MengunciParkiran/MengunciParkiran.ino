#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <SPI.h>

MFRC522 mfrc522(4, 9);
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo parkiran1;
Servo parkiran2;
Servo parkiran3;
Servo parkiran4;
Servo parkiran5;

const byte numRows = 4;
const byte numCols = 4;

boolean RFIDMode = true;
String tagUID_1 = "B9 78 7F 98";
String tagUID_2 = "62 F2 CD 1A";
String tagUID_3 = "59 38 09 BA";
String tagUID_4 = "D9 F3 2F 99";
String tagUID_5 = "D9 99 9B 98";

char key_pressed = 0;
uint8_t i = 0;

char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {A3, A2, A1, A0};
byte colPins[numCols] = {3, 2, 1, 0};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
  Serial.begin(9600);
  parkiran1.attach(7);
  parkiran2.attach(5);
  parkiran3.attach(6);
  parkiran4.attach(8);
  parkiran5.attach(10);
  parkiran1.write(0);
  parkiran2.write(0);
  parkiran3.write(0);
  parkiran4.write(0);
  parkiran5.write(0);
  lcd.begin();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.clear();
}

void loop()
{
  if (RFIDMode == true) {
    lcd.clear();
    lcd.print("Tag rfid anda");
    delay(3000);
    lcd.clear();
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();
    //Checking the card
    if (tag.substring(1) == tagUID_1 || tagUID_2 || tagUID_3 || tagUID_4 || tagUID_5)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ID Terdeteksi");
      lcd.setCursor(0, 1);
      lcd.print(tag);
      delay(3000);
      lcd.clear();
      lcd.print("Pilih parkiran");
      lcd.setCursor(0, 1);
      lcd.print("anda...");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Masukkan no.parkir");
      RFIDMode = false; // Make RFID mode false
    }
    else
    {
      // If UID of tag is not matched.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ID tidak sesuai");
      lcd.setCursor(0, 1);
      lcd.print("Akses Ditolak");
      delay(3000);
      lcd.clear();
    }
  }

  if (RFIDMode == false) {
    char keypressed = myKeypad.getKey();
    if (keypressed != NO_KEY)
    {
      if (keypressed == '1')
      {
        lcd.clear();
        lcd.print(keypressed);
        parkiran1.write(90);
        delay(1000);  
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sepeda Terkunci");
        lcd.setCursor(0, 1);
        lcd.print("di park.1");
        delay(5000);
        RFIDMode = true;

      }
      if (keypressed == '2')
      {
        lcd.print(keypressed);
        parkiran2.write(90);
        delay(15);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sepeda Terkunci");
        lcd.setCursor(0, 1);
        lcd.print("di park.2");
        delay(5000);
        RFIDMode = true;
      }
      if (keypressed == '7')
      {
        lcd.print(keypressed);
        parkiran3.write(90);
        delay(15);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sepeda Terkunci");
        lcd.setCursor(0, 1);
        lcd.print("di park.3");
        delay(5000);
        RFIDMode = true;
      }
      if (keypressed == '4')
      {
        lcd.print(keypressed);
        parkiran4.write(90);
        delay(15);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sepeda Terkunci");
        lcd.setCursor(0, 1);
        lcd.print("di park.4");
        delay(5000);
        RFIDMode = true;
      }
      if (keypressed == '5')
      {
        lcd.print(keypressed);
        parkiran5.write(90);
        delay(15);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sepeda Terkunci");
        lcd.setCursor(0, 1);
        lcd.print("di park.5");
        delay(5000);
        RFIDMode = true;
      }
    }
  }
}
