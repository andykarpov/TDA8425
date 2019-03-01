/*
 * TDA8425.h
 */

#ifndef _TDA8425_H_
#define _TDA8425_H_

#include <Arduino.h>

class TDA8425 {

	private:
		virtual void write(const byte subaddr, const byte value);

	public:
		TDA8425();
		virtual void begin(void);
		virtual void setMute(const bool mute);
		virtual void setVolume(const int left, const int right);
		virtual void setBassTreble(const int bass,const int treble);
};

#endif  // _TDA8425_H_
