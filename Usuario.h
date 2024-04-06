#include<iostream>
#include<graphics.h>

using namespace std;

class User{
	private:
		string name = "Nombre: ";
		int x,y,width,height;
	public:
		double money,bet = 0;
		User(string name,double money){
			this->name += name;
			this->money = money;
		}
		void set_bounds(int,int,int,int); // establecer medidas/limites
		void print_user(double); // imprimir cuadro de usuario mostrar monto, ganancia, apuesta 
		string amount_decimals(double); // esto es para recortar los decimales de double a 2 decimales
		
};

void User::set_bounds(int x,int y,int width,int height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void User::print_user(double ganancia=0){
	rectangle(this->x,this->y,this->x+this->width,this->height);
	settextstyle(1,0,1);
	settextjustify(CENTER_TEXT,VCENTER_TEXT);
	string credit = "Monto: " + this->amount_decimals(this->money);
	string gain = "Ganancia: " + this->amount_decimals(ganancia);
	string apuesta = "Apuesta: " + this->amount_decimals(this->bet);
	char str[gain.size()],amount[credit.size()],bet_str[apuesta.size()];
	strcpy(str,gain.c_str());
	strcpy(amount,credit.c_str());
	strcpy(bet_str,apuesta.c_str());
	outtextxy(this->x+(this->width/2),this->y+(this->height/8)+5,amount);
	outtextxy(this->x+(this->width/2),this->y+(this->height/4)+5,str);
	outtextxy(this->x+(this->width/2),this->y+(2*this->height/5)+5,bet_str);
	settextstyle(11,0,1);
	settextjustify(LEFT_TEXT,TOP_TEXT);
}

string User::amount_decimals(double amount){
	string decimal = to_string(amount);
	int i=0;
	do{
		if(decimal[i]==46) break;
		i++;
	}while(i<decimal.length());
	return decimal.substr(0,i+3);
}