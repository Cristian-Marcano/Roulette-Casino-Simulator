#include"Casilla_tablero.h"

class Board{
	private:
		const int numbers_board[37] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
		Board_box *number_boxes[12][3], *other_boxes_1[6], *other_boxes_2[3], *other_boxes_3[3];
		int x,y,width,height;
	public:
		Board(int x,int y,int width,int height){
			this->x = x;
			this->y = y-(height/15);
			this->width = width;
			this->height = height;
		}
		void initialize_boxes();
		void print_board();
		void click_boxes(int,int,int);
};

void Board::initialize_boxes(){
	string characters[12] = {"18-1","Par","N","R","Impar","36-19","12-1","24-13","36-15","2:1","2:1","2:1"};
	int u=1;
	for(int i=0; i<12; i++){
		for(int j=0; j<3; j++){
			this->number_boxes[i][j] = new Board_box(this->numbers_board[u],this->x+((j+1)*this->width/4),this->y+((i+1)*this->height/14),(this->width/4),(this->height/14));
			u++;
		}
		if(i<6) this->other_boxes_1[i] = new Board_box(characters[i],this->x,this->y+((this->height/14)+(i*(this->height/7))),(this->width/8),(this->height/7));
		else if(i<9) this->other_boxes_2[i-6] = new Board_box(characters[i],this->x+(this->width/8),this->y+((this->height/14)+((i-6)*(2*this->height/7))),(this->width/8),(2*this->height/7));
		else this->other_boxes_3[i-9] = new Board_box(characters[i],this->x+(this->width/4)+((i-9)*(this->width/4)),this->y+(13*this->height/14),(this->width/4),(this->height/14));
	}
}

void Board::print_board(){
	int center_box_0_X = this->x+(this->width/4)+(3*this->width/8);
	int y = this->y + (this->height/28);
	rectangle(this->x+(this->width/4),this->y,this->x+(this->width/4)+(3*this->width/4),this->y+(this->height/14));
	char str[2];
	itoa(this->numbers_board[0],str,10);
	settextstyle(10,0,1);
	settextjustify(CENTER_TEXT,VCENTER_TEXT);
	outtextxy(center_box_0_X,y+5,str);
	setfillstyle(SOLID_FILL,GREEN);
	floodfill(this->x+(this->width/4)+1,this->y+1,WHITE);
	for(int i=0; i<12; i++){
		for(int j=0; j<3; j++) this->number_boxes[i][j]->print_box_nro();
		if(i<6) this->other_boxes_1[i]->print_box_others();
		else if(i<9) this->other_boxes_2[i-6]->print_box_others();
		else this->other_boxes_3[i-9]->print_box_others();
	}
	settextstyle(11,0,1);
	settextjustify(LEFT_TEXT,TOP_TEXT);
}

void Board::click_boxes(int x,int y,int id){
	if((this->x>=x && (this->x+this->width)<=x) && (this->y>=y && (this->y+this->height)<=y)){
		for(int i=0; i<12; i++){
			for(int j=0; j<3; j++){
				if(this->number_boxes[i][j]->click(x,y)) this->number_boxes[i][j]->insert(id);
			}
		}
	}
}