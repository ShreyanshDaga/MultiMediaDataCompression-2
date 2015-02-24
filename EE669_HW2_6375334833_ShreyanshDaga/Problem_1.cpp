#include "HW_2.h"
#include "FileStats.h"
#include "QMEnc.h"

void Problem_1_B()
{	
	// File Statistics for Text file
	FileStats fText("text.dat");
	QMEnc enc;

	enc.LoadQMTable("QM_state_transition_table.txt");
	enc.Encode("text.dat");

	/*FileStats fImage("image.dat");
	FileStats fBin("binary.dat");
	FileStats fAudio("audio.dat");*/
}