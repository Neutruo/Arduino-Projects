#include <stdio.h>
#include <DS1302.h>

const int kCePin   = 12;  // Chip Enable
const int kIoPin   = 3;  // Input/Output
const int kSclkPin =11;  // Serial Clock

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);
Time t = rtc.time();

void setup() {
  Serial.begin(9600);     
  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(false);
  rtc.halt(false);
  // Make a new time object to set the date and time.
  // Year, Month, Date  Hour Min Sec 

 // set the latest time here
 // Time t(2023, 7, 30, 13, 55, 10, Time::kSunday);

 // Set the time and date on the chip.
   //rtc.time(t);
}

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sun";
    case Time::kMonday: return "Mon";
    case Time::kTuesday: return "Tue";
    case Time::kWednesday: return "Wed";
    case Time::kThursday: return "Thu";
    case Time::kFriday: return "Fri";
    case Time::kSaturday: return "Sat";
  }
  return "(unknown day)";
}

void printTime() {
 Time t = rtc.time();
  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  Serial.println(buf);
}

void loop() {
  printTime();
}
