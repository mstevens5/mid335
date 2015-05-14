//CMPS 335
//mid335.cpp
//
//
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>

#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4
#define NUM_OCTAVES 9
#define NUM_NOTES 12

typedef enum {
	C = 1,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
	END = B,
	HALF_STEPS_PER_OCTAVE = B 
} note_t;

double freq(note_t note, int octave_delta);


int main(int argc, char *argv[])
{
	note_t note;
	int octave_delta;
    float frequency = 0;
    ifstream inputFile;
    inputFile.open("inputFrequency");
    int outputNote = 0; 
    float tolerance = 0;
    char inputData[10];
    float diff = 0;
    int badElement = 0;

    int notesArray[NUM_OCTAVES][NUM_NOTES];    

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA>" << endl;
		return 0;
	}
    if (argc == 4){
        tolerance = atof(argv[3]);
    }

	//
	note = (note_t)(toupper(argv[1][0]) - 64);
	switch(toupper(argv[1][0])) {
		case 'A': note = A; break;
		case 'B': note = B; break;
		case 'C': note = C; break;
		case 'D': note = D; break;
		case 'E': note = E; break;
		case 'F': note = F; break;
	}
	//You may call your unit test here...

    if (note != (note_t)26){


	    if (note > END) {
		    cout << "Invalid note!" << endl;
		    return 1;
	    }
	    octave_delta = atoi(argv[2]);
	    cout << HALF_STEPS_PER_OCTAVE << endl;
	    cout << freq(note, octave_delta) << endl;
    }
    else{
        cout << "tolerance: " << tolerance << endl;
        cout << "freq function unit-test" << endl << endl;
        cout << "note octave value   diff     " << endl;
        cout << "---- ------ ------- ----------" << endl;
        for (int i = 0; i < NUM_OCTAVES; i++){
            for (int j = 0; j< NUM_NOTES; j++){
                outputNote = j + 1;
                frequency = freq((note_t) outputNote,i);
                cout << " " << setw(4) << to_string(outputNote) << "    " << i << "    "<< frequency;
                inputFile >> inputData;
                diff = fabs(atof(inputData) - frequency);
                cout << "  " << to_string(diff);
                if ( diff < tolerance){
                    cout << "      good" << endl;
                }
                else{
                    cout <<  "<---- bad" << endl;
                    badElement++;
                }

            }
        }
        cout << "bad element count: " << badElement << endl;
        cout << "unit test complete." << endl;
    }
    inputFile.close();
	return 0;
}

//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
	double freq;
	double factor;
	double a;
	int n;
	int octave = octave_delta - F0_octave;

	a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
	n = note - F0_note;
	freq = F0 * pow(a, (double)n);
	factor = pow(2.0, (double)octave);
	freq = freq * factor;
	return freq;
}

