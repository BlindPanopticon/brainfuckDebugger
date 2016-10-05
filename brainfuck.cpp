#include "brainfuck.h"

brainfuck::brainfuck(){
}
brainfuck::~brainfuck(){
	delete[] memStack;
	delete[] loopStack;
}

void brainfuck::dumpStackMemory(){
	printf("\nMemory Stack Values");
        for( int x = 0; x < memMax; x++){
                if(x%10 == 0){
                        printf("\n\t[%i]\t:\t", x);
                }
                printf("[%i]\t", memStack[x]);
        }
        printf("\n");
}
void brainfuck::dumpStackLoop(){
	printf("\nLoop Stack Values");
        for( int x = 0; x < loopMax; x++){
                if(x%10 == 0){
                        printf("\n\t[%i]\t:\t", x);
                }
                printf("[%i]\t", loopStack[x]);
        }
        printf("\n");
}

void brainfuck::initMemStack(unsigned int memSize){
        memStack = new (nothrow) char [memSize];
        memoryPointer = 0;
	memMax = memSize;
        for(int x = 0; x < memMax; x++) memStack[x] = 0;
}
void brainfuck::initLoopStack(unsigned int loopSize){
        loopStack = new (nothrow) unsigned int [loopSize];
        loopPointer = 0;
        loopMax = loopSize;
        for(int x = 0; x < loopMax; x++) loopStack[x] = 0;
}

void brainfuck::loadProgram(string inputProgram){
	program = inputProgram;

        for(int x = 0; x < 8; x++) commandCount[x] = 0;
	
	for(int x = 0; x < program.size(); x++){
                switch( program.at(x) ) {
                        case '+':
                                ++commandCount[0];
                                break;
                        case '-':
                                ++commandCount[1];
                                break;
                        case '>':
                                ++commandCount[2];
                                break;
                        case '<':
                                ++commandCount[3];
                                break;
                        case '.':
                                ++commandCount[4];
                                break;
                        case ',':
                                ++commandCount[5];
                                break;
                        case '[':
                                ++commandCount[6];
                                break;
                        case ']':
                                ++commandCount[7];
                                break;
                        default:
			        break;
		}
	}
}

void brainfuck::programStatistics(){
	const char commands[] = {'+','-','>','<','.',',','[',']'};

	printf("\nProgram Statistics\n");
        	printf("\tProgram Instructions\n");
                	printf("\t\tProgram Cycles:\t%i\n", programCycles);
                        printf("\t\tProgram Length:\t%i\n", program.size());
                printf("\tMemory Stack\n");
                        printf("\t\tCurrent Total:\t%i\n", 1 + commandInstance[2] - commandInstance[3]);
                printf("\tCommand Counts\n");
                        printf("\t\tType\tInstructions\tInstances\n");
                                for(int x = 0; x < 8; x++){
                                        printf("\t\t%c\t%i\t\t%i\n", commands[x], commandCount[x], commandInstance[x]);
				}
}
void brainfuck::programValues(){
	printf("\nProgram Values\n");
		printf("\tProgram Counter:\t%i\n", programCounter);
		printf("\tProgram Cycles:\t\t%i\n", programCycles);
		printf("\tMemory Pointer:\t\t%i\n", memoryPointer);
		printf("\tMemory Value:\t\t%i\n", memStack[memoryPointer]);
		printf("\tLoop Pointer:\t\t%i\n", loopPointer);
		printf("\tLoop Value:\t\t%i\n", loopStack[loopPointer]);
}

void brainfuck::runReset(){
	programCounter = 0;
	programCycles = 0;

	loopPointer = 0;
	for(int x = 0; x < loopMax; x++) loopStack[x] = 0;

	memoryPointer = 0;
	for(int x = 0; x < memMax; x++) memStack[x] = 0;
	
        for(int x = 0; x < 8; x++) commandInstance[x] = 0;
}
void brainfuck::runSingleStep(){
	switch( program.at(programCounter) ){
		case '+':
			commandInc();
			break;
		case '-':
                        commandDec();
                        break;
		case '>':
                        commandShr();
                        break;
		case '<':
                        commandShl();
                        break;
		case '.':
                        commandOut();
                        break;
		case ',':
                        commandInt();
                        break;
		case '[':
                        commandStart();
                        break;
		case ']':
                        commandStop();
                        break;
		case 'L':
                        dumpStackLoop();
                        --programCycles;
			break;
		case 'M':
                        dumpStackMemory();
                        --programCycles;
			break;
		case 'V':
                        programValues();
                        --programCycles;
			break;
		default:
			--programCycles;
                        break;
	}
	++programCounter;
	++programCycles;
}
void brainfuck::runContinue(){
	while(programCounter < program.size()){
		runSingleStep();
	}
}

void brainfuck::commandInc(){
	++memStack[memoryPointer];
	++commandInstance[0];
}
void brainfuck::commandDec(){
	--memStack[memoryPointer];
	++commandInstance[1];
}
void brainfuck::commandShr(){
	++memoryPointer;
	++commandInstance[2];
}
void brainfuck::commandShl(){
	--memoryPointer;
	++commandInstance[3];
}
void brainfuck::commandInt(){
	printf("\ninput request:\t\t");
	memStack[memoryPointer] = getchar();
	++commandInstance[5];
}
void brainfuck::commandOut(){
	printf("\noutput received:\t%c\n", memStack[memoryPointer]);
	++commandInstance[4];
}
void brainfuck::commandStart(){
	if(memStack[memoryPointer] == 0){
		//skip this level of loop
        	unsigned int temp = 0;
        	for(programCounter; programCounter < program.size(); programCounter++){
			if(program.at(programCounter) = '['){
				//new level loop detected
				++temp;
			}else if(program.at(programCounter) = ']'){
				//current level loop closed
				--temp;
				if(temp == 0){
					//have made it to the current level loop end
                                        break;
                                }
                        }
                }
        }else{
		//now into a new loop
                loopStack[loopPointer] = programCounter;
                ++loopPointer;
        }
	++commandInstance[6];
}
void brainfuck::commandStop(){
        if(memStack[memoryPointer] != 0){
		//still in loop, goto level's loop beginning
                programCounter = loopStack[loopPointer - 1];
        }else{
		//break from loop
                --loopPointer;
        }
	++commandInstance[7];
}
