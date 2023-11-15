#include<iostream>
#include<graphics.h>
#include<cmath>
#include<time.h>

#define windowWidth 1200
#define windowHeight 700
#define deltaTime 1000/60

using namespace std;

bool findNegros(int);

void ball_rotation(long double &ball_angle,int centerX,int centerY,int radius,int distancia,double speed){
	// gira alrededor del punto que se le coloco como referencia
	int x = centerX + distancia * cos(ball_angle*(M_PI/180)),y = centerY + distancia * sin(ball_angle*(M_PI/180));
	setcolor(YELLOW);
	circle(x,y,radius);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(x,y,YELLOW);
	ball_angle-=speed;
}

void roulette_rotation(long double &roulette_angle,int centerX,int centerY,int radius,int radius2){
	int numeros_ruleta[] = {0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,32,10,37,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26};
	for(int i: numeros_ruleta){
		roulette_angle+= 9.473684211;// getch(); fflush(stdin);
		int x1 = centerX+radius*cos((roulette_angle*(M_PI/180))),y1 = centerY+radius*sin((roulette_angle*(M_PI/180))),x2 = centerX+radius2*cos((roulette_angle*(M_PI/180))),y2 = centerY+radius2*sin((roulette_angle*(M_PI/180))),x3=centerX+((radius+radius2)/2)*cos((roulette_angle*(M_PI/180)+(M_PI/38))),y3=centerY+((radius+radius2)/2)*sin((roulette_angle*(M_PI/180)+(M_PI/38)));
		line(x1,y1,x2,y2);
		if(i==0 || i==37){
			setfillstyle(SOLID_FILL,GREEN);
			setbkcolor(GREEN);
		}
		else if(findNegros(i)){
			setfillstyle(SOLID_FILL,BLACK);
			setbkcolor(BLACK);
		}
		else{
			setfillstyle(SOLID_FILL,RED);
			setbkcolor(RED);
		}
		floodfill(x3,y3,WHITE);
//		string x = to_string(i);
//		char var[x.size()];
//		strcpy(var,x.c_str());
//		outtextxy(x3,y3,var);
	}
}

int search_repetition_for_square(int win_number){
	int numeros_ruleta[] = {0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,32,10,37,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26};
	int size = sizeof(numeros_ruleta)/sizeof(numeros_ruleta[0]);
	for(int i=0; i<size; i++){
		if(numeros_ruleta[i]==win_number) return i+1;
	}
	return 0;
}

main(){
	initwindow(windowWidth,windowHeight,"Waos");
    int centerX = windowWidth/2; // coordenada X del centro del circulo
    int centerY = windowHeight/2; // coordenada Y del centro del circulo
    int radius = 100, radius2 = 150, radius3 = 120; // Radio del circulo
    long double roulette_angle = -90,ball_angle = -90, square_angle_win = 0, square_angle_in_360_win; // angulo inicial de rotacion en radianes
    int verde = COLOR(0,100,0);
    setbkcolor(verde);
	srand(time(NULL));
	int nro = 70 + rand()%(100+1-70),iteration = -1,win_number,rpte = 0;
	double speed_roulette=5,speed_ball=9; //velocidad de ruleta 5°, velocidad de bola 9°
	bool stop = true;
	setlinestyle(0,0,2);
	do{
		iteration++;
		swapbuffers();
		cleardevice();
//		setfillstyle(SOLID_FILL,verde);
//		bar(0,0,windowWidth,windowHeight);
		circle(centerX,centerY,radius);
		circle(centerX,centerY,radius2);
		roulette_rotation(roulette_angle,centerX,centerY,radius,radius2);
		circle(centerX,centerY,radius3);
		ball_rotation(ball_angle,centerX,centerY,((radius3-radius)/2)-1,((radius+radius3)/2),speed_ball);
		if(speed_roulette==0){
			if(ball_angle<-360) ball_angle+=360;
			if(speed_ball>4) speed_ball-=0.25;
			else if(speed_ball>1.1) speed_ball-=0.1;
			else if(round(360+ball_angle)==round(square_angle_in_360_win)) speed_ball=0;
		}
		if(iteration==round(nro*0.50)) speed_roulette = 4.5;
		else if(iteration==round(nro*0.60)) speed_roulette = 4;
		else if(iteration==round(nro*0.65)) speed_roulette = 3.6;
		else if(iteration==round(nro*0.70)) speed_roulette = 3;
		else if(iteration==round(nro*0.75)) speed_roulette = 2.5;
		else if(iteration==round(nro*0.80)) speed_roulette = 2;
		else if(iteration==round(nro*0.90)) speed_roulette = 1.5;
		else if(iteration==nro && stop){
			speed_roulette = 0;
			win_number = rand()%37;
			rpte = search_repetition_for_square(win_number);
			square_angle_win = roulette_angle + ((9.473684211*rpte) +4.736842105);
			int n = ceil(square_angle_win/(360));
			square_angle_in_360_win = square_angle_win -((n-1)*(360));
			stop = false;
			n = ceil(ball_angle/(-360));
			ball_angle += (n-1)*(360);
			cout<<"\n\t\tRepeticion -> "<<rpte;
			cout<<"\n\t\tNumero ganador -> "<<win_number<<"\n\t\tAngulo -> "<<(square_angle_in_360_win); 
//			system("pause>nul");
			
		}
		roulette_angle+=speed_roulette;
		setcolor(WHITE);
		delay(deltaTime);
//		setbkcolor(verde);
	}while(speed_ball!=0);
	system("pause>nul");
	closegraph();
	return 0;
}

bool findNegros(int casilla){
	int numeros_negros[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
	for(int i: numeros_negros) if(i==casilla) return true;
	return false;
}