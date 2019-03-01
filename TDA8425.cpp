#include <stdio.h>
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <Wire.h>
#include "TDA8425.h"

#define TDA8425_ADDR	   0x82  /* i2c address */
#define TDA8425_VL         0x00  /* volume left */   
#define TDA8425_VR         0x01  /* volume right */   
#define TDA8425_BA         0x02  /* bass */   
#define TDA8425_TR         0x03  /* treble */   
#define TDA8425_S1         0x08  /* switch functions */   
                                 /* values for those registers: */   
#define TDA8425_S1_OFF     0xEE  /* audio off (mute on) */   
#define TDA8425_S1_ON      0xCE  /* audio on (mute off) - "linear stereo" mode */   
   
void TDA8425::Write(const int Subaddr, const int Value) {
	Wire.beginTransmission(TDA8425_ADDR);
	Wire.write(Subaddr);
	Wire.write(Value);
	Wire.endTransmission();
}

void TDA8425::Restart()   
{   
    Write(TDA8425_VL, 0x3C |0xC0);   
    Write(TDA8425_VR, 0x3C |0xC0);   
    Write(TDA8425_BA, 0x6  |0xF0);   
    Write(TDA8425_TR, 0x6  |0xF0);   
    Write(TDA8425_S1, TDA8425_S1_OFF); /* mute */   
}   
   
TDA8425::TDA8425() {
	Wire.begin();
    TDA8425::Restart();   
}   
   
void TDA8425::SetMute(int Mute)
{
    Write(TDA8425_S1, (Mute) ? TDA8425_S1_ON : TDA8425_S1_OFF);  
}   
   
void TDA8425::SetVolume(const int Left,const int Right) /* 0x3C = 0dB */   
{   
    int AdjLeft  = (Left /546) + 0x3C;   
    int AdjRight = (Right/546) + 0x3C;   
    AdjLeft = (AdjLeft > 0x3F) ? 0x3F: AdjLeft;   
    AdjRight = (AdjRight > 0x3F) ? 0x3F: AdjRight;   
   
    Write(TDA8425_VL, AdjLeft  | 0xC0);   
    Write(TDA8425_VR, AdjRight | 0xC0);   
}    
   
void TDA8425::SetBassTreble(const int Bass,const int Treble)    
{   
    int AdjBass   = (Bass   / 3641) + 0x6;   
    int AdjTreble = (Treble / 3641) + 0x6;   
    AdjBass   = (AdjBass   < 0) ? 0: AdjBass;   
    AdjTreble = (AdjTreble < 0) ? 0: AdjTreble;   
   
    Write(TDA8425_BA, AdjBass   |0xF0);    
    Write(TDA8425_TR, AdjTreble |0xF0);    
}
