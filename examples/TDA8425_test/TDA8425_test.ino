#include <Wire.h>
#include <TDA8425.h>

TDA8425 audio;

byte ch = 0;

void setup() {
   Serial.begin(115200);
   Serial.println("TDA8425 test suite");
   audio.begin();
   Serial.println("setVolume(0,0)");
   audio.setVolume(0, 0);
   delay(500);
   Serial.println("setBassTreble(50,50)");
   audio.setBassTreble(50,50);
   delay(500);
   Serial.println("setMuteChannel(false, 0)");
   audio.setMuteChannel(false, 0);
   delay(500);
}

void loop() {
  for (int i=0; i<=100; i++) {
    Serial.print("setVolume("); Serial.print(i); Serial.print(","); Serial.print(i); Serial.println(")");
    audio.setVolume(i, i);
    delay(50);
  }

  for (int i=100; i>=0; i--) {
    Serial.print("setVolume("); Serial.print(i); Serial.print(","); Serial.print(i); Serial.println(")");
    audio.setVolume(i, i);
    delay(50);
  }

  ch = (ch==0) ? 1 : 0;
  Serial.print("setMuteChannel(false,"); Serial.print(ch); Serial.println(")");
  audio.setMuteChannel(false, ch);
  delay(500);
  
}
