#include<iostream>
#include<graphics.h>

using namespace std;

class Board_box{
	private:
		string name;
		int x,y,width,height,nro;
	public:
		int fichas_users[10] = {0,0,0,0,0,0,0,0,0,0};
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
		void print_box_nro(int);
		void print_box_others(int);
		bool click(int,int);
		void show_coins(int);
		bool find_black(int);
};

void Board_box::print_box_nro(int id){
	int center_board_box_X = this->x + (this->width/2);
	int y = this->y + (this->height/2);
	rectangle(this->x,this->y,(this->x+this->width),(this->y+this->height));
	char str[3];
	itoa(this->nro,str,10);
	outtextxy(center_board_box_X,y+5,str);
	if(this->find_black(this->nro)) setfillstyle(SOLID_FILL,BLACK);
	else setfillstyle(SOLID_FILL,RED);
	floodfill(this->x+1,this->y+1,WHITE);
	if(this->fichas_users[id-1]>0) this->show_coins(id);
}

void Board_box::print_box_others(int id){
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
	if(this->fichas_users[id-1]>0) this->show_coins(id);
}

void Board_box::show_coins(int id){
	char str[3];
	itoa(this->fichas_users[id-1],str,10);
	int center_coin_x = this->x + (this->width*0.8),center_coin_y = this->y + (this->height*0.8);
	int radius = 10;
	circle(center_coin_x,center_coin_y,radius);
	settextstyle(11,0,1); setcolor(BLACK);
	outtextxy(center_coin_x,center_coin_y+5,str);
	settextstyle(10,0,1); setcolor(WHITE);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(center_coin_x,center_coin_y,WHITE);
}

bool Board_box::find_black(int nro){
	const int numbers_negros[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
	for(int i: numbers_negros) if(i==nro) return true; 
	return false;
}

bool Board_box::click(int x,int y){
	return ((this->x<=x && (this->x+this->width)>=x) && (this->y<=y && (this->y+this->height)>=y)) ? true : false;
}