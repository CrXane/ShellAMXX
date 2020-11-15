#include "amxxmodule.h"
#include "pstream.h"
#include <string>
#include <iostream>

using namespace std;

AMX_NATIVE_INFO Native[] = { "shell_exec" };

void OnAmxxAttach(){
	MF_AddNatives(Native);
}

static cell AMX_NATIVE_CALL shell_exec(AMX* amx, cell* params){
	char* cmd = MF_FormatAmxString(amx, params, 1, 0);
	redi::ipstream proc(cmd, redi::pstreams::pstdout | redi::pstreams::pstderr);
	string line;
	while (std::getline(proc.out(), line))
		MF_PrintSrvConsole(line.c_str());
	if (proc.eof() && proc.fail())
		proc.clear();
	while (std::getline(proc.err(), line))
		MF_PrintSrvConsole(line.c_str());
	return 0;
}
