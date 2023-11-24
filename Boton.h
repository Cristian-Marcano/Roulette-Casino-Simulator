#include<iostream>
#include<graphics.h>

using namespace std;

class Button{
	private:
		string text_button;
		int x,y,width,height,color,color_focus;
	public:
		Button(string text){
			this->text_button = text;
		}
		void set_bounds(int,int,int,int);
		void print_button();
		bool focus();
		void apply_color_focus();
		void apply_color();
		bool click_button(int,int);
		void set_bk_color(int,int,int);
		void set_bk_color_focus(int,int,int);
		int get_bk_color();
		int get_bk_color_focus();
};

void Button::set_bounds(int x,int y,int width,int height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Button::print_button(){
	setcolor(WHITE);
	rectangle(this->x,this->y,this->x+this->width,this->y+this->height);
	char text[this->text_button.size()];
	strcpy(text,this->text_button.c_str());
	settextjustify(CENTER_TEXT,VCENTER_TEXT);
	outtextxy(this->x+(this->width/2),this->y+(this->height/2),text);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	this->focus();
}

bool Button::focus(){
	return ((mousex()>=this->x && mousex()<=(this->x+this->width)) && (mousey()>=this->y && mousey()<=(this->y+this->height))) ? true : false;
}

void Button::apply_color_focus(){
	setfillstyle(SOLID_FILL,this->color_focus);
	floodfill(this->x+5,this->y+5,WHITE);
}

void Button::apply_color(){
	setfillstyle(SOLID_FILL,this->color);
	floodfill(this->x+5,this->y+5,WHITE);
}

bool Button::click_button(int x,int y){
	return ((x>=this->x && x<=(this->x+this->width)) && (y>=this->y && y<=(this->y+this->height))) ? true : false;
}

void Button::set_bk_color(int r,int g,int b){
	this->color = COLOR(r,g,b);
}

void Button::set_bk_color_focus(int r,int g,int b){
	this->color_focus = COLOR(r,g,b);
}

int Button::get_bk_color(){
	return this->color;
}

int Button::get_bk_color_focus(){
	return this->color_focus;
}