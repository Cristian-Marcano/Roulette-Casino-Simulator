#include<time.h>
#include"Panel.h"

#define windowWidth 1200 //El ancho de la pantalla grafica
#define windowHeight 700 //El alto de la pantalla grafica
#define deltaTime 1000/60 //Esto es para generar una tasa de refresco 60 por segundo
// En resumen seria como los fps

char users[6] = "Users",board[6] = "Table",roulette[9] = "Roulette";

void refresh(){
	swapbuffers();
	cleardevice();
}

int spin_roulette(Panel*&,Panel*&,Panel*&,int);

main(){
	initwindow(windowWidth,windowHeight,"Waos");
    int verde = COLOR(0,100,0); // elegir color verde para el fondo
    setbkcolor(verde); // editar fondo
    refresh();
    setbkcolor(verde);
    refresh();
	srand(time(NULL)); // generar un numero que no se repita
	int win_number,id=1;
	Panel *panel_users = new Panel(users);
	panel_users->set_bounds(10,10,(windowWidth*0.30)-10,windowHeight-10);
	panel_users->show_panel();
	Panel *panel_board = new Panel(board);
	panel_board->set_bounds((windowWidth*0.30)+10,10,(windowWidth*0.325)-10,windowHeight-10);
	panel_board->initialize_board();
	panel_board->board->initialize_boxes();
	panel_board->show_panel();
	panel_board->board->print_board(id);
	Panel *panel_roulette = new Panel(roulette);
	panel_roulette->set_bounds((windowWidth*0.30)+(windowWidth*0.325)+10,10,(windowWidth*0.375)-20,windowHeight-10);
	panel_roulette->initialize_roulette();
	panel_roulette->show_panel();
	panel_roulette->button->set_bk_color(140,140,140);
	panel_roulette->button->set_bk_color_focus(85,85,85);
	bool focus = false,change = true;
	do{
		int x,y;
		if(panel_roulette->button->focus() && !focus){
			change = true;
			focus = true;
		} else if(focus && !panel_roulette->button->focus()){
			change = true;
			focus = false;
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x,y);
			if(panel_roulette->button->click_button(x,y)){
				win_number = spin_roulette(panel_roulette,panel_board,panel_users,id);
				change = true;
			}
			else if(panel_board->board->click(x,y)){
				panel_board->board->click_boxes(x,y,id);
				change = true;
			}
		}
		if(change){
			panel_users->show_panel();
			panel_board->show_panel();
			panel_board->board->print_board(id);
			panel_roulette->show_panel();
			panel_roulette->show_number_win(windowHeight,win_number);
			panel_roulette->roulette->roulette_rotation();
			panel_roulette->roulette->ball_rotation();
			swapbuffers();
			change = false;
		}
	}while(true);
	closegraph();
	return 0;
}

int spin_roulette(Panel *&ruleta,Panel *&tablero,Panel *&usuarios,int id){
	bool stop = true;
	int nro = 70 + rand()%(100+1-70),iteration = -1,win_number;
	double porcent = 0.5,square_angle_in_360_win; 
	ruleta->roulette->initialize();
	usuarios->show_panel();
	tablero->show_panel();
	tablero->board->print_board(id);
	swapbuffers();
	usuarios->show_panel();
	tablero->show_panel();
	tablero->board->print_board(id);
	do{
		ruleta->apply_view_port();
		swapbuffers();
		clearviewport();
		setviewport(0,0,windowWidth,windowHeight,1);
		iteration++;
		ruleta->roulette->roulette_rotation();
		ruleta->roulette->ball_rotation();
		if(stop) ruleta->roulette->roulette_deceleration(stop,iteration,nro,win_number,porcent,square_angle_in_360_win);
		else ruleta->roulette->ball_deceleration(square_angle_in_360_win);
		ruleta->show_panel();
		ruleta->show_number_win(windowHeight);
		delay(deltaTime);
	}while(ruleta->roulette->get_ball_speed()!=0);
	return win_number;
}