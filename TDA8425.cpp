#include <stdio.h>
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <Wire.h>
#include "TDA8425.h"

#define TDA8425_ADDR	   0x41  /* i2c address */
#define TDA8425_VL         0x00  /* volume left */
#define TDA8425_VR         0x01  /* volume right */
#define TDA8425_BA         0x02  /* bass */
#define TDA8425_TR         0x03  /* treble */
#define TDA8425_S1         0x08  /* switch functions */
                                 /* values for those registers: */
#define TDA8425_S1_OFF     0xEE  /* audio off (mute on) */
#define TDA8425_S1_ON      0xCE  /* audio on (mute off) - "linear stereo" mode */

TDA8425::TDA8425()
{
}

void TDA8425::begin()
{
    Wire.begin();
    write(TDA8425_VL, 0x3C |0xC0);
    write(TDA8425_VR, 0x3C |0xC0);
    write(TDA8425_BA, 0x6  |0xF0);
    write(TDA8425_TR, 0x6  |0xF0);
    write(TDA8425_S1, TDA8425_S1_OFF); /* mute */
}

void TDA8425::write(byte subaddr, byte value)
{
    Wire.beginTransmission(TDA8425_ADDR);
    Wire.write(subaddr);
    Wire.write(value);
    Wire.endTransmission();
}


void TDA8425::setMuteChannel(bool mute, const byte channel)
{
    byte c = constrain(channel, 0, 1);
    write(TDA8425_S1, (mute) ? TDA8425_S1_OFF + c : TDA8425_S1_ON + c);
}

void TDA8425::setVolume(const int left, const int right) /* 0x3C = 0dB */
{
    byte l = map(left, 0, 100, 16, 63);
    byte r = map(right, 0, 100, 16, 63);

    l = constrain(l, 16, 63); // TODO: check manual, 28 - 63 ?
    r = constrain(l, 16, 63);

    write(TDA8425_VL, l  | 0xC0);
    write(TDA8425_VR, r | 0xC0);
}

void TDA8425::setBassTreble(const int bass, const int treble)
{
    byte b = map(bass, 0, 100, 2, 11); // TODO: check manual 0..15 ?
    byte t = map(treble, 0, 100, 2, 10); // TODO: check manual 0...15 ?

    b = constrain(b, 2, 11);
    t = constrain(t, 2, 10);

    write(TDA8425_BA, b | 0xF0);
    write(TDA8425_TR, t | 0xF0);
}
