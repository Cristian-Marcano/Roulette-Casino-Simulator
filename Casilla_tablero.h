#include<iostream>
#include<graphics.h>

using namespace std;

class Board_box{
	private:
		string name;
		int x,y,width,height,nro;
	public:
		int fichas_users = 0;
		Board_box(int nro,int x,int y,int width,int height){
			this->nro = nro;
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		Board_box(string name,int x,int y,int width,int height){
			this->name = name;
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		void print_box_nro(); // imprimir la casilla si es un solo nro
		void print_box_others(); // imprimir casillas de 1:1 o 2:1
		bool click(int,int); // retornar true si se clickeo la casilla
		void show_coins(); // mostrar las fichas
		bool find_black(int); // encontrar los nros que son negros
		int get_amount_win(int);
		int get_amount_col(int,int);
		int get_nro(); // obtener nro de la casilla
};

void Board_box::print_box_nro(){
	int center_board_box_X = this->x + (this->width/2);
	int y = this->y + (this->height/2);
	rectangle(this->x,this->y,(this->x+this->width),(this->y+this->height));
	char str[3];
	itoa(this->nro,str,10);
	outtextxy(center_board_box_X,y+5,str);
	if(this->find_black(this->nro)) setfillstyle(SOLID_FILL,BLACK);
	else setfillstyle(SOLID_FILL,RED);
	floodfill(this->x+1,this->y+1,WHITE);
	if(this->fichas_users>0) this->show_coins();
}

void Board_box::print_box_others(){ // imprimir las casillas que no son numericas
	int center_board_box_X = this->x + (this->width/2);
	int y = this->y + (this->height/2);
	rectangle(this->x,this->y,(this->x+this->width),(this->y+this->height));
	if(this->name.compare("N")==0 || this->name.compare("R")==0){
		rectangle(this->x+(this->width*0.1),this->y+(this->height*0.1),this->x+(this->width*0.1)+(this->width*0.8),this->y+(this->height*0.1)+(this->height*0.8));
		(this->name.compare("N")==0) ? setfillstyle(SOLID_FILL,BLACK) : setfillstyle(SOLID_FILL,RED);
		floodfill(this->x+(this->width*0.1)+1,this->y+(this->height*0.1)+1,WHITE);
	}
	else{
		char str[this->name.size()];
		strcpy(str,this->name.c_str());
		if(this->name.compare("2:1")!=0){
			settextstyle(10,1,1);
			outtextxy(center_board_box_X+5,y,str);
		}
		else outtextxy(center_board_box_X,y+5,str);
		settextstyle(10,0,1);
	}
	setfillstyle(SOLID_FILL,COLOR(85,85,85));
	floodfill(this->x+1,this->y+1,WHITE);
	if(this->fichas_users>0) this->show_coins();
}

void Board_box::show_coins(){// al imprimir la casilla se muestra las fichas en el tablero
	char str[5];
	int val = this->fichas_users;
	itoa(val,str,10);
	int center_coin_x = this->x + ((this->width>this->height) ? this->width*0.7 : this->width*0.5),center_coin_y = this->y + ((this->height>this->width) ? this->height*0.6 : this->height*0.5);
	int radius = 12;
	circle(center_coin_x,center_coin_y,radius);
	settextstyle(11,0,1);
	outtextxy(center_coin_x,center_coin_y+5,str);
	settextstyle(10,0,1);
	setfillstyle(SOLID_FILL,COLOR(184,134,11));
	floodfill(center_coin_x,center_coin_y+5,WHITE);
}

bool Board_box::find_black(int nro){
	const int numbers_negros[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
	for(int i: numbers_negros) if(i==nro) return true; 
	return false;
}

bool Board_box::click(int x,int y){
	return ((this->x<=x && (this->x+this->width)>=x) && (this->y<=y && (this->y+this->height)>=y)) ? true : false;
}

int Board_box::get_amount_win(int nro){ // esta funcion es para multiplicar lo apostado por la ganancia en caso de que si se acierte
	if(this->name.compare("18-1")==0 && nro>=1 && nro<=18 && this->fichas_users>0){
		return this->fichas_users*2;
	} else if(this->name.compare("36-19")==0 && nro>=19 && nro<=36 && this->fichas_users>0){
		return this->fichas_users*2;
	} else if(this->name.compare("Par")==0 && nro!=0 && nro%2==0 && this->fichas_users>0){
		return this->fichas_users*2;
	} else if(this->name.compare("Impar")==0 && nro!=0 && nro%2!=0 && this->fichas_users>0){
		return this->fichas_users*2;
	} else if(this->name.compare("N")==0 && this->find_black(nro) && this->fichas_users>0){
		return this->fichas_users*2;
	} else if(this->name.compare("R")==0 && !this->find_black(nro) && nro!=0 && this->fichas_users>0){
		return this->fichas_users*2;
	} else if(this->name.compare("12-1")==0 && nro>=1 && nro<=12 && this->fichas_users>0){
		return this->fichas_users*3;
	} else if(this->name.compare("24-13")==0 && nro>=13 && nro<=24 && this->fichas_users>0){
		return this->fichas_users*3;
	} else if(this->name.compare("36-25")==0 && nro>=25 && nro<=36 && this->fichas_users>0){
		return this->fichas_users*3;
	}
	return 0;
}

int Board_box::get_amount_col(int nro,int i){ // esta funcion es para multiplicar lo apostado por la ganancia en caso de que si se acierte
	if(i==0){
		const int numbers_col_1[12] = {1,4,7,10,13,16,19,22,25,28,31,34};
		for(int x: numbers_col_1) if(x==nro) return this->fichas_users*3;
	} else if(i==1){
		const int numbers_col_2[12] = {2,5,8,11,14,17,20,23,26,29,32,35};
		for(int x: numbers_col_2) if(x==nro) return this->fichas_users*3;
	} else{
		const int numbers_col_3[12] = {3,6,9,12,15,18,21,24,27,30,33,36};
		for(int x: numbers_col_3) if(x==nro) return this->fichas_users*3;
	}
	return 0;
}

int Board_box::get_nro(){
	return this->nro;
}