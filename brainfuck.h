#include <stdio.h>
#include <new>
#include <string>
	using namespace std;

class brainfuck {
	public:
		brainfuck();
		~brainfuck();

		void initMemStack(unsigned int);
		void initLoopStack(unsigned int);
		void loadProgram(string);

		void dumpStackMemory();
		void dumpStackLoop();

		void programStatistics();
		void programValues();

		void runReset();
		void runSingleStep();
		void runContinue();

	private:
		unsigned int * loopStack;
		char * memStack;
		
		unsigned int loopMax;
		unsigned int memMax;
		
		unsigned int loopPointer;
		unsigned int memoryPointer;

		string program;
		unsigned int programCounter;
		unsigned int programCycles;

		unsigned int commandCount[8];
		unsigned int commandInstance[8];

		void commandInc();
		void commandDec();
		void commandShr();
		void commandShl();
		void commandInt();
		void commandOut();
		void commandStart();
		void commandStop();
};
