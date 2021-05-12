#include "pitches.h"
void intro(int melody,int durations, int songLength);
// Two things need to be created: the array for the notes of the melody (in order)
// and the duration of each (think of it like sheet music in two parts)

// BOTH ARRAYS MUST BE THE SAME SIZE!

//--------------------------------------------------------1---------------------------------------------------
int melody1[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

int durations1[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

int songLength1 = sizeof(melody1)/sizeof(melody1[0]);
//-----------------------------------------------------------------------------------------------------------


//----------------------------------2 (PADDLE IZQUIERDO)-----------------------------------------------------
int melody2[] = {
   NOTE_E5,NOTE_C5
   //NOTE_E7,NOTE_C7  
};
   
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int durations2[] = {
2, 2
};

int songLength2 = sizeof(melody2)/sizeof(melody2[0]);
//-----------------------------------------------------------------------------------------------------------

//-------------------------------------3 (PADDLE DERCHO)-----------------------------------------------------
int melody3[] = {
   NOTE_E7,NOTE_C7  
};
   
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int durations3[] = {
2, 2
};

int songLength3 = sizeof(melody3)/sizeof(melody3[0]);


//-----------------------------------------------------------------------------------------------------------
//-------------------------------------3 (WIN)--------------------------------------------------------------
int melody4[] = { //using note c5 e5 a5 b4 g5
  NOTE_F4, NOTE_F4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_F4, NOTE_B3,
  NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_G4,
  NOTE_F4, NOTE_B3,
  NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_G4
};

// note durations: 8 = eighth note
int durations4[] = {
  4,4,4,4,4,4,4,4,4,4,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4
};
int songLength4 = sizeof(melody4)/sizeof(melody4[0]);
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------


void musica(int melody[],int durations[], int songLength) {
  // Iterate through both arrays
  // Notice how the iteration variable thisNote is created in the parenthesis
  // The for loop stops when it is equal to the size of the melody array
  for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(PC_4, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(PC_4);
  }
}
