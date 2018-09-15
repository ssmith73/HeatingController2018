/*
  DS3231: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;
int numSeconds;

struct ElapsedTime
{
  int elapsedMinutes;
  int elapsedSeconds;
  int elapsedHours;
};
struct ElapsedTime myTime;

void setup()
{
  Serial.begin(9600);

  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();
  numSeconds = 0;
  
    
  // Set sketch compiling time
  ///clock.setDateTime(__DATE__, __TIME__);
}

void loop()
{
  dt = clock.getDateTime();

  if(dt.minute >= 21 && dt.minute < 25)
    numSeconds++;

  if(dt.second == 0) 
  {
    myTime = CalculateElapsedTime(numSeconds);
    Serial.print("Elapsed Time "); 
      Serial.print(myTime.elapsedHours); Serial.print(":");
      Serial.print(myTime.elapsedMinutes); Serial.print(":"); 
      Serial.println(myTime.elapsedSeconds);
  }
    
  // For leading zero look to DS3231_dateformat example

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  delay(1000);
}

  ElapsedTime CalculateElapsedTime(int elapsedSeconds) 
  {
    struct ElapsedTime et;
    et.elapsedSeconds = elapsedSeconds%60;
    et.elapsedMinutes = elapsedSeconds/60;
    et.elapsedHours   = et.elapsedMinutes/60;
    return et;
  }



