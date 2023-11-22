#include<iostream>

using namespace std;

struct Pila{
	int id,nro_fichas=0;
	Pila *sig;
};

void insert_user(Pila *&casilla,int id){
	Pila *nuevo_user = new Pila();
	nuevo_user->id = id;
	nuevo_user->sig = casilla;
	casilla = nuevo_user;
}

bool verify_user(Pila *&casilla,int id){
	Pila *verify = casilla;
	while(verify!=NULL){
		if(verify->id) return true;
		verify = verify->sig;
	}
	return false;
}

void insert_coin(Pila *&casilla,int id){
	Pila *show = casilla;
	while(show!=NULL){
		if(show->id==id){
			show->nro_fichas++;
			break;
		}
		show = show->sig;
	}
}

void delete_coin(Pila *&casilla,int id){
	Pila *show = casilla;
	while(show!=NULL){
		if(show->id==id){
			if(show->nro_fichas>0) show->nro_fichas--;
			break;
		}
		show = show->sig;
	}
}

void delete_all_coins(Pila *&casilla,int id){
	Pila *show = casilla;
	while(show!=NULL){
		if(show->id==id){
			show->nro_fichas = 0;
			break;
		}
		show = show->sig;
	}
}

int get_nro_fichas(Pila *&casilla,int id){
	Pila *show = casilla;
	while(show!=NULL){
		if(show->id==id) break;
		show = show->sig;
	}
	return show->nro_fichas;
}

bool find_black(int nro){
	const int numbers_negros[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
	for(int i: numbers_negros) if(i==nro) return true; 
	return false;
}