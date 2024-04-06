#include"Boton.h"
#include"Ruleta.h"
#include"Tablero.h"
#include"Usuario.h"

class Panel{
	private:
		char *name;
		int x,y,width,height;
	public:
		User *user = NULL;
		Board *board = NULL;
		Button *button = NULL;
		Roulette *roulette = NULL;
		Panel(char *name){
			this->name = name;
		}
		void initialize_roulette(); // inicializar ruleta
		void initialize_board(); // inicializar tablero
		void initialize_user(string,double); // inicializar user
		void set_bounds(int,int,int,int); // establecer medidas/limites
		void show_panel(); // mostrar panel
		void show_number_win(int,int); // mostra circulo de nro ganador
		void apply_view_port(); // establecer tamaño del viewport
};

void Panel::initialize_roulette(){
	int center_panel_X = (this->x+(this->width/2)); //centro del plano y que sera de la ruleta
	int center_panel_Y = (this->y+(this->height/2))-(this->height/10); //centro del plano y que sera de la ruleta
	int radius3 = this->width/3, radius2 = radius3*0.8, radius = (2*radius3)/3; 
	// radius3: radio de la ruleta
	// radius2: radio del circulo intermedio de la ruleta 
	// radius1: radio del circulo chico de la ruleta
	this->roulette = new Roulette(center_panel_X,center_panel_Y,radius,radius2,radius3); // instanciar ruleta
	this->button = new Button("Girar"); // instanciar boton para girar la ruleta
	// establecer medidas/limites al boton
	this->button->set_bounds(this->x+radius3,this->height-(this->height/10)-(this->height/100),radius3,(this->height/10)-(this->height/100));
}

void Panel::initialize_board(){
	//instanciar tablero
	this->board = new Board(this->x+(this->width*0.05),this->y+(this->height*0.10),(this->width*0.9),(this->height*0.8));
	this->button = new Button("Limpiar"); //instanciar boton
	//establecer medidas/limites al boton
	this->button->set_bounds(this->x+(this->width/3),this->height-(this->height/10)-(this->height/100),(this->width/3),(this->height/10)-(this->height/100));
}

void Panel::initialize_user(string name="Admin",double money=50){
	this->user = new User(name,money); //instanciar usuario
	//establecer medidas/limites al cuadro del usuario
	this->user->set_bounds(this->x+(this->width/10),this->y+(this->height/8),(4*this->width/5),(this->height/3));
}

void Panel::set_bounds(int x,int y,int width,int height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Panel::show_panel(){
	settextstyle(11,0,1); // estilo de texto por defecto
	rectangle(this->x,this->y,this->x+this->width,this->height); // crea rectangulo
	outtextxy(this->x+5,this->y-5,this->name); // inserta nombre del panel encima del rectangulo
	if(this->roulette!=NULL || this->board!=NULL){ // si el objeto ruleta o el objeto tablero estan instanciado se muestra el boton 
		this->button->print_button(); //imprimir boton
		if(this->button->focus()) this->button->apply_color_focus(); //si estan enfocando al boton aplicar color de focus
		else this->button->apply_color(); // si no aplicar color default
	}
}

void Panel::show_number_win(int height,int win_number=-1){
	int size = (height>600) ? 2 : 1; //dependiendo del tamaño de la pantalla se elije el tamaño de la letra
	int center_panel_X = (this->x+(this->width/2)); // centro del circulo que es justo en el medio del panel
	int y = (this->y+(this->height)-(this->height/4)); // altura baja 1/4 de la altura del panel
	int radius = this->width/15; // radio del circulo
	setlinestyle(0,0,2); // establecer nuevo estilo de linea
	circle(center_panel_X,y,radius); // crear circulo
	setlinestyle(0,0,1); // establecer estilo por default de linea
	if(win_number>=0 && win_number<=36){ // si el numero ganador se encuentra entre ese rango mostrar numero
		settextstyle(10,0,size); // establecer estilo del texto
		settextjustify(CENTER_TEXT,VCENTER_TEXT); // colocar el ajuste de texto en un estilo centrado
		char nro[3]; // char donde contendra el nro
		itoa(win_number,nro,10); // pasa un nro a una cadena char
		outtextxy(center_panel_X,y+5,nro); // mostrar nro justo en el medio del circulo dibujado
		settextjustify(LEFT_TEXT,TOP_TEXT); // colocar el ajuste de texto en un estilo por default
		if(win_number==0) setfillstyle(SOLID_FILL,GREEN); // si el nro es 0 rellenar con verde
		else if(roulette->findNegros(win_number)) setfillstyle(SOLID_FILL,BLACK); // si es un nro de lo negros rellenar el fondo con negro
		else setfillstyle(SOLID_FILL,RED); // si no rellenar con rojo
		floodfill(center_panel_X,y+5,WHITE); // coordendas de donde va empezar el rellenado
	}
	else{ // si no rellenar el circulo de gris y sin nro
		setfillstyle(SOLID_FILL,COLOR(120,120,120));
		floodfill(center_panel_X,y,WHITE);
	}
}

void Panel::apply_view_port(){
	setviewport(this->x-5,0,this->x+this->width,this->height+10,1);
}