#include"Ruleta.h"

class Panel{
	private:
		string name;
		Roulette *ruleta;
		int x,y,width,height;
	public:
		Panel(string name){
			this->name = name;
		}
		void initialize_roulette();
		void set_bounds(int,int,int,int);
		void show_panel();
};

void Panel::initialize_roulette(){
	int center_panel_X = (this->x+(this->width/2));
	int center_panel_Y = (this->y+(this->height/2))-(this->height/10);
	int radius3 = this->width/3, radius2 = radius3*0.8, radius = (2*radius3)/3;
	this->ruleta = new Roulette(center_panel_X,center_panel_Y,radius,radius2,radius3);
}

void Panel::set_bounds(int x,int y,int width,int height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Panel::show_panel(){
	rectangle(this->x,this->y,this->x+this->width,this->height);
	char str[this->name.size()];
	strcpy(str,this->name.c_str());
	outtextxy(this->x+5,this->y-5,str);
	if(this->ruleta!=NULL){
		setlinestyle(0,0,2);
		this->ruleta->print_roulette();
		setlinestyle(0,0,1);
	}
}