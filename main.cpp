#include "brainfuck.h"
#include <iostream>
	using namespace std; 

int main(){
	brainfuck bf;
	int memSize, loopSize;
	string program;

	cout << "\nEnter Memory Stack Size:\t";
	cin >> memSize;
	bf.initMemStack((unsigned)memSize);

	cout << "\nEnter Loop Stack Size:\t\t";
	cin >> loopSize;
	bf.initLoopStack((unsigned)loopSize);

	cout << "\nEnter Brainfuck Program:\t";
	cin >> program;
	bf.loadProgram(program);

	bf.runReset();

	bf.dumpStackMemory();
	bf.dumpStackLoop();

	bf.programValues();

	bf.runContinue();

	bf.dumpStackMemory();
        bf.dumpStackLoop();

        bf.programValues();
	bf.programStatistics();

	return 0;
}
