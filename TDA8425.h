/*
 * TDA8425.h
 * defintions for TDA8425 audio processor.
 * Created by Andrey Karpov
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _TDA8425_H_
#define _TDA8425_H_

#include <Arduino.h>

class TDA8425 { 
 
	public: 
		TDA8425(); 
		virtual void Write(const int Subaddr, const int Value);
		virtual void SetMute(const int Mute) ; 
		virtual void SetVolume(const int Left,const int Right) /* 0 = Gain 1 */ ; 
		virtual void SetBassTreble(const int Bass,const int Treble)  ; 
 
		virtual bool IsVolumeAvailable()	{ return true; } 
		virtual bool IsBassTrebleAvailable(){ return true; } 
 
		// To support Hibernate mode 
		virtual void Restart( void ); 
 
}; 
 
#endif  // _TDA8425_H_
