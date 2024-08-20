#include"Casilla_tablero.h"

class Board{
	private:
		// numbers_board: numeros del tablero
		const int numbers_board[37] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
		// *number_boxes: las casillas de los numeros del tablero exceptuando el 0
		// *other_boxes_1: casillas que es de apuestas que abarcan la mitad de todos los nros del tablero exceptuando el 0
		// por ejemplo: negro, rojo, impar, par, negro, rojo, del 1 al 18 y del 19 al 36
		// *other_boxes_2: casillas de apuestas de 1 al 12, 13 al 24 y 25 al 36
		// *other_boxes_3: casilas de apuestas de columnas del tablero sera vistas como 2:1
		Board_box *number_boxes[12][3], *other_boxes_1[6], *other_boxes_2[3], *other_boxes_3[3];
		int x,y,width,height;
	public:
		Board(int x,int y,int width,int height){
			this->x = x;
			this->y = y-(height/15);
			this->width = width;
			this->height = height;
		}
		void initialize_boxes(); // inicializar cada casilla del tablero
		void print_board(); // imprimir tablero
		void click_boxes(int,int); // colocarle +1 a la casilla que fue oprimida
		bool click(int,int); // retorna true si clickie el tablero
		void clear(); // limpiar el tablero osea todas las fichas desaparecen y vuelven al monto del usuario
		int hit(int); // retorna el monto de la suma de la casillas qu fueron acertadas
};

void Board::initialize_boxes(){
	const string characters[12] = {"18-1","Par","N","R","Impar","36-19","12-1","24-13","36-25","2:1","2:1","2:1"};
	int u=1;// desde el 1 por que ahi se enceuntra el 1 en el array numbers_board osea el 0 no debe de ser mostrado aqui
	for(int i=0; i<12; i++){
		for(int j=0; j<3; j++){
			//instanciar cada casilla  con sus medidas bien calculadas (fue dificil plantearm ele algoritmo xd)
			this->number_boxes[i][j] = new Board_box(this->numbers_board[u],this->x+((j+1)*this->width/4),this->y+((i+1)*this->height/14),(this->width/4),(this->height/14));
			u++; // aumenta la iteracion para pasar al siguiente nro
		}
		// instanciar el resto de casillas que son de apuestas 1:1 y 2:1
		if(i<6) this->other_boxes_1[i] = new Board_box(characters[i],this->x,this->y+((this->height/14)+(i*(this->height/7))),(this->width/8),(this->height/7));
		else if(i<9) this->other_boxes_2[i-6] = new Board_box(characters[i],this->x+(this->width/8),this->y+((this->height/14)+((i-6)*(2*this->height/7))),(this->width/8),(2*this->height/7));
		else this->other_boxes_3[i-9] = new Board_box(characters[i],this->x+(this->width/4)+((i-9)*(this->width/4)),this->y+(13*this->height/14),(this->width/4),(this->height/14));
	}
}

void Board::print_board(){
	//imprime el nro 0
	int center_box_0_X = this->x+(this->width/4)+(3*this->width/8);
	int y = this->y + (this->height/28);
	rectangle(this->x+(this->width/4),this->y,this->x+(this->width/4)+(3*this->width/4),this->y+(this->height/14));
	char str[2] = "0";
	settextstyle(10,0,1);
	settextjustify(CENTER_TEXT,VCENTER_TEXT);
	outtextxy(center_box_0_X,y+5,str);
	setfillstyle(SOLID_FILL,GREEN);
	floodfill(this->x+(this->width/4)+1,this->y+1,WHITE);
	// comienza a imprimir el resto de casillas del tablero
	for(int i=0; i<12; i++){
		for(int j=0; j<3; j++) this->number_boxes[i][j]->print_box_nro();
		if(i<6) this->other_boxes_1[i]->print_box_others();
		else if(i<9) this->other_boxes_2[i-6]->print_box_others();
		else this->other_boxes_3[i-9]->print_box_others();
	}
	settextstyle(11,0,1);
	settextjustify(LEFT_TEXT,TOP_TEXT);
}

bool Board::click(int x,int y){
	return ((this->x<=x && (this->x+this->width)>=x) && ((this->y + this->height/14)<=y && (this->y+this->height)>=y)) ? true : false;
}

void Board::click_boxes(int x,int y){
	for(int i=0; i<12; i++){
		if(this->number_boxes[i][0]->click(x,y)){
			this->number_boxes[i][0]->fichas_users++;
			break;
		}else if(this->number_boxes[i][1]->click(x,y)){
			this->number_boxes[i][1]->fichas_users++;
			break;
		} else if(this->number_boxes[i][2]->click(x,y)){
			this->number_boxes[i][2]->fichas_users++;
			break;
		} else if(i<6 && this->other_boxes_1[i]->click(x,y)){
			this->other_boxes_1[i]->fichas_users++;
			break;
		} else if(i<9 && this->other_boxes_2[i-6]->click(x,y)){
			this->other_boxes_2[i-6]->fichas_users++;
			break;
		} else if(this->other_boxes_3[i-9]->click(x,y)){
			this->other_boxes_3[i-9]->fichas_users++;
			break;
		}
	}
}

void Board::clear(){
	for(int i=0; i<12; i++){
		this->number_boxes[i][0]->fichas_users = 0;
		this->number_boxes[i][1]->fichas_users = 0;
		this->number_boxes[i][2]->fichas_users = 0;
		if(i<6) this->other_boxes_1[i]->fichas_users = 0;
		else if(i<9) this->other_boxes_2[i-6]->fichas_users = 0;
		else this->other_boxes_3[i-9]->fichas_users = 0;
	}
}

int Board::hit(int nro){
	int sum = 0;
	for(int i=0; i<12; i++){
		for(int j=0; j<3; j++) if(this->number_boxes[i][j]->fichas_users>0 && this->number_boxes[i][j]->get_nro()==nro){
			sum += this->number_boxes[i][j]->fichas_users*35;
		}
		if(i<6) sum += this->other_boxes_1[i]->get_amount_win(nro);
		else if(i<9) sum += this->other_boxes_2[i-6]->get_amount_win(nro);
		else sum += this->other_boxes_3[i-9]->get_amount_col(nro,i-9);
	}
	return sum;
}