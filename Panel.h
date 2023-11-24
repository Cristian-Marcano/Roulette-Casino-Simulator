#include"Boton.h"
#include"Ruleta.h"
#include"Tablero.h"

class Panel{
	private:
		char *name;
		int x,y,width,height;
	public:
		Board *board;
		Button *button;
		Roulette *roulette;
		Panel(char *name){
			this->name = name;
		}
		void initialize_roulette();
		void initialize_board();
		void set_bounds(int,int,int,int);
		void show_panel();
		void show_number_win(int,int);
		void apply_view_port();
};

void Panel::initialize_roulette(){
	int center_panel_X = (this->x+(this->width/2));
	int center_panel_Y = (this->y+(this->height/2))-(this->height/10);
	int radius3 = this->width/3, radius2 = radius3*0.8, radius = (2*radius3)/3;
	this->roulette = new Roulette(center_panel_X,center_panel_Y,radius,radius2,radius3);
	this->button = new Button("Girar");
	this->button->set_bounds(this->x+radius3,this->height-(this->height/10)-(this->height/100),radius3,(this->height/10)-(this->height/100));
}

void Panel::initialize_board(){
	this->board = new Board(this->x+(this->width*0.05),this->y+(this->height*0.10),(this->width*0.9),(this->height*0.8));
}

void Panel::set_bounds(int x,int y,int width,int height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Panel::show_panel(){
	settextstyle(11,0,1);
	rectangle(this->x,this->y,this->x+this->width,this->height);
	outtextxy(this->x+5,this->y-5,this->name);
	if(this->roulette!=NULL){
		this->button->print_button();
		if(this->button->focus()) this->button->apply_color_focus();
		else this->button->apply_color();
	}
}

void Panel::show_number_win(int height,int win_number=-1){
	int size = (height>600) ? 2 : 1;
	int center_panel_X = (this->x+(this->width/2));
	int y = (this->y+(this->height)-(this->height/4));
	int radius = this->width/15;
	setlinestyle(0,0,2);
	circle(center_panel_X,y,radius);
	setlinestyle(0,0,1);
	if(win_number>=0 && win_number<=36){
		settextstyle(10,0,size);
		settextjustify(CENTER_TEXT,VCENTER_TEXT);
		char nro[3];
		itoa(win_number,nro,10);
		outtextxy(center_panel_X,y+5,nro);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		if(win_number==0) setfillstyle(SOLID_FILL,GREEN);
		else if(roulette->findNegros(win_number)) setfillstyle(SOLID_FILL,BLACK);
		else setfillstyle(SOLID_FILL,RED);
		floodfill(center_panel_X,y,WHITE);
	}
	else{
		setfillstyle(SOLID_FILL,COLOR(120,120,120));
		floodfill(center_panel_X,y,WHITE);
	}
}

void Panel::apply_view_port(){
	setviewport(this->x-5,0,this->x+this->width,this->height+10,1);
}