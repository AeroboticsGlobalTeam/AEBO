/*
 * AEBO.cpp - Library for AEBO robot
 * Created by Lokesh Kode, July 26,2021.
 * Released into public domain
 */

 #include "Arduino.h"
 #include "AEBO.h"
 #include <inttypes.h>
 #include "Wire.h"
 #include "Print.h"
 



 AEBO::AEBO(){
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(11,OUTPUT);
  
 }

void AEBO::Forward(int speed){
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  analogWrite(3,speed);
  analogWrite(11,speed);
}

void AEBO::Backward(int speed){
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  analogWrite(3,speed);
  analogWrite(11,speed);
}

void AEBO::Left(int speed){
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  analogWrite(3,speed);
  analogWrite(11,speed);
}

void AEBO::Right(int speed){
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  analogWrite(3,speed);
  analogWrite(11,speed);
}

void AEBO::StopRobot(){
  analogWrite(3,0);
  analogWrite(11,0);
}

float AEBO::distance(int trigPin, int echoPin){
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  float duration = pulseIn(echoPin,HIGH);
  float d = 0.034*duration/2;

  return d;
}

//LCD functions



#define printIIC(args)	Wire.write(args)
inline size_t AEBO::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

void AEBO::LCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows){
  _Addr = lcd_Addr;
  _cols = lcd_cols;
  _rows = lcd_rows;
  _backlightval = LCD_NOBACKLIGHT;
  Wire.begin();
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(_cols, _rows);
}

void AEBO::begin(uint8_t cols, uint8_t lines, uint8_t dotsize){
  if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	if ((dotsize != 0) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay(50); 
  
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	delay(1000);

  	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	  // we start in 8bit mode, try to set 4 bit mode
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // second try
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // third go!
   write4bits(0x03 << 4); 
   delayMicroseconds(150);
   
   // finally, set to 4-bit interface
   write4bits(0x02 << 4); 


	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);  
	
	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	
	// clear it off
	LCD_clear();
	
	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);
	
	command(LCD_RETURNHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!

	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void AEBO::command(uint8_t value) {
	send(value, 0);
}

void AEBO::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}


void AEBO::LCD_clear(){
  command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void AEBO:: LCD_setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;    // we count rows starting w/0
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void AEBO::LCD_backlight(){
  _backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}

void AEBO::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
       write4bits((highnib)|mode);
	write4bits((lownib)|mode); 
}

void AEBO::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void AEBO::expanderWrite(uint8_t _data){                                        
	Wire.beginTransmission(_Addr);
	printIIC((int)(_data) | _backlightval);
	Wire.endTransmission();   
}

void AEBO::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	delayMicroseconds(1);		// enable pulse must be >450ns
	
	expanderWrite(_data & ~En);	// En low
	delayMicroseconds(50);		// commands need > 37us to settle
} 
void AEBO::LCD_print(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed 
	print(c);
}



