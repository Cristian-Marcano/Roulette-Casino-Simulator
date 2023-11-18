#include<time.h>
#include"Panel.h"

#define windowWidth 1200 //El ancho de la pantalla grafica
#define windowHeight 700 //El alto de la pantalla grafica
#define deltaTime 1000/60 //Esto es para generar una tasa de refresco 60 por segundo
// En resumen seria como los fps

main(){
	initwindow(windowWidth,windowHeight,"Waos");
    int verde = COLOR(0,100,0); // elegir color verde para el fondo
    setbkcolor(verde); // editar fondo
    cleardevice(); //actualizar pantalla
	srand(time(NULL)); // generar un numero que no se repita
	//nro: cantidad de iteraciones que hara el while en este caso serian del 70 al 100 que puede dar
	//iteration: contador que aumentara por cada iteracion
	int nro = 70 + rand()%(100+1-70),iteration = -1,win_number;
	//porcentaje: es para cuando vaya justo a la mitad de la iteraciones, ya comience a desacelerar
	//square_angle_in_360_win: la casilla del numero ganador, pero en 360 grados
	double porcentaje = 0.5,square_angle_in_360_win;
	bool stop = true; // Comenzar a desacelerar la ruleta
	setlinestyle(0,0,1); // el ancho de las lineas de la ruleta 
//	Roulette *ruleta = new Roulette(centerX,centerY); //inicializar ruleta
//	ruleta->initialize(); //Establecer velocidad predeterminada
	Panel *panel_users = new Panel("Users");
	panel_users->set_bounds(10,10,(windowWidth*0.30)-10,windowHeight-10);
	panel_users->show_panel();
	Panel *panel_table = new Panel("Table");
	panel_table->set_bounds((windowWidth*0.30)+10,10,(windowWidth*0.325)-10,windowHeight-10);
	panel_table->show_panel();
	Panel *panel_roulette = new Panel("Roulette");
	panel_roulette->set_bounds((windowWidth*0.30)+(windowWidth*0.325)+10,10,(windowWidth*0.375)-20,windowHeight-10);
	panel_roulette->initialize_roulette();
	panel_roulette->show_panel();
//	do{
//		iteration++;
//		swapbuffers(); //esta funcion genera una fluidez al actualizar la pantalla
//		cleardevice();
//		panel_ruleta->show_panel();
//		ruleta->roulette_rotation(); // comienza rotar la ruleta
//		ruleta->ball_rotation(); // comieza a rotar al pelota
//		//Si stop es true comienza la desacelarion de la ruleta, pero eso se aplica en la funcion
//		//y como tal comienza a desacelerar cuando llega a la mitad del de las iteraciones
//		if(stop) ruleta->roulette_deceleration(stop,iteration,nro,win_number,porcentaje,square_angle_in_360_win);
//		else ruleta->ball_deceleration(square_angle_in_360_win);
//		//Sino osea la ruleta ya se paro, ahora comieza a desacelerar la bola
//		delay(deltaTime); //es para pausar la imagen por el tiempo indicado en la constante deltaTime
//	}while(ruleta->get_ball_speed()!=0); //esto se repetira hasta que la velociadad de la pelota sea 0, osea se pare
	system("pause>nul");
	closegraph();
	return 0;
}