#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

//Define all possible states that the button can choose from to determine which data to measure and display
enum b_State {
  temp,pressure,altitude};

 
//Initializations
Adafruit_BMP280 bmp;    // I2C configuration of sensor
LiquidCrystal_I2C lcd(0x3F,20,4);  // set LCD address to 0x3F
b_State reading = temp;   //Initially temperature will be displayed


void setup()
{
  pinMode(53, INPUT);
  
  lcd.init();   // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.printstr("<<<Turning On>>>");
  delay(3000);
  clear(lcd);
  
  if (!bmp.begin()) {
  lcd.setCursor(0,0);
  lcd.print("BMP280 sensor");
  lcd.setCursor(0,1);
  lcd.print("Error!");
  while (1);
  }

  /* Default settings from datasheet of BMP280 sensor. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}


void loop()
{
  
  switch(reading){
    case temp:
    {lcd.setCursor(0,0);
    lcd.print("Temperature:");
    lcd.setCursor(0,1);
    lcd.print(bmp.readTemperature());
    lcd.print(" *C");
    delay(3000);
    clear(lcd);
    }
    break;
    case pressure:
    {
    lcd.setCursor(0,0);
    lcd.printstr("Pressure:");
    lcd.setCursor(0,1);
    lcd.print(bmp.readPressure());
    lcd.print(" Pa");
    delay(3000);
    clear(lcd);
    }
    break;
    case altitude:
    {
    lcd.setCursor(0,0);
    lcd.printstr("Approx altitude:");
    lcd.setCursor(0,1);
    lcd.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    lcd.printstr(" m");
    delay(3000);
    clear(lcd);
    }
    break;
    default:
    {
    lcd.setCursor(0,0);
    lcd.printstr("Error!");
    }
  }
  reading = updateReading(reading);
}

//Functions
void clear(LiquidCrystal_I2C lcd){
  lcd.setCursor(0,0);
  lcd.printstr("                ");
  lcd.setCursor(0,1);
  lcd.printstr("                ");
}

b_State updateReading(b_State r){
  if(digitalRead(53)){
    switch(r){
      case temp:
        r = pressure;
      break;
      case pressure:
        r = altitude;
      break;
      case altitude:
        r = temp;
      break;
      default:
        lcd.print("Error!");
    }
  }
  return r;
}
