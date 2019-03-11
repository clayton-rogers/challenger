#ifndef MARIO_H
#define MARIO_H

#include "pitches.h"

// notes in the melody:
const int melody[] PROGMEM = {

// 1
	NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,
	NOTE_G5, 0, 0,  0, NOTE_G4, 0, 0, 0,
	NOTE_C5, 0, 0, NOTE_G4, 0, 0, NOTE_E4, 0,
	0, NOTE_A4, 0, NOTE_B4,	0, NOTE_AS4, NOTE_A4, 0,

// 5
	NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, 0, NOTE_F5, NOTE_G5,
	0, NOTE_E5, 0,NOTE_C5, NOTE_D5, NOTE_B4, 0, 0,
	NOTE_C5, 0, 0, NOTE_G4,	0, 0, NOTE_E4, 0,
	0, NOTE_A4, 0, NOTE_B4,	0, NOTE_AS4, NOTE_A4, 0,

// 9
	NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, 0, NOTE_F5, NOTE_G5,
	0, NOTE_E5, 0,NOTE_C5, NOTE_D5, NOTE_B4, 0, 0,
	0, 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
	0, NOTE_GS4, NOTE_A4, NOTE_C5, 0, NOTE_A4, NOTE_C5, NOTE_D5,

// 13
	0, 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
	0, NOTE_C6, 0 , NOTE_C6, NOTE_C6, 0, 0, 0,
	0, 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
	0, NOTE_GS4, NOTE_A4, NOTE_C5, 0, NOTE_A4, NOTE_C5, NOTE_D5,
	0, 0, NOTE_DS5, 0, 0, NOTE_D5, 0, 0,

// 18
	NOTE_C5, 0, 0, 0, 0, 0, 0, 0,
	0, 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
	0, NOTE_GS4, NOTE_A4, NOTE_C5, 0, NOTE_A4, NOTE_C5, NOTE_D5,
	0, 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
	0, NOTE_C6, 0 , NOTE_C6, NOTE_C6, 0, 0, 0,

// 23
	0, 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
	0, NOTE_GS4, NOTE_A4, NOTE_C5, 0, NOTE_A4, NOTE_C5, NOTE_D5,
	0, 0, NOTE_DS5, 0, 0, NOTE_D5, 0, 0,
	NOTE_C5, 0, 0, 0, 0, 0, 0, 0,
	NOTE_C5, NOTE_C5, 0, NOTE_C5, 0, NOTE_C5, NOTE_D5, 0,

// 28
	NOTE_E5, NOTE_C5, 0, NOTE_A4, NOTE_G4, 0, 0, 0,
	NOTE_C5, NOTE_C5, 0, NOTE_C5, 0, NOTE_C5, NOTE_D5, NOTE_E5,
	0, 0, 0, 0,
	NOTE_C5, NOTE_C5, 0, NOTE_C5, 0, NOTE_C5, NOTE_D5, 0,
	NOTE_E5, NOTE_C5, 0, NOTE_A4, NOTE_G4, 0, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,

// 34
	NOTE_G5, 0, 0, 0, NOTE_G4, 0, 0, 0,
	NOTE_C5, 0, 0, NOTE_G4, 0, 0, NOTE_E4, 0,
	0, NOTE_A4, 0, NOTE_B4, 0, NOTE_AS3, NOTE_A4, 0,
	NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, 0, NOTE_F5, NOTE_G5,
	0, NOTE_E5, 0,NOTE_C5, NOTE_D5, NOTE_B4, 0, 0,

// 39
	NOTE_C5, 0, 0, NOTE_G4, 0, 0, NOTE_E4, 0,
	0, NOTE_A4, 0, NOTE_B4, 0, NOTE_AS3, NOTE_A4, 0,
	NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, 0, NOTE_F5, NOTE_G5,
	0, NOTE_E5, 0,NOTE_C5, NOTE_D5, NOTE_B4, 0, 0,

// 43
	NOTE_E5, NOTE_C5, 0, NOTE_G4, 0, 0, NOTE_GS4, 0,
	NOTE_A4, NOTE_F5, 0, NOTE_F5, NOTE_A4, 0, 0, 0,
	NOTE_B4, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
	NOTE_E5, NOTE_C5, 0, NOTE_A4, NOTE_G4, 0, 0, 0,

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
const int noteDurations[] PROGMEM = {

// 1
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 5
	9, 9, 9, 12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 9
	9, 9, 9, 12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 13
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 18
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 23
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 28
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	6, 6, 6, 6,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 34
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	9, 9, 9, 12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 39
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	9, 9, 9, 12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,

// 43
	12, 12, 12, 12,	12, 12, 12, 12,
	12, 12, 12, 12,	12, 12, 12, 12,
	9, 9, 9, 9, 9, 9,
	12, 12, 12, 12,	12, 12, 12, 12,

};

static_assert(sizeof(melody) == sizeof(noteDurations), "Melody and note lengths should be equal");

const int number_of_notes = sizeof(melody)/sizeof(melody[0]);

void update_mario(int pin) {
	static int thisNote = 0;
	static unsigned long next_time = millis();

	unsigned long current_time = millis();

	// If we have not yet hit the designated time, do nothing
	if (current_time < next_time) {
		return;
	}

	static bool currently_playing = false;

	if (!currently_playing) {
		// to calculate the note duration, take one second divided by the note type.
		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		const int noteBeats = pgm_read_word_near(noteDurations + thisNote);
		const int notePitch = pgm_read_word_near(melody + thisNote);

		int noteDuration = 1000 / noteBeats;
		tone(pin, notePitch, noteDuration);

		next_time = current_time + noteDuration;

		currently_playing = true;
	} else {
		noTone(pin); // Probably not required? Docs say no effect if no tone is being played.

		// to calculate the note duration, take one second divided by the note type.
		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		const int noteBeats = pgm_read_word_near(noteDurations + thisNote);
		int noteDuration = 1000 / noteBeats;
		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		int pauseBetweenNotes = noteDuration * 0.3;//1.30;

		next_time = current_time + pauseBetweenNotes;

		++thisNote;
		if (thisNote == number_of_notes) {
			thisNote = 0;
		}
		currently_playing = false;
	}
}

#endif // MARIO_H
