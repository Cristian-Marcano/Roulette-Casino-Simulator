#include<time.h>
#include"Panel.h"

#define windowWidth 1200 //El ancho de la pantalla grafica
#define windowHeight 700 //El alto de la pantalla grafica
#define deltaTime 1000/60 //Esto es para generar una tasa de refresco 60 por segundo
// En resumen seria como los fps

char users[6] = "User",board[6] = "Board",roulette[9] = "Roulette";

void refresh(){ // funcion de refrescar pantalla
	swapbuffers(); // cambia de imagen en el buffer
	cleardevice(); // limpia la pantalla
}

void print_other_panels(Panel *&usuario,Panel *&tablero,double ganancia=0){
	usuario->show_panel(); // se muestra el panel usuario en la pantalla
	usuario->user->print_user(ganancia); // imprime el monto del usuario, el monto de la apuesta
	tablero->show_panel(); // mostrar el panel tablero junto el boton limpiar
	tablero->board->print_board(); // imprimir el tablero
}

int spin_roulette(Panel*&,Panel*&,Panel*&); // realizar giro de la rulata, retorna el numero ganador

main(){
	initwindow(windowWidth,windowHeight,"Waos");
    int verde = COLOR(0,100,0); // elegir color verde para el fondo
    setbkcolor(verde); // editar fondo
    refresh();
    setbkcolor(verde);
    refresh();
	srand(time(NULL)); // generar un numero que no se repita
	double ganancia = 0;// obtener las ganancias para mostrarlas en pantalla
	int win_number = -1,montdescont = 0; // numero ganador y el monto que se le descuenta al monto total del jugador
	Panel *panel_users = new Panel(users); // instanciar panel usuario
	panel_users->set_bounds(10,10,(windowWidth*0.30)-10,windowHeight-10); // estableciendo medidas/limites
	panel_users->initialize_user(); // inicializar el panel para el usuario
	panel_users->show_panel(); // mostrar panel
	Panel *panel_board = new Panel(board); // instanciar panel del tablero 
	panel_board->set_bounds((windowWidth*0.30)+10,10,(windowWidth*0.325)-10,windowHeight-10); // establecer medidas/limites
	panel_board->initialize_board(); // inicializar el panel para el tablero
	panel_board->board->initialize_boxes(); // inicializar tablero para las casillas
	panel_board->show_panel(); // mostrar el panel tablero
	panel_board->board->print_board(); // imprimir el tablero
	panel_board->button->set_bk_color(140,140,140); // establecer color por default del boton limpiar
	panel_board->button->set_bk_color_focus(85,85,85); // establecer color focus del boton limpiar
	Panel *panel_roulette = new Panel(roulette); // instanciar panel ruleta
	// establecer medidas/limites del panel ruleta
	panel_roulette->set_bounds((windowWidth*0.30)+(windowWidth*0.325)+10,10,(windowWidth*0.375)-20,windowHeight-10);
	panel_roulette->initialize_roulette(); // inicializar la ruleta 
	panel_roulette->show_panel(); // mostrar el panel ruleta
	panel_roulette->button->set_bk_color(140,140,140);  // establecer color por default del boton girar
	panel_roulette->button->set_bk_color_focus(85,85,85); // establecer color focus del boton girar
	// focus: true si el mouse esta haciendo focus algun boton
	// change: realizar actualizado de pantalla cuando haya un cambio
	bool focus = false,change = true;
	do{
		delay(deltaTime);
		//x: coordenada del mouse en x
		//y: coordenadas del mouse en y
		int x,y;
		if(panel_roulette->button->focus() && !focus){ // si se enfoca en el boton girar, cambiar color del boton
			change = true; // osea que hay cambio y volver actualizar pantalla
			focus = true; // en este momento esta haciendo focus
		} else if(focus && !panel_roulette->button->focus()){ // si no se enfoca en el girar, colocar color default
			change = true; // osea que hay cambio y volver actualizar pantalla
			focus = false; // en este momento ya no esta haciendo focus
		}
		if(panel_board->button->focus() && !focus){ // si se enfoca en el boton limpiar
			change = true;
			focus = true;
		} else if(focus && !panel_board->button->focus()){ // si no se enfoca en el boton limpiar
			change = true;
			focus = false;
		}
		if(ismouseclick(WM_LBUTTONDOWN)){ // si haces click
			getmouseclick(WM_LBUTTONDOWN,x,y); // obtener las coordenadas de x y del click
			if(panel_roulette->button->click_button(x,y)){ // verificar si presiono el boton girar
				win_number = spin_roulette(panel_roulette,panel_board,panel_users);
				ganancia = panel_board->board->hit(win_number); // obtener la suma de todas la ganancias
				panel_users->user->money += ganancia; // actualizar el dinero del usuario
				/* si la cantidad de dinero del usuario menos las fichas que aun tienen en el tablero
				 es mayor e igual a 0 se le resta la misma cantidad de la apuesta realizada en la jugada pasada*/
				if(panel_users->user->money-montdescont>=0) panel_users->user->money-=montdescont;
				else{ //si no, la apuesta pasa a 0 y se limpiar el tablero
					montdescont = 0;
					panel_users->user->bet = montdescont;
					panel_board->board->clear();
				}
				change = true; // hubo cambios, por lo tanto actualizar es necesario
			} else if(panel_board->button->click_button(x,y)){ // verificar si presiono el boton limpiar
				panel_board->board->clear(); //limpiar tablero
				panel_users->user->money+=montdescont; // retornar todo lo que se tenia pensado apostar
				montdescont=0; // el monto que se descuenta pasa a ser 0
				panel_users->user->bet = montdescont; // y la apuesta tambien
				change = true; // hay cambios
			} else if(panel_board->board->click(x,y) && panel_users->user->money-1>=0){ // verificar si presiona alguna de las casillas del tablero
				panel_users->user->money--; // disminuye 1 de monto por cada ficha
				montdescont++; // aumenta el monto que se le va a descontar
				panel_users->user->bet = montdescont; // se le coloca a la apuesta
				panel_board->board->click_boxes(x,y); // aumntar el nro de fichas en casilla
				change = true; // hubo cambio
			}
		}
		if(change){ // si hay cambio 
			cleardevice(); // se limpia la pantalla
			print_other_panels(panel_users,panel_board,ganancia);
			panel_roulette->show_panel(); // mostrar el panel ruleta junto el boton girar
			panel_roulette->show_number_win(windowHeight,win_number); // mostrar el numero ganador en el panel ruleta
			panel_roulette->roulette->roulette_rotation(); // mostrar ruleta estatica
			panel_roulette->roulette->ball_rotation(); // mostrar bola estatica
			swapbuffers(); // cambiar de imagen en el buffer
			change = false; // ya no hay cambio por el cual realizar
		}
	}while(true); // ciclo infinito
	closegraph();
	return 0;
}

int spin_roulette(Panel *&ruleta,Panel *&tablero,Panel *&usuarios){
	bool stop = true; // este permite que comience a frenar la ruleta 
	int nro = 70 + rand()%(100+1-70),iteration = -1,win_number; // el numero de iteraciones del 70 al 100 para parar la ruleta
	// porcent: el en que porcentaje de iteracion comenzara a desacelerar
	// square_angle_in_360_win: el angulo en 360° de la casilla ganadora
	double porcent = 0.5,square_angle_in_360_win; 
	ruleta->roulette->initialize(); // inicializar la velocidad de la ruleta y la bola
	// anteriormente no tenia velocidad pero ahora que la tiene al imprimirla ya no estara estatica
	cleardevice();
	print_other_panels(usuarios,tablero); // pintar los paneles usuario y tablero, para guardarlo en el buffer
	refresh();
	print_other_panels(usuarios,tablero);
	do{
		iteration++; // aumenta 1 en iteracion
		ruleta->roulette->roulette_rotation(); // mostrar ruleta
		ruleta->roulette->ball_rotation(); // mostrar bola
		// si stop esta true comienza a desacelerar la ruleta
		if(stop) ruleta->roulette->roulette_deceleration(stop,iteration,nro,win_number,porcent,square_angle_in_360_win);
		else ruleta->roulette->ball_deceleration(square_angle_in_360_win);
		//si no osea la rulata e habra parado, desacelerar la bola
		ruleta->show_panel(); // mostrar panel de la ruleta
		ruleta->show_number_win(windowHeight); // mostrar circulo de nro ganador
		delay(deltaTime); // tiempo 
		ruleta->apply_view_port(); // establecer viewport para realizar limpieado de pantalla en solo el panel ruleta
		swapbuffers(); // cambia de buffer
		clearviewport(); // limpia el viewpor del panel ruleta
		setviewport(0,0,windowWidth,windowHeight,1); // establecer el viewport a todo la panatalla, por defecto
	}while(ruleta->roulette->get_ball_speed()!=0); //esto finalizara cuando la bola se pare osea cuando su velocidad sea igual a 0
	return win_number; // retornar nro ganador
}