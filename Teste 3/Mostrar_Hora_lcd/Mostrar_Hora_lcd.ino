#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include "Wire.h"

//Definiçao necessarias
LiquidCrystal_I2C lcd(0x27,16,2);
#define DS1307_ADDRESS 0x68
byte zero = 0x00; 

void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight(); 
}

void loop()
{
  //lcd.clear();
  Mostrarelogio();
  Metros();
  delay(200);
}

byte ConverteParaBCD(byte val){ //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)  { //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}

void Mostrarelogio()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int segundos = ConverteparaDecimal(Wire.read());
  int minutos = ConverteparaDecimal(Wire.read());
  int horas = ConverteparaDecimal(Wire.read() & 0b111111); 
  int diadasemana = ConverteparaDecimal(Wire.read()); 
  int diadomes = ConverteparaDecimal(Wire.read());
  int mes = ConverteparaDecimal(Wire.read());
  int ano = ConverteparaDecimal(Wire.read());
  
  //Hora: xx:xx:xx  

  //Mostra a data no Serial Monitor
    lcd.setCursor(0, 0);
    lcd.print("Hora: ");
    lcd.setCursor(6, 0);
    if(horas<10)
    {      
      lcd.print("0");
      lcd.setCursor(7, 0);
    }
    lcd.print(horas);
    lcd.setCursor(8, 0);
    lcd.print(":");
    lcd.setCursor(9, 0);
    if(minutos<10)
    {      
      lcd.print("0");
      lcd.setCursor(10, 0);
    }
    lcd.print(minutos);
    lcd.setCursor(11, 0);
    lcd.print(":");
    lcd.setCursor(12, 0);
    if(segundos<10)
    {      
      lcd.print("0");
      lcd.setCursor(13, 0);
    }
    lcd.print(segundos);
    lcd.setCursor(14, 0);
    lcd.print("  ");
}

 void Metros()
 {
   //Dist.: xxx mts
   unsigned int distancia=123;
   lcd.setCursor(0,1);
   lcd.print("Dist.: ");
   lcd.setCursor(7,1);
   lcd.print(distancia);
   lcd.setCursor(10,1);
   lcd.print(" mts         ");
 }
