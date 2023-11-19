#include<iostream>
#include<graphics.h>
#include<cmath>

//este angulo lo saque dividiendo 360/37, que 37 seria las casillas que va haber en la ruleta
#define squareAngle 9.72972973 // este es el angulo que hay entre cada casilla
#define mid_sA 4.864864865 // este es el angulo de la mitad de la casilla

using namespace std;

class Roulette{
	private:
		//roulette_numbers: numeros de la ruleta en orden de izquierda a derecha
		const int roulette_numbers[37] = {0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,32,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26};
		//center_roulette... : coordenadas del centro de la ruleta
		//radius: radio del circulo interno, osea el mas pequeño
		//radius2: radio del circulo medio, el que esta entre el mas grande y el mas pequeño
		//radius3: radio del circulo grande, el que es el tamaño completo de la ruleta
		int center_roulette_X, center_roulette_Y, radius, radius2, radius3;
		//roulette_angle: angulo inicial de la ruleta esto es en base al angulo inicial de la ruleta
		//ball_angle: angulo inicial de la bola dentro de la ruleta
		//roulette_speed: velocidad de la ruleta en grados
		//ball_speed: velocidad de la bola en grados
		double roulette_angle = -90, ball_angle = -90, roulette_speed = 0, ball_speed = 0;
	public:
		Roulette(int x, int y,int radius,int radius2,int radius3){ //inicializar ruleta
			this->center_roulette_X = x;
			this->center_roulette_Y = y;
			this->radius = radius;
			this->radius2 = radius2;
			this->radius3 = radius3;
		}
		void initialize(); //inicializar velocidad
//		void print_roulette(); // muestra la ruleta estatica
		void roulette_rotation(); //rotacion de la ruleta
		void ball_rotation(); //rotacion de la bola
		int search_repetition_for_square(int); // buscar cuantas casillas hay por delante de la casilla 0 hasta encontrar la casilla ganadora
		bool findNegros(int); // retorna true si es un numero de casilla negro
		void roulette_deceleration(bool&,int,int,int&,double&,double&); // desacelerar ruleta
		void ball_deceleration(double); //desacelerar bola
		void set_roulette_angle(int);
		void set_roulette_speed(double);
		void set_ball_angle(int);
		void set_ball_speed(double);
		double get_roulette_speed();
		double get_ball_speed();
};

void Roulette::initialize(){
	this->ball_speed = 9;
	this->roulette_speed = 5;
}

void Roulette::roulette_rotation(){
	setcolor(WHITE); //Color de trazado es blanco
	setlinestyle(0,0,2);
	circle(this->center_roulette_X,this->center_roulette_Y,this->radius); //1er circulo, el mas pequeño
	circle(this->center_roulette_X,this->center_roulette_Y,this->radius3); //3er crculo, el mas grande
	for(int i: this->roulette_numbers){ // este for itera la cantidad exacta de elementos que hay en un vector y i: es igual cada elemento de este, entros palabras es el numero de la casilla
		this->roulette_angle += squareAngle; // para generar un trazo y que este vaya cambiando de angulo debe de ser sumado al angulo que hay en una casilla
		// x1 y y1: punto que se encontraran en el 1er circulo
		// x2 y y2: punto que se encuentra en el 3er circulo 
		// x3 y y3: punto que se encuentra entre el 1er circulo y el 3er circulo
		int x1 = this->center_roulette_X + this->radius * cos(this->roulette_angle*(M_PI/180)), y1 = this->center_roulette_Y + this->radius * sin(this->roulette_angle*(M_PI/180));
		int x2 = this->center_roulette_X + this->radius3 * cos(this->roulette_angle*(M_PI/180)), y2 = this->center_roulette_Y + this->radius3 * sin(this->roulette_angle*(M_PI/180));
		int x3 = this->center_roulette_X + ((this->radius+this->radius3)/2) * cos((this->roulette_angle+mid_sA)*(M_PI/180)), y3 = this->center_roulette_Y + ((this->radius+this->radius3)/2) * sin((this->roulette_angle+mid_sA)*(M_PI/180));
		line(x1,y1,x2,y2); //genera trazo por trazo
		//al generar un trazo necesita rellenar la ruleta justo unos grados por delante del trazo ya generado
		if(i==0) setfillstyle(SOLID_FILL,GREEN); //Se elije el colocar a rellenar verde si la casilla es el numero 0
		else if(this->findNegros(i)) setfillstyle(SOLID_FILL,BLACK); //si la casilla es uno de los numeros negros se elije negro
		else setfillstyle(SOLID_FILL,RED); //si no se da ninguno de lo anterior se elije negro
		floodfill(x3,y3,WHITE); //aqui se rellena el espacio seleccionado por el punto
		//el punto esta medio angulo del angulo por casila
		//WHITE por que ese es borde que no puede pintar
	}
	circle(this->center_roulette_X,this->center_roulette_Y,this->radius2); // 2do circulo
	this->roulette_angle += this->roulette_speed; //se cambia de posicion la ruleta para generar el efecto de que esta girando 5 grados por fps
	setlinestyle(0,0,1);
}

void Roulette::ball_rotation(){
	int distancia = (this->radius2+this->radius)/2; //distancia que debe haber entre el centro de la ruleta 
	//X y Y: coordenadas del centro de la pelota estas van cambiando dependiendo del angulo
	int x = this->center_roulette_X + distancia * cos(this->ball_angle*(M_PI/180)), y = this->center_roulette_Y + distancia * sin(this->ball_angle*(M_PI/180));
	setcolor(YELLOW);// se cambia el color de trazado
	circle(x,y,((this->radius2-this->radius)/2)-1); // dibula la pelota
	setfillstyle(SOLID_FILL,YELLOW);// se elije el color de relleno de la pelota 
	floodfill(x,y,YELLOW); // se rellena la pelota
	this->ball_angle -= this->ball_speed; // se cambia de angulo la pelota oara generar efecto de movimiento
	setcolor(WHITE);
}

int Roulette::search_repetition_for_square(int win_number){
	int size = sizeof(this->roulette_numbers)/sizeof(this->roulette_numbers[0]); //saber el tamaño del array
	for(int i=0; i<size; i++) if(this->roulette_numbers[i]==win_number) return i+1; //si se encuentra el numero ganador se retorna cuantas casilla esta por delante de la casilla 0
	return 0;
}

bool Roulette::findNegros(int casilla){
	const int numbers_negros[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35}; //numeros de casillas negras
	for(int i: numbers_negros) if(i==casilla) return true; // si el numero que se paso como parametro es igual a uno de los del array retorna true
	return false; // se acabo el array y el numero pasado por el parametro no es un numero de casilla negra
}

void Roulette::roulette_deceleration(bool &stop,int i,int finish,int &win_number,double &porcent,double &square_angle_in_360){
	double speed = this->roulette_speed - 0.5; // speed es la variable que sera asignada a la velocidad de la ruleta, hara reducir la velocidad
	if(i==finish){ // si la iteracion es igual al nro de iteraciones deseadas se detiene la ruleta
		this->roulette_speed = 0;
		win_number = rand() % 37; // genera un numero ganador del 0 al 36
		int rpte = this->search_repetition_for_square(win_number); // busca la cantidad de casillas por delante para saber el angulo de la casilla ganadora
		double square_angle_win = this->roulette_angle + ((squareAngle*rpte) + mid_sA); // es el angulo de la casilla ganadora, se multiplica el angulo que hay de cada casilla por la cantidad de casillas que hay hasta encontrar el nro ganador
		int n = ceil(square_angle_win/360); // calcular las veces que angulo rebasa los 360°
		square_angle_in_360 = square_angle_win - ((n-1)*360); // el angulo anterior probablemente era mas de 360° por lo tanto aqui se aplica la reducion  
		n = ceil(this->ball_angle/(-360)); // lo mismo con el angulo de la bola
		this->ball_angle += n*360;
		stop = false; // esto hara que comience a desacelerar la pelota
	}
	else if(i==round(finish*porcent)){ // si no, la ruleta comenzara a reducir su velocidad cuando llegue al 50% y mas
		this->roulette_speed = speed;
		if(porcent<0.90) porcent += 0.10; // este porcentaje aumentara hasta que llegue al 90% que de ahi se espera la cantidad de iterciones planeadas
	}
}

void Roulette::ball_deceleration(double square_angle_in_360){
	if(this->ball_angle<0) this->ball_angle += 360; // cada vez que el angulo sea menor que 0, es decir es negativo se le añade 360° para realizar mejor los calculos
	if(this->ball_speed>4) this->ball_speed -= 0.25; // reduce 0.25 de velocidad por cada iteracion que la velocidad sea mayor que 4°
	else if(this->ball_speed>1) this->ball_speed -= 0.1; // los mismo pero con 1.1
	else if(round(this->ball_angle)==round(square_angle_in_360)) this->ball_speed = 0; //si los angulos son iguales se detiene la bola
}

void Roulette::set_roulette_angle(int angle){
	this->roulette_angle += angle;
} 

void Roulette::set_roulette_speed(double speed){
	this->roulette_speed = speed;
}

void Roulette::set_ball_angle(int angle){
	this->ball_angle += angle;
}

void Roulette::set_ball_speed(double speed){
	this->ball_speed = speed;
}

double Roulette::get_roulette_speed(){
	return this->roulette_speed;
}

double Roulette::get_ball_speed(){
	return this->ball_speed;
}