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
		void set_bounds(int,int,int,int); // establecer medidas
		void print_button(); // imprimir boton
		bool focus(); // retorn true si el mouse esta encima del boton
		void apply_color_focus(); // aplicar color de color focus
		void apply_color(); // aplicar color default
		bool click_button(int,int); // retorna true si el mouse presiono el botton
		void set_bk_color(int,int,int); // cambiar el color del color por default del boton
		void set_bk_color_focus(int,int,int); // cambiar el color del color focus del boton
};

void Button::set_bounds(int x,int y,int width,int height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Button::print_button(){
	setcolor(WHITE); // establecer el color de escritura en blanco
	rectangle(this->x,this->y,this->x+this->width,this->y+this->height); // mostrar un rectangulo que es la forma del boton
	char text[this->text_button.size()]; // text recibira el valor del atributo text_button
	strcpy(text,this->text_button.c_str());
	settextjustify(CENTER_TEXT,VCENTER_TEXT); // establecer ajuste de estilo de texto a centrado
	outtextxy(this->x+(this->width/2),this->y+(this->height/2),text);
	settextjustify(LEFT_TEXT,TOP_TEXT); // establecer ajuste de estilo de texto a por default
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