#include "fsm.h"

typedef enum fsm_state {
	ENCENDIDO = 0,
	APAGADO = 1,
}bombilla_fsm_state_t;

typedef struct dron_fsm_ {
	fsm_t fsm;				//Herencia
	int interruptor_flag;		//Flags necesarios 
}bombilla_fsm_t;


/**********************************************
Funciones de inicialización y destruccion
***********************************************/
bombilla_fsm_t* new_bombilla_fsm(fsm_trans_t* bombilla_transition_table);
void delete_bombilla_fsm(bombilla_fsm_t* bombilla_fsm);
/**********************************************
Funciones de interacción
***********************************************/
void activa_interruptor(fsm_t* fsm);
void apaga_interruptor(fsm_t* fsm);