#include <stdio.h>
#include "bombilla.h"
#include <conio.h>
#include <time.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(void* data);

#define CLK_MS 				100
#define MAX_TEST_TIME		100000000000000000


extern fsm_trans_t bombilla_transition_table[];

int main() {
	unsigned long long time = 0;	//Time count in ms
	fsm_t* fsm = (fsm_t*)new_bombilla_fsm(bombilla_transition_table);
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, fsm, 0, NULL);
	while (time < MAX_TEST_TIME) {
		fsm_fire(fsm);

		Sleep(CLK_MS);
		time += CLK_MS;
	}

	delete_bombilla_fsm((bombilla_fsm_t*)fsm);

	return 0;
}




DWORD WINAPI ThreadFunc(void* data) {
	static char c;
	fsm_t* fsm = (fsm_t*)data;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			if (c == 'a') {
				activa_interruptor(fsm);
			}
			else if (c == 's') {
				apaga_interruptor(fsm);
			}
			printf("%c\n", c);
		}
	}
	return 0;
}
