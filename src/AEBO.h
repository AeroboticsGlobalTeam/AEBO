/*
 * Library for AEBO Robot 
 * Created by Lokesh Kode, July 26,2021.
 * Released into public domain
*/


#ifndef AEBO_H
#define AEBO_H

#include "Arduino.h"
#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit


class AEBO : public Print{

  public:
    AEBO();

    //Movement Functions
    void Forward(int speed);
    void Backward(int speed);
    void Left(int speed);
    void Right(int speed);
    void StopRobot();  

    //Distance Function
    float distance(int trigPin, int echoPin);

    //LCD functions

    void LCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
    void LCD_clear();
    void LCD_backlight();
    void LCD_setCursor(uint8_t, uint8_t);
    virtual size_t write(uint8_t);
    void LCD_print(const char c[]);

   private:

    int _trigpin;
    int _echopin;
    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
    void send(uint8_t, uint8_t);
    void write4bits(uint8_t);
    void expanderWrite(uint8_t);
    void pulseEnable(uint8_t);
    void display();
    void command(uint8_t);
    uint8_t _Addr;
    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
    uint8_t _numlines;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightval;
    
    
};

#endif
