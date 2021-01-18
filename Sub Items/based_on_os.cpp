#pragma once
#include "Precompiled_Headers.cpp"
short int check_os(){
    #ifdef _WIN32
	    return 0;
	#elif __linux__ || __unix__
	    return 1;
	#else
	    return 2;
	#endif
}
short int value = check_os();
void clr_console(){
	switch (value){
	case 0: system("cls");
		break;
	case 1: system("clear");
		break;
	default: cout<<"Error: Undefined OS";
		break;
	}
}
#ifdef _WIN32
	#include <windows.h>
#elif __linux__ || __unix__
	#include <unistd.h>
#endif
void Sleep_For(){
	#ifdef _WIN32
		Sleep(3 * 1000); // 3 is the no. of seconds to hold and 10^3 is the millisecond argument thaat Sleep takes
	#elif __linux__ || __unix__
		usleep(3 * 1000000); // 3 is the no. of seconds to hold and 10^6 is the microsecond argument thaat usleep takes
	#else
		cerr<< "Error: Undefined OS";
		exit(1);
	#endif
}