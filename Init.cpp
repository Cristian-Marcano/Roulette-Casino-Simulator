#include<iostream>
#include<graphics.h>
#include<cmath>

#define windowWidth 1200
#define windowHeight 700
#define deltaTime 1000/60

using namespace std;

bool findNegros(int);

void ball_rotation(double &ball_angle,int centerX,int centerY,int radius,int distancia){
	// gira alrededor del punto que se le coloco como referencia
	int x = centerX + distancia * cos(ball_angle),y = centerY + distancia * sin(ball_angle);
	setcolor(YELLOW);
	circle(x,y,radius);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(x,y,YELLOW);
	ball_angle-=M_PI/36;
}

void roulette_rotation(double roulette_angle,int centerX,int centerY,int radius,int radius2){
	for(int i=0; i<37; i++){
		roulette_angle+= 2*M_PI/37;// getch(); fflush(stdin);
		int x1 = centerX+radius*cos(roulette_angle),y1 = centerY+radius*sin(roulette_angle),x2 = centerX+radius2*cos(roulette_angle),y2 = centerY+radius2*sin(roulette_angle);
		line(x1,y1,x2,y2);
	}
}

void paint_squares(double &angle,int centerX,int centerY,int radius,int radius2){
	for(int i=0; i<37; i++){
		angle+= 2*M_PI/37;
		int x3 = centerX+((radius+radius2)/2)*cos((angle+(M_PI/60))),y3 = centerY+((radius+radius2)/2)*sin((angle+(M_PI/60)));
		if(i==0) setfillstyle(SOLID_FILL,GREEN);
		else if(findNegros(i)) setfillstyle(SOLID_FILL,BLACK);
		else setfillstyle(SOLID_FILL,RED);
		floodfill(x3,y3,WHITE);
	}
}

main(){
	initwindow(windowWidth,windowHeight,"Waos");
    int centerX = windowWidth/2; // coordenada X del centro del circulo
    int centerY = windowHeight/2; // coordenada Y del centro del circulo
    int radius = 100, radius2 = 150; // Radio del circulo
    int distancia = 50;
    double roulette_angle = -M_PI/2,ball_angle = -M_PI/2; // angulo inicial de rotacion en radianes
    int verde = COLOR(0,100,0);
	setbkcolor(verde);
//	cleardevice();
	while(!kbhit()){
		swapbuffers();
		cleardevice();
		circle(centerX,centerY,radius);
		circle(centerX,centerY,radius2);
//		circle(centerX,centerY,radius+20);
//		roulette_rotation(roulette_angle,centerX,centerY,radius,radius2);
//		paint_squares(roulette_angle,centerX,centerY,radius,radius2);
		for(int i=0; i<37; i++){
			roulette_angle+= 2*M_PI/37; //getch(); fflush(stdin);
			int x1 = centerX+radius*cos(roulette_angle),y1 = centerY+radius*sin(roulette_angle),x2 = centerX+radius2*cos(roulette_angle),y2 = centerY+radius2*sin(roulette_angle),x3=centerX+((radius+radius2)/2)*cos((roulette_angle+(M_PI/37))),y3=centerY+((radius+radius2)/2)*sin((roulette_angle+(M_PI/37)));
			line(x1,y1,x2,y2);
			if(i==0) setfillstyle(SOLID_FILL,GREEN);
			else if(findNegros(i)) setfillstyle(SOLID_FILL,BLACK);
			else setfillstyle(SOLID_FILL,RED);
//			setfillstyle(SOLID_FILL,((i==0) ? GREEN : ((findNegros(i)) ? BLACK : RED )));
//			circle(x3,y3,10);
			floodfill(x3,y3,WHITE);
		}
		circle(centerX,centerY,radius+20);
		ball_rotation(ball_angle,centerX,centerY,9,radius+10);
		roulette_angle+=M_PI/90;
		setcolor(WHITE);
		// Generar un número aleatorio del 0 al 36
        int numero = rand() % 37;
        // Detener la bola en el número aleatorio
        if (ball_angle <= -M_PI / 2 - (numero * M_PI / 18)) {
            ball_angle = -M_PI / 2 - (numero * M_PI / 18);
            cout<<"\n\t\tball "<<ball_angle*(180/M_PI);
            cout<<numero;
            getch();
        }
		delay(deltaTime);
	}
	closegraph();
	return 0;
}

bool findNegros(int casilla){
	int numeros_negros[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
	for(int i: numeros_negros) if(i==casilla) return true;
	return false;
}