#include "bombilla.h"
#include <stdio.h>

/**********************************************
Funciones que comprueban las entradas
***********************************************/
static int input_condition_func_encendido(fsm_t* fsm);
static int input_condition_func_apagado(fsm_t* fsm);


/**********************************************
Funciones que ejecutan las salidas
***********************************************/
static void output_func_encendido(fsm_t* fsm);
static void output_func_apagado(fsm_t* fsm);


fsm_trans_t bombilla_transition_table[] = {
		{APAGADO, input_condition_func_encendido,ENCENDIDO,output_func_encendido},
		{ENCENDIDO,input_condition_func_apagado,APAGADO,output_func_apagado},
		{-1, NULL, -1, NULL },
};

static int input_condition_func_encendido(fsm_t* fsm)
{
	bombilla_fsm_t* bombilla = (bombilla_fsm_t*)fsm; //Casteamos porque sabemos que el FSM está dentro del tipo bombilla_fsm_t
	if (bombilla->interruptor_flag == 1) { //Comprobamos interruptor encendido
		return 1;
	}
	return 0;
}

static int input_condition_func_apagado(fsm_t* fsm)
{
	bombilla_fsm_t* bombilla = (bombilla_fsm_t*)fsm; //Casteamos porque sabemos que el FSM está dentro del tipo bombilla_fsm_t
	if (bombilla->interruptor_flag == 0) { //Comprobamos interruptor apagado
		return 1;
	}
	return 0;
}

void output_func_encendido(fsm_t* fsm)
{
	printf("Se ha encendido la bombilla  \n"); // En un MCU escribiriamos un 0 en el pin correspondiente
}

void output_func_apagado(fsm_t* fsm)
{
	printf("Se ha apagado la bombilla  \n"); // En un MCU escribiriamos un 1 en el pin correspondiente 
}

bombilla_fsm_t* new_bombilla_fsm(fsm_trans_t* bombilla_transition_table)
{
	bombilla_fsm_t* bombilla = (bombilla_fsm_t*)malloc(sizeof(bombilla_fsm_t));
	bombilla->fsm.tt = bombilla_transition_table;
	bombilla->fsm.current_state = 1; // Por defecto Apagado
	bombilla->interruptor_flag = 0; //Inicializamos a 0 que es como tiene que estar en apagado
	return bombilla;
}

void delete_bombilla_fsm(bombilla_fsm_t* bombilla_fsm)
{
	free(bombilla_fsm);
}

void activa_interruptor(fsm_t* fsm) {
	bombilla_fsm_t* bombilla = (bombilla_fsm_t*)fsm; //Casteamos porque sabemos que el FSM está dentro del tipo bombilla_fsm_t
	bombilla->interruptor_flag = 1;
	printf("Interruptor encendido \n");
}

void apaga_interruptor(fsm_t* fsm) {
	bombilla_fsm_t* bombilla = (bombilla_fsm_t*)fsm; //Casteamos porque sabemos que el FSM está dentro del tipo bombilla_fsm_t
	bombilla->interruptor_flag = 0;
	printf("Interruptor apagado \n");
}
