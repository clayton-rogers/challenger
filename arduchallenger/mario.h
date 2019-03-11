#ifndef MARIO_H
#define MARIO_H

#include "pitches.h"

// notes in the melody:
const int melody[] PROGMEM = {
	//NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4

	NOTE_E5, NOTE_E5, 0, NOTE_E5,
	0, NOTE_C5, NOTE_E5, 0,
	NOTE_G5, 0, 0,  0,
	NOTE_G4, 0, 0, 0,

	NOTE_C5, 0, 0, NOTE_G4,
	0, 0, NOTE_E4, 0,
	0, NOTE_A4, 0, NOTE_B4,
	0, NOTE_AS4, NOTE_A4, 0,

	NOTE_G4, NOTE_E5, NOTE_G5,
	NOTE_A5, 0, NOTE_F5, NOTE_G5,
	0, NOTE_E5, 0,NOTE_C5,
	NOTE_D5, NOTE_B4, 0, 0,

	NOTE_C5, 0, 0, NOTE_G4,
	0, 0, NOTE_E4, 0,
	0, NOTE_A4, 0, NOTE_B4,
	0, NOTE_AS4, NOTE_A4, 0,

	NOTE_G4, NOTE_E5, NOTE_G5,
	NOTE_A5, 0, NOTE_F5, NOTE_G5,
	0, NOTE_E5, 0,NOTE_C5,
	NOTE_D5, NOTE_B4, 0, 0

//NOTE_A6,NOTE_FS6,NOTE_G6,NOTE_A6,NOTE_FS6,NOTE_G6,NOTE_A6,NOTE_A5,NOTE_B5,NOTE_CS6,NOTE_D6,NOTE_E6,NOTE_FS6,NOTE_G6,NOTE_FS6,NOTE_D6,NOTE_E6,NOTE_FS6,NOTE_FS5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_FS5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_FS5,NOTE_E5,NOTE_FS5,NOTE_E5,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_G5,NOTE_B5,NOTE_A5,NOTE_B5,NOTE_CS6,NOTE_D6,NOTE_A5,NOTE_B5,NOTE_CS6,NOTE_D6,NOTE_E6,NOTE_FS6,NOTE_G6,NOTE_A6
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
const int noteDurations[] PROGMEM = {
	//4, 8, 8, 4, 4, 4, 4, 4

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

//8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16
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