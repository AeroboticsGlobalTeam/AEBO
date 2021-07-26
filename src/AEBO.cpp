/*
 * AEBO.cpp - Library for AEBO robot
 * Created by Lokesh Kode, July 26,2021.
 * Released into public domain
 */

 #include "Arduino.h"
 #include "AEBO.h"

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
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
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
