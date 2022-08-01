# AEBO
AEBO Arduino Library

This library is for Arduino IDE to simplify the functions for LCD, Movement and Ultrasonic sensor.

Please install the library by following these steps

- Open Arduino IDE and go to Tools -> Manage Libraries
- Search and install AEBO 

The library can be used in the following methods

## Printing to LCD 

```sh
#include<AEBO.h>

AEBO robot;

void setup() {
  // Initialising the LCD 
  robot.LCD(0x27,16,2);
  robot.LCD_backlight();
}

void loop() {

  robot.LCD_setCursor(0,0); //setting the cursor
  robot.print("hi");        // Printing to the LCD
  delay(1000);
  robot.LCD_clear();       // Clearing the LCD
}
```

## Movement Functions

```sh
#include<AEBO.h>

AEBO robot; //Initialising the library

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // The function takes input as speed which is 0-255

  robot.Forward(100);
  delay(100);

  robot.Backward(100);
  delay(100);

  robot.Left(100);
  delay(100);

  robot.Right(100);
  delay(100);

  robot.StopRobot();
  delay(100);

}
```

## Ultrasonic sensor Functions

```sh
#include<AEBO.h>


AEBO robot;

void setup() {
  // Using LCD to display the distance
  robot.LCD(0x27,16,2);
  robot.LCD_backlight();
   
}

void loop() {
  // put your main code here, to run repeatedly:

  float d = robot.distance(A1,A0); //this function takes input in form of triggerpin,echopin

  robot.LCD_setCursor(0,0);
  robot.print(d);           // printing the distance
  delay(100);
  robot.LCD_clear();
  
 
}
```
