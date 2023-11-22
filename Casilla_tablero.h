#include"Pila_casilla.h"
#include<graphics.h>

class Board_box{
	private:
		string name;
		Pila *casilla = NULL;
		int x,y,width,height,nro;
	public:
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
		void print_box_nro();
		void print_box_others();
		bool click(int,int);
		void insert(int);
};

void Board_box::print_box_nro(){
	int center_board_box_X = this->x + (this->width/2);
	int y = this->y + (this->height/2);
	rectangle(this->x,this->y,(this->x+this->width),(this->y+this->height));
	char str[3];
	itoa(this->nro,str,10);
	outtextxy(center_board_box_X,y+5,str);
	if(find_black(this->nro)) setfillstyle(SOLID_FILL,BLACK);
	else setfillstyle(SOLID_FILL,RED);
	floodfill(this->x+1,this->y+1,WHITE);
}

void Board_box::print_box_others(){
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
}

bool Board_box::click(int x,int y){
	return ((this->x>=x && (this->x+this->width)<=x) && (this->y>=y && (this->y+this->height)<=y)) ? true : false;
}

void Board_box::insert(int id){
	if(!verify_user(this->casilla,id)) insert_user(this->casilla,id);
	insert_coin(this->casilla,id);
}