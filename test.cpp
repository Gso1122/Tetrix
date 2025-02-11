#define _CRT_SECURE_NO_WARNINGS
//CLIENT
#include <cstdlib>
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
// need link with Ws2_32.lib
#pragma comment(lib, "wsock32.lib")

#define DELAY 1
#define FRAME 200
#define SIZE 10
//#define IP "140.136.146.151"
//¤W¦â¥Î
//Ref:https://www.gomcu.com/cc-console/

#define TC_NONE     0
#define TC_BG_INTENSIFY BACKGROUND_INTENSITY
#define TC_FG_INTENSIFY FOREGROUND_INTENSITY
#define TC_FGBG_INTENSIFY (FOREGROUND_INTENSITY | BACKGROUND_INTENSITY)

WORD colorFG[]={//0¶Â1¬õ2ºñ3¶À4ÂÅ5µµ6«C7¥Õ
	0,
	FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};
WORD colorBG[]={//0¶Â1¬õ2ºñ3¶À4ÂÅ5µµ6«C7¥Õ
	0,
	BACKGROUND_RED,
	BACKGROUND_GREEN,
	BACKGROUND_RED | BACKGROUND_GREEN,
	BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
};

//ÃC¦â±±¨î
void textcolor(int attr, int fg, int bg){
	HANDLE test=GetStdHandle(STD_OUTPUT_HANDLE); //Get the Standard Ctrl of I/O
	SetConsoleTextAttribute (test, attr | colorFG[fg] | colorBG[bg]);
}

void title(void);//game start print
void gotoxy(int x, int y);//move pos(x,y)
void print_UI(int x,int y,int cx,int cy,char c[]);//UI design

//Part4
//menu
//Ref:http://oblivious9.pixnet.net/blog/post/198964978-c-%E6%94%94%E6%88%AA%E9%8D%B5%E7%9B%A4%E4%BA%8B%E4%BB%B6
//Virtual Key Ctrl Method

#define OFFSET_X 10
#define OFFSET_Y 0

#define CORNER_LEFT_UPPER_X 0+OFFSET_X
#define CORNER_LEFT_UPPER_Y 0+OFFSET_Y
#define CORNER_RIGHT_UPPER_X 21+OFFSET_X//total 62 units for wall_x,playground 60 
#define CORNER_RIGHT_UPPER_Y 00+OFFSET_Y
#define CORNER_LEFT_DOWN_X 0+OFFSET_X
#define CORNER_LEFT_DOWN_Y 41+OFFSET_Y//total 40 units for wall_y,playground 38
#define CORNER_RIGHT_DOWN_X 21+OFFSET_X
#define CORNER_RIGHT_DOWN_Y 41+OFFSET_Y

#define OFFSET_P2_X 40

#define CORNER_LEFT_UPPER_X2 0+OFFSET_X+OFFSET_P2_X
#define CORNER_LEFT_UPPER_Y2 0+OFFSET_Y
#define CORNER_RIGHT_UPPER_X2 21+OFFSET_X+OFFSET_P2_X//total 62 units for wall_x,playground 60 
#define CORNER_RIGHT_UPPER_Y2 00+OFFSET_Y
#define CORNER_LEFT_DOWN_X2 0+OFFSET_X+OFFSET_P2_X
#define CORNER_LEFT_DOWN_Y2 41+OFFSET_Y//total 40 units for wall_y,playground 38
#define CORNER_RIGHT_DOWN_X2 21+OFFSET_X+OFFSET_P2_X
#define CORNER_RIGHT_DOWN_Y2 41+OFFSET_Y

struct UI{

	int P1_icon_next_arr[5];
	int P1_hold;
	int P2_icon_next_arr[5];
	int P2_hold;

	void print(int x,int y,int cx,int cy,char *c){//pos(x,y),color(x,y),*char
		gotoxy(2*x,y);
		textcolor(TC_FG_INTENSIFY,cx,cy);
		printf("%s",c);
		dft();
	}
	void dft(void){//set as default color
		textcolor(TC_FG_INTENSIFY,7,0);
	}
	void init(void){
		print(CORNER_LEFT_UPPER_X,CORNER_LEFT_UPPER_Y,7,0,"¡´");//LU
		print(CORNER_RIGHT_UPPER_X,CORNER_RIGHT_UPPER_Y,7,0,"¡´");//RU
		print(CORNER_LEFT_DOWN_X,CORNER_LEFT_DOWN_Y,7,0,"¡´");//LD
		print(CORNER_RIGHT_DOWN_X,CORNER_RIGHT_DOWN_Y,7,0,"¡´");//RD
		//for(int counter = CORNER_LEFT_UPPER_X;counter < CORNER_RIGHT_UPPER_X;counter++)//top
		//print(counter,CORNER_LEFT_UPPER_Y,7,0,"¡´");
		for(int counter = CORNER_LEFT_DOWN_X;counter < CORNER_RIGHT_UPPER_X;counter++)//bottom
			print(counter,CORNER_LEFT_DOWN_Y,7,0,"¡´");
		for(int counter = CORNER_LEFT_UPPER_Y;counter < CORNER_LEFT_DOWN_Y;counter++)//left
			print(CORNER_LEFT_UPPER_X,counter,7,0,"¡´");
		for(int counter = CORNER_LEFT_UPPER_Y;counter < CORNER_LEFT_DOWN_Y;counter++)//right
			print(CORNER_RIGHT_UPPER_X,counter,7,0,"¡´");

		print(CORNER_LEFT_UPPER_X2,CORNER_LEFT_UPPER_Y2,7,0,"¡´");//LU
		print(CORNER_RIGHT_UPPER_X2,CORNER_RIGHT_UPPER_Y2,7,0,"¡´");//RU
		print(CORNER_LEFT_DOWN_X2,CORNER_LEFT_DOWN_Y2,7,0,"¡´");//LD
		print(CORNER_RIGHT_DOWN_X2,CORNER_RIGHT_DOWN_Y2,7,0,"¡´");//RD
		//for(int counter = CORNER_LEFT_UPPER_X;counter < CORNER_RIGHT_UPPER_X;counter++)//top
		//print(counter,CORNER_LEFT_UPPER_Y,7,0,"¡´");
		for(int counter = CORNER_LEFT_DOWN_X2;counter < CORNER_RIGHT_UPPER_X2;counter++)//bottom
			print(counter,CORNER_LEFT_DOWN_Y2,7,0,"¡´");
		for(int counter = CORNER_LEFT_UPPER_Y2;counter < CORNER_LEFT_DOWN_Y2;counter++)//left
			print(CORNER_LEFT_UPPER_X2,counter,7,0,"¡´");
		for(int counter = CORNER_LEFT_UPPER_Y2;counter < CORNER_LEFT_DOWN_Y2;counter++)//right
			print(CORNER_RIGHT_UPPER_X2,counter,7,0,"¡´");

		gotoxy(0,45);
	}
	void tetris_shadow(int x,int y,int style_fg,int style_bg){
		print(2*x+1+OFFSET_X,2*y+1,style_fg,style_bg,"¡@");
		print(2*x+2+OFFSET_X,2*y+1,style_fg,style_bg,"¡@");
		print(2*x+1+OFFSET_X,2*y+2,style_fg,style_bg,"¡@");
		print(2*x+2+OFFSET_X,2*y+2,style_fg,style_bg,"¡@");
	}
	void tetris_block(int x,int y,int style_fg,int style_bg){
		print(2*x+1+OFFSET_X,2*y+1,style_fg,style_bg,"¡½");
		print(2*x+2+OFFSET_X,2*y+1,style_fg,style_bg,"¡½");
		print(2*x+1+OFFSET_X,2*y+2,style_fg,style_bg,"¡½");
		print(2*x+2+OFFSET_X,2*y+2,style_fg,style_bg,"¡½");
	}
	void tetris_window(int x,int y){
		dft();

		print(x,y,7,0,"ùÝ");//LU
		print(x+5,y,7,0,"ùß");//RU
		print(x,y+5,7,0,"ùã");//LD
		print(x+5,y+5,7,0,"ùå");//RD

		for(int counter = x+1;counter < x+5;counter++)//top
			print(counter,y,7,0,"ùù");
		for(int counter = x+1;counter < x+5;counter++)//bottom
			print(counter,y+5,7,0,"ùù");
		for(int counter = y+1;counter < y+5;counter++)//left
			print(x,counter,7,0,"ùø");
		for(int counter = y+1;counter < y+5;counter++)//right
			print(x+5,counter,7,0,"ùø");
	}
	void P1_window(){
		print(4,1,7,0,"HOLD");
		print(36,1,7,0,"NEXT");
		tetris_window(2,2);
		tetris_window(34,2);
		tetris_window(34,8);
		tetris_window(34,14);
		tetris_window(34,20);
		tetris_window(34,26);
	}
	void P2_window(){
		print(4+OFFSET_P2_X,1,7,0,"HOLD");
		print(36+OFFSET_P2_X,1,7,0,"NEXT");
		tetris_window(2+OFFSET_P2_X,2);
		tetris_window(34+OFFSET_P2_X,2);
		tetris_window(34+OFFSET_P2_X,8);
		tetris_window(34+OFFSET_P2_X,14);
		tetris_window(34+OFFSET_P2_X,20);
		tetris_window(34+OFFSET_P2_X,26);
	}
	void icon_show(int x,int y,int blk_type){
		if(blk_type == 0){
			print(x,y+2,6,0,"¡½");
			print(x+1,y+2,6,0,"¡½");
			print(x+2,y+2,6,0,"¡½");
			print(x+3,y+2,6,0,"¡½");
		}else if(blk_type == 1){
			print(x+1,y+1,3,0,"¡½");
			print(x+2,y+1,3,0,"¡½");
			print(x+1,y+2,3,0,"¡½");
			print(x+2,y+2,3,0,"¡½");
		}else if(blk_type == 2){
			print(x+1,y+1,2,0,"¡½");
			print(x+1,y+2,2,0,"¡½");
			print(x+2,y+2,2,0,"¡½");
			print(x+2,y+3,2,0,"¡½");
		}else if(blk_type == 3){
			print(x+2,y+1,1,0,"¡½");
			print(x+1,y+2,1,0,"¡½");
			print(x+2,y+2,1,0,"¡½");
			print(x+1,y+3,1,0,"¡½");
		}else if(blk_type == 4){
			print(x+1,y+3,4,0,"¡½");
			print(x+2,y+1,4,0,"¡½");
			print(x+2,y+2,4,0,"¡½");
			print(x+2,y+3,4,0,"¡½");
		}else if(blk_type == 5){
			print(x+1,y+3,7,0,"¡½");
			print(x+1,y+1,7,0,"¡½");
			print(x+1,y+2,7,0,"¡½");
			print(x+2,y+3,7,0,"¡½");
		}else if(blk_type == 6){
			print(x+1,y+2,5,0,"¡½");
			print(x+2,y+1,5,0,"¡½");
			print(x+2,y+2,5,0,"¡½");
			print(x+2,y+3,5,0,"¡½");
		}
	}
	void icon_clear(int x,int y,int blk_type){
		if(blk_type == 0){
			print(x,y+2,6,0,"¡@");
			print(x+1,y+2,6,0,"¡@");
			print(x+2,y+2,6,0,"¡@");
			print(x+3,y+2,6,0,"¡@");
		}else if(blk_type == 1){
			print(x+1,y+1,3,0,"¡@");
			print(x+2,y+1,3,0,"¡@");
			print(x+1,y+2,3,0,"¡@");
			print(x+2,y+2,3,0,"¡@");
		}else if(blk_type == 2){
			print(x+1,y+1,2,0,"¡@");
			print(x+1,y+2,2,0,"¡@");
			print(x+2,y+2,2,0,"¡@");
			print(x+2,y+3,2,0,"¡@");
		}else if(blk_type == 3){
			print(x+2,y+1,1,0,"¡@");
			print(x+1,y+2,1,0,"¡@");
			print(x+2,y+2,1,0,"¡@");
			print(x+1,y+3,1,0,"¡@");
		}else if(blk_type == 4){
			print(x+1,y+3,4,0,"¡@");
			print(x+2,y+1,4,0,"¡@");
			print(x+2,y+2,4,0,"¡@");
			print(x+2,y+3,4,0,"¡@");
		}else if(blk_type == 5){
			print(x+1,y+3,7,0,"¡@");
			print(x+1,y+1,7,0,"¡@");
			print(x+1,y+2,7,0,"¡@");
			print(x+2,y+3,7,0,"¡@");
		}else if(blk_type == 6){
			print(x+1,y+2,5,0,"¡@");
			print(x+2,y+1,5,0,"¡@");
			print(x+2,y+2,5,0,"¡@");
			print(x+2,y+3,5,0,"¡@");
		}
	}

	void P1_icon_init(int n[]){
		for(int i=0;i<5;i++){
			P1_icon_next_arr[i] = n[i];
		}
		icon_show(35,3,P1_icon_next_arr[0]);
		icon_show(35,9,P1_icon_next_arr[1]);
		icon_show(35,15,P1_icon_next_arr[2]);
		icon_show(35,21,P1_icon_next_arr[3]);
		icon_show(35,27,P1_icon_next_arr[4]);
	}
	void P1_icon_next(int n[]){
		icon_clear(35,3,P1_icon_next_arr[0]);
		icon_clear(35,9,P1_icon_next_arr[1]);
		icon_clear(35,15,P1_icon_next_arr[2]);
		icon_clear(35,21,P1_icon_next_arr[3]);
		icon_clear(35,27,P1_icon_next_arr[4]);
		P1_icon_init(n);
	}
	int P1_isHold(void){
		if(P1_hold == 7)
			return 0;
		else
			return 1;
	}
	void P1_hold_init(){
		P1_hold = 7;
	}
	void P1_hold_next(int *n){
		if(P1_hold == 7){
			P1_hold = *n;
			icon_show(3,3,P1_hold);
		}		
	}
	void P1_hold_swap(int *n){
		icon_clear(3,3,P1_hold);
		int temp = *n;
		*n = P1_hold;
		P1_hold = temp;
		icon_show(3,3,P1_hold);
	}

	void P2_icon_init(int n[]){
		for(int i=0;i<5;i++){
			P2_icon_next_arr[i] = n[i];
		}
		icon_show(35+OFFSET_P2_X,3,P2_icon_next_arr[0]);
		icon_show(35+OFFSET_P2_X,9,P2_icon_next_arr[1]);
		icon_show(35+OFFSET_P2_X,15,P2_icon_next_arr[2]);
		icon_show(35+OFFSET_P2_X,21,P2_icon_next_arr[3]);
		icon_show(35+OFFSET_P2_X,27,P2_icon_next_arr[4]);
	}
	void P2_icon_next(int n[]){
		icon_clear(35+OFFSET_P2_X,3,P2_icon_next_arr[0]);
		icon_clear(35+OFFSET_P2_X,9,P2_icon_next_arr[1]);
		icon_clear(35+OFFSET_P2_X,15,P2_icon_next_arr[2]);
		icon_clear(35+OFFSET_P2_X,21,P2_icon_next_arr[3]);
		icon_clear(35+OFFSET_P2_X,27,P2_icon_next_arr[4]);
		P2_icon_init(n);
	}
	int P2_isHold(void){
		if(P2_hold == 7)
			return 0;
		else
			return 1;
	}
	void P2_hold_init(){
		P2_hold = 7;
	}
	void P2_hold_next(int *n){
		if(P2_hold == 7){
			P2_hold = *n;
			icon_show(3+OFFSET_P2_X,3,P2_hold);
		}		
	}
	void P2_hold_swap(int *n){
		icon_clear(3+OFFSET_P2_X,3,P2_hold);
		int temp = *n;
		*n = P2_hold;
		P2_hold = temp;
		icon_show(3+OFFSET_P2_X,3,P2_hold);
	}
	void result(int n){
		if(n == 0){
			print(15,15,7,0,"¡½");
		}
	}
}UI;

struct coord{//coordination
	int x;
	int y;
};

struct end_of_game1
{
	void title(void) {

		system("cls");
		textcolor(TC_FG_INTENSIFY, 7, 0);
		gotoxy(37, 6);
		printf("Winner is Server\n");
	}
}endgame1;

struct end_of_game2
{
	void title(void) {

		system("cls");
		textcolor(TC_FG_INTENSIFY, 7, 0);
		gotoxy(37, 6);
		printf("Winner is Client\n");
	}
}endgame2;

struct tetris{

	int score,KO;
	int gameOverFlag;
	char map_block[10][24];
	int endline;
	int lines;
	void init(void){
		score = 0;
		gameOverFlag = 0;
		for(int i=0;i<10;i++)
			for(int j=0;j<24;j++)
				map_block[i][j] = 'B';
	}
	int isOccupied(int x,int y){
		if(map_block[x][y+4] != 'B')
			return 1;
		else
			return 0;
	}
	void land(coord c[],char name){
		for(int i=0;i<=3;i++){
			map_block[c[i].x][c[i].y+4] = name;
		}
	}
	void map_print(void){
		for(int i=0;i<10;i++){
			for(int j=0;j<24;j++){
				if(map_block[i][j] == 'I'){
					UI.print(50+i,10+j,6,0,"¡½");
				}else if(map_block[i][j] == 'O'){
					UI.print(50+i,10+j,3,0,"¡½");
				}else if(map_block[i][j] == 'S'){
					UI.print(50+i,10+j,2,0,"¡½");
				}else if(map_block[i][j] == 'Z'){
					UI.print(50+i,10+j,1,0,"¡½");
				}else if(map_block[i][j] == 'J'){
					UI.print(50+i,10+j,4,0,"¡½");
				}else if(map_block[i][j] == 'L'){
					UI.print(50+i,10+j,7,0,"¡½");
				}else if(map_block[i][j] == 'T'){
					UI.print(50+i,10+j,5,0,"¡½");
				}else{
					UI.print(50+i,10+j,7,7,"  ");
		

				}				
			}

		}
	}
	int isGameOver(void){
		int num = 0;
		for(int i=0;i<10;i++)
			for(int j=0;j<4;j++)
				if(map_block[i][j]!='B')
					num++;
		if(num>=1){
			return 1;
			gameOverFlag = 1;
		}else
			return 0;
	}
	int isAnyLines(void){
		lines=0;
		for(int j=4;j<=23;j++){
			int blk=0;
			for(int i=0;i<=9;i++){
				if(map_block[i][j] != 'B')
					blk++;
			}
			if(blk==10){
				lines++;
				endline=j;//4 lines are reserved to be outside
			}
		}
		return lines;
	}
	void clearlines(void){
		for(int j=endline;j>=4;j--){
			for(int i=0;i<=9;i++){
				map_block[i][j]=map_block[i][j-lines];
			}
		}
	}
	void redraw(void){
		for(int i=0;i<10;i++){
			for(int j=4;j<=23;j++){
				if(map_block[i][j]=='I')
					UI.tetris_block(i,j-4,6,0);
				else if(map_block[i][j]=='O')
					UI.tetris_block(i,j-4,3,0);
				else if(map_block[i][j]=='S')
					UI.tetris_block(i,j-4,2,0);
				else if(map_block[i][j]=='Z')
					UI.tetris_block(i,j-4,1,0);
				else if(map_block[i][j]=='J')
					UI.tetris_block(i,j-4,4,0);
				else if(map_block[i][j]=='L')
					UI.tetris_block(i,j-4,7,0);
				else if(map_block[i][j]=='T')
					UI.tetris_block(i,j-4,5,0);
				else if(map_block[i][j]=='B')
					UI.tetris_shadow(i,j-4,0,0);
			}
		}
	}
	void score_print(void){
		score+=lines;
		lines=0;
		char s[10];
		if (score >= 30)
		{
			endgame2.title();
		}
		if (isGameOver())
		{
			KO++;
		}
		if (KO == 2)
		{
			endgame1.title();
		}
		else {
			sprintf(s, "%dKO", KO);
			UI.print(35 + OFFSET_P2_X, 41, 7, 0, s);
			sprintf(s, "%d LINES", score);
			UI.print(35, 40, 7, 0, s);
		}
		
	}
}P1;
struct tetris2{

	int score,KO;
	int gameOverFlag;
	char map_block[10][24];
	int endline;
	int lines;
	void init(void){
		gameOverFlag = 0;
		score = 0;
		for(int i=0;i<10;i++)
			for(int j=0;j<24;j++)
				map_block[i][j] = 'B';
	}
	int isOccupied(int x,int y){
		if(map_block[x][y+4] != 'B')
			return 1;
		else
			return 0;
	}
	void land(coord c[],char name){
		for(int i=0;i<=3;i++){
			map_block[c[i].x][c[i].y+4] = name;
		}
	}
	void map_print(void){
		for(int i=0;i<10;i++){
			for(int j=0;j<24;j++){
				if(map_block[i][j] == 'I'){
					UI.print(50+i,10+j,6,0,"¡½");
				}else if(map_block[i][j] == 'O'){
					UI.print(50+i,10+j,3,0,"¡½");
				}else if(map_block[i][j] == 'S'){
					UI.print(50+i,10+j,2,0,"¡½");
				}else if(map_block[i][j] == 'Z'){
					UI.print(50+i,10+j,1,0,"¡½");
				}else if(map_block[i][j] == 'J'){
					UI.print(50+i,10+j,4,0,"¡½");
				}else if(map_block[i][j] == 'L'){
					UI.print(50+i,10+j,7,0,"¡½");
				}else if(map_block[i][j] == 'T'){
					UI.print(50+i,10+j,5,0,"¡½");
				}else{
					UI.print(50+i,10+j,7,7,"  ");
					//char s[2];
					//sprintf(s,"%c",map_block[i][j]);
					//UI.print(50+i,10+j,7,0,s);

				}				
			}

		}
	}
	int isGameOver(void){
		int num = 0;
		for(int i=0;i<10;i++)
			for(int j=0;j<4;j++)
				if(map_block[i][j]!='B')
					num++;
		if(num>=1){
			return 1;
			gameOverFlag = 1;
		}else
			return 0;
	}
	int isAnyLines(void){
		lines=0;
		for(int j=4;j<=23;j++){
			int blk=0;
			for(int i=0;i<=9;i++){
				if(map_block[i][j] != 'B')
					blk++;
			}
			if(blk==10){
				lines++;
				endline=j;//4 lines are reserved to be outside
			}
		}
		return lines;
	}
	void clearlines(void){
		for(int j=endline;j>=4;j--){
			for(int i=0;i<=9;i++){
				map_block[i][j]=map_block[i][j-lines];
			}
		}
	}
	void redraw(void){
		for(int i=0;i<10;i++){
			for(int j=4;j<=23;j++){
				if(map_block[i][j]=='I')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,6,0);
				else if(map_block[i][j]=='O')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,3,0);
				else if(map_block[i][j]=='S')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,2,0);
				else if(map_block[i][j]=='Z')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,1,0);
				else if(map_block[i][j]=='J')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,4,0);
				else if(map_block[i][j]=='L')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,7,0);
				else if(map_block[i][j]=='T')
					UI.tetris_block(i+OFFSET_P2_X/2,j-4,5,0);
				else if(map_block[i][j]=='B')
					UI.tetris_shadow(i+OFFSET_P2_X/2,j-4,0,0);
			}
		}
	}
	void score_print(void){
		score+=lines;
		lines=0;
		char s[10];
		if (score >= 30)
		{
			endgame1.title();
		}
		if (isGameOver())
		{
			KO++;
		}
		if (KO == 2)
		{
			endgame2.title();
		}
		else {
			sprintf(s, "%dKO", KO);
			UI.print(35, 41, 7, 0, s);

			sprintf(s, "%d LINES", score);
			UI.print(35 + OFFSET_P2_X, 40, 7, 0, s);
		}
		
	}
}P2;


struct I{//1 for standing, while 2 for lying
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,6,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'I';
		form = 1;
		body[0].x = 5;
		body[0].y = -4;
		body[1].x = 5;
		body[1].y = -3;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 5;
		body[3].y = -1;
		findGoal();
		showGoal();
		show();
	}
	void init2(void){
		name = 'I';
		form = 2;
		body[0].x = 3;
		body[0].y = -1;
		body[1].x = 4;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -1;
		body[3].x = 6;
		body[3].y = -1;
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[3].x,body[3].y+1) == 1)
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1) == 1)
				return 1;
			else if(P1.isOccupied(body[1].x,body[1].y+1) == 1)
				return 1;
			else if(P1.isOccupied(body[2].x,body[2].y+1) == 1)
				return 1;
			else if(P1.isOccupied(body[3].x,body[3].y+1) == 1)
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y)==1)
					num++;
			}
			if(P1.isOccupied(body[3].x-1,body[3].y-1)==1)//if left down exists sth
				num++;
		}else if(form == 2){
			if(P1.isOccupied(body[0].x-1,body[0].y)==1)
				num++;
			if(P1.isOccupied(body[0].x-1,body[0].y-1)==1)//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&isLeftOccupied()==0){
			if(body[3].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&isLeftOccupied()==0){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y)==1)
					num++;
			}
			if(P1.isOccupied(body[3].x+1,body[3].y+1)==1)//if right down exists sth
				num++;
		}else if(form == 2){
			if(P1.isOccupied(body[3].x+1,body[3].y)==1)
				num++;
			if(P1.isOccupied(body[0].x+1,body[0].y+1)==1)//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&isRightOccupied()==0){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&isRightOccupied()==0){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[1].x <= 1){
				if(P1.isOccupied(0,body[1].y))
					num++;
				if(P1.isOccupied(1,body[1].y))
					num++;
				if(P1.isOccupied(2,body[1].y))
					num++;
				if(P1.isOccupied(3,body[1].y))
					num++;
			}else if(body[1].x >=7){
				if(P1.isOccupied(6,body[1].y))
					num++;
				if(P1.isOccupied(7,body[1].y))
					num++;
				if(P1.isOccupied(8,body[1].y))
					num++;
				if(P1.isOccupied(9,body[1].y))
					num++;
			}else{
				if(P1.isOccupied(body[1].x-1,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x+1,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x+2,body[1].y))
					num++;
			}
		}else if(form == 2){
			if(P1.isOccupied(body[1].x,body[1].y-1))
				num++;
			if(P1.isOccupied(body[1].x,body[1].y))
				num++;
			if(P1.isOccupied(body[1].x,body[1].y+1))
				num++;
			if(P1.isOccupied(body[1].x,body[1].y+2))
				num++;
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[1].x <= 1){
				body[0].x = 0;
				body[0].y = body[1].y;
				body[1].x = 1;
				body[1].y = body[1].y;
				body[2].x = 2;
				body[2].y = body[1].y;
				body[3].x = 3;
				body[3].y = body[1].y;
			}else if(body[1].x >=7){
				body[0].x = 6;
				body[0].y = body[1].y;
				body[1].x = 7;
				body[1].y = body[1].y;
				body[2].x = 8;
				body[2].y = body[1].y;
				body[3].x = 9;
				body[3].y = body[1].y;
			}else{
				body[0].x = body[1].x-1;
				body[0].y = body[1].y;
				body[1].x = body[1].x;
				body[1].y = body[1].y;
				body[2].x = body[1].x+1;
				body[2].y = body[1].y;
				body[3].x = body[1].x+2;
				body[3].y = body[1].y;
			}
		}else if(form == 2){
			form = 1;
			body[0].x = body[1].x;
			body[0].y = body[1].y-1;
			body[1].x = body[1].x;
			body[1].y = body[1].y;
			body[2].x = body[1].x;
			body[2].y = body[1].y+1;
			body[3].x = body[1].x;
			body[3].y = body[1].y+2;
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[3].x,c[3].y+1) == 1)
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1) == 1)
				return 1;
			else if(P1.isOccupied(c[1].x,c[1].y+1) == 1)
				return 1;
			else if(P1.isOccupied(c[2].x,c[2].y+1) == 1)
				return 1;
			else if(P1.isOccupied(c[3].x,c[3].y+1) == 1)
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}I;
struct O{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,3,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){//form is always 1
		name = 'O';
		form = 1;
		body[0].x = 5;
		body[0].y = -2;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 6;
		body[2].y = -1;
		body[3].x = 6;
		body[3].y = -2;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[1].y == 19||body[2].y == 19)
				return 1;
			else if(P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[3].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[2].x+1,body[2].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&isRightOccupied()==0){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[1].y == 19||c[2].y == 19)
				return 1;
			else if(P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}O;
struct S{//1 for lying, while 2 for standing
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,2,0);
		}
	}
	void clear(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'S';
		form = 1;
		body[0].x = 4;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 6;
		body[3].y = -2;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			if(P1.isOccupied(body[0].x-1,body[0].y)==1)
				num++;
			if(P1.isOccupied(body[0].x-1,body[0].y-1)||P1.isOccupied(body[2].x-1,body[2].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x+1,body[1].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 8){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[1].x <= 1){
				if(P1.isOccupied(1,body[1].y+1))
					num++;
				if(P1.isOccupied(1,body[1].y))
					num++;
				if(P1.isOccupied(0,body[1].y))
					num++;
				if(P1.isOccupied(0,body[1].y-1))
					num++;
			}else if(body[1].x >=8){
				if(P1.isOccupied(9,body[1].y+1))
					num++;
				if(P1.isOccupied(9,body[1].y))
					num++;
				if(P1.isOccupied(8,body[1].y))
					num++;
				if(P1.isOccupied(8,body[1].y-1))
					num++;
			}else{
				if(P1.isOccupied(body[1].x,body[1].y+1))
					num++;
				if(P1.isOccupied(body[1].x,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x-1,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x-1,body[1].y-1))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P1.isOccupied(0,body[2].y+1))
					num++;
				if(P1.isOccupied(1,body[2].y+1))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(2,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(7,body[2].y+1))
					num++;
				if(P1.isOccupied(8,body[2].y+1))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
			}else{
				if(P1.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[1].x <= 1){
				body[0].x = 1;
				body[0].y = body[1].y+1;
				body[1].x = 1;
				body[1].y = body[1].y;
				body[2].x = 0;
				body[2].y = body[1].y;
				body[3].x = 0;
				body[3].y = body[1].y-1;
			}else if(body[1].x >=7){
				body[0].x = 9;
				body[0].y = body[1].y+1;
				body[1].x = 9;
				body[1].y = body[1].y;
				body[2].x = 8;
				body[2].y = body[1].y;
				body[3].x = 8;
				body[3].y = body[1].y-1;
			}else{
				body[0].x = body[1].x;
				body[0].y = body[1].y+1;
				body[1].x = body[1].x;
				body[1].y = body[1].y;
				body[2].x = body[1].x-1;
				body[2].y = body[1].y;
				body[3].x = body[1].x-1;
				body[3].y = body[1].y-1;
			}
		}else if(form == 2){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y+1;
				body[1].x = 1;
				body[1].y = body[2].y+1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 2;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 7;
				body[0].y = body[2].y+1;
				body[1].x = 8;
				body[1].y = body[2].y+1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x+1;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x+1;
				body[2].y = body[2].y;
				body[3].x = body[2].x+1;
				body[3].y = body[2].y;
			}
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}S;
struct Z{//1 for lying, while 2 for standing
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,1,0);
		}
	}
	void clear(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'Z';
		form = 1;
		body[0].x = 6;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 4;
		body[3].y = -2;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[3].x-1,body[3].y-1)||P1.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[1].x <= 1){
				if(P1.isOccupied(0,body[1].y+1))
					num++;
				if(P1.isOccupied(0,body[1].y))
					num++;
				if(P1.isOccupied(1,body[1].y))
					num++;
				if(P1.isOccupied(1,body[1].y-1))
					num++;
			}else if(body[1].x >=8){
				if(P1.isOccupied(8,body[1].y+1))
					num++;
				if(P1.isOccupied(8,body[1].y))
					num++;
				if(P1.isOccupied(9,body[1].y))
					num++;
				if(P1.isOccupied(9,body[1].y-1))
					num++;
			}else{
				if(P1.isOccupied(body[1].x,body[1].y+1))
					num++;
				if(P1.isOccupied(body[1].x,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x+1,body[1].y))
					num++;
				if(P1.isOccupied(body[1].x+1,body[1].y-1))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P1.isOccupied(2,body[2].y+1))
					num++;
				if(P1.isOccupied(1,body[2].y+1))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(9,body[2].y+1))
					num++;
				if(P1.isOccupied(8,body[2].y+1))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(7,body[2].y))
					num++;
			}else{
				if(P1.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[1].x <= 1){
				body[0].x = 0;
				body[0].y = body[1].y+1;
				body[1].x = 0;
				body[1].y = body[1].y;
				body[2].x = 1;
				body[2].y = body[1].y;
				body[3].x = 1;
				body[3].y = body[1].y-1;
			}else if(body[1].x >=7){
				body[0].x = 8;
				body[0].y = body[1].y+1;
				body[1].x = 8;
				body[1].y = body[1].y;
				body[2].x = 9;
				body[2].y = body[1].y;
				body[3].x = 9;
				body[3].y = body[1].y-1;
			}else{
				body[0].x = body[1].x;
				body[0].y = body[1].y+1;
				body[1].x = body[1].x;
				body[1].y = body[1].y;
				body[2].x = body[1].x+1;
				body[2].y = body[1].y;
				body[3].x = body[1].x+1;
				body[3].y = body[1].y-1;
			}
		}else if(form == 2){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 2;
				body[0].y = body[2].y+1;
				body[1].x = 1;
				body[1].y = body[2].y+1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y+1;
				body[1].x = 8;
				body[1].y = body[2].y+1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 7;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x-1;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x-1;
				body[2].y = body[2].y;
				body[3].x = body[2].x-1;
				body[3].y = body[2].y;
			}
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}Z;
struct J{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,4,0);
		}
	}
	void clear(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'J';
		form = 1;
		body[0].x = 4;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 5;
		body[3].y = -3;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[1].x,body[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[2].x,body[2].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(body[1].y == 19||body[2].y == 19||body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[2].x,body[2].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1)||P1.isOccupied(body[1].x-1,body[1].y-1)||P1.isOccupied(body[2].x-1,body[2].y-1)||P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x-1,body[1].y-1)||P1.isOccupied(body[2].x-1,body[2].y-1)||P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 3&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 4&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1))//if right down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x+1,body[1].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 3&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 4&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[2].x <= 1){
				if(P1.isOccupied(2,body[2].y+1))
					num++;
				if(P1.isOccupied(2,body[2].y))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(9,body[2].y+1))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(7,body[2].y))
					num++;
			}else{
				if(P1.isOccupied(body[2].x+1,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P1.isOccupied(1,body[2].y-1))
					num++;
				if(P1.isOccupied(0,body[2].y-1))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
				if(P1.isOccupied(0,body[2].y+1))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(9,body[2].y-1))
					num++;
				if(P1.isOccupied(8,body[2].y-1))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(8,body[2].y+1))
					num++;
			}else{
				if(P1.isOccupied(body[2].x+1,body[2].y-1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y-1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y+1))
					num++;
			}
		}else if(form == 3){
			if(body[2].x <= 1){
				if(P1.isOccupied(0,body[2].y-1))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(2,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(7,body[2].y-1))
					num++;
				if(P1.isOccupied(7,body[2].y))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
			}else{
				if(P1.isOccupied(body[2].x-1,body[2].y-1))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y))
					num++;
			}
		}else if(form == 4){
			if(body[2].x <= 1){
				if(P1.isOccupied(0,body[2].y+1))
					num++;
				if(P1.isOccupied(1,body[2].y+1))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(1,body[2].y-1))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(8,body[2].y+1))
					num++;
				if(P1.isOccupied(9,body[2].y+1))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
				if(P1.isOccupied(9,body[2].y-1))
					num++;
			}else{
				if(P1.isOccupied(body[2].x-1,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y-1))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[2].x <= 1){
				body[0].x = 2;
				body[0].y = body[2].y+1;
				body[1].x = 2;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y;
			}else if(body[2].x >=7){
				body[0].x = 9;
				body[0].y = body[2].y+1;
				body[1].x = 9;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 7;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x+1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x-1;
				body[3].y = body[2].y;
			}
		}else if(form == 2){
			form = 3;
			if(body[2].x <= 1){
				body[0].x = 1;
				body[0].y = body[2].y-1;
				body[1].x = 0;
				body[1].y = body[2].y-1;
				body[2].x = 0;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y+1;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y-1;
				body[1].x = 8;
				body[1].y = body[2].y-1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 8;
				body[3].y = body[2].y+1;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x;
				body[1].y = body[2].y-1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y+1;
			}
		}else if(form == 3){
			form = 4;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y-1;
				body[1].x = 0;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 2;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 7;
				body[0].y = body[2].y-1;
				body[1].x = 7;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x-1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x+1;
				body[3].y = body[2].y;
			}
		}else if(form == 4){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y+1;
				body[1].x = 1;
				body[1].y = body[2].y+1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 1;
				body[3].y = body[2].y-1;
			}else if(body[2].x >= 8){
				body[0].x = 8;
				body[0].y = body[2].y+1;
				body[1].x = 9;
				body[1].y = body[2].y+1;
				body[2].x = 9;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y-1;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y-1;
			}
		}
		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[1].x,c[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[2].x,c[2].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(c[1].y == 19||c[2].y == 19||c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[2].x,c[2].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}J;
struct L{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,7,0);
		}
	}
	void clear(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'L';
		form = 1;
		body[0].x = 6;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 5;
		body[3].y = -3;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[1].x,body[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[2].x,body[2].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(body[1].y == 19||body[2].y == 19||body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[2].x,body[2].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1)||P1.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x-1,body[0].y-1)||P1.isOccupied(body[2].x-1,body[2].y-1)||P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x-1,body[1].y-1)||P1.isOccupied(body[2].x-1,body[2].y-1)||P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 3&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 4&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x+1,body[1].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[0].x+1,body[0].y+1)||P1.isOccupied(body[1].x+1,body[1].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 3&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 4&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[2].x <= 1){
				if(P1.isOccupied(0,body[2].y+1))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(2,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(7,body[2].y+1))
					num++;
				if(P1.isOccupied(7,body[2].y))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
			}else{
				if(P1.isOccupied(body[2].x-1,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P1.isOccupied(0,body[2].y-1))
					num++;
				if(P1.isOccupied(1,body[2].y-1))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(1,body[2].y+1))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(8,body[2].y-1))
					num++;
				if(P1.isOccupied(9,body[2].y-1))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
				if(P1.isOccupied(9,body[2].y+1))
					num++;
			}else{
				if(P1.isOccupied(body[2].x-1,body[2].y-1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y-1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y+1))
					num++;
			}
		}else if(form == 3){
			if(body[2].x <= 1){
				if(P1.isOccupied(2,body[2].y-1))
					num++;
				if(P1.isOccupied(2,body[2].y))
					num++;
				if(P1.isOccupied(1,body[2].y))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(9,body[2].y-1))
					num++;
				if(P1.isOccupied(9,body[2].y))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(7,body[2].y))
					num++;
			}else{
				if(P1.isOccupied(body[2].x+1,body[2].y-1))
					num++;
				if(P1.isOccupied(body[2].x+1,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x-1,body[2].y))
					num++;
			}
		}else if(form == 4){
			if(body[2].x <= 1){
				if(P1.isOccupied(1,body[2].y+1))
					num++;
				if(P1.isOccupied(0,body[2].y+1))
					num++;
				if(P1.isOccupied(0,body[2].y))
					num++;
				if(P1.isOccupied(0,body[2].y-1))
					num++;
			}else if(body[2].x >=8){
				if(P1.isOccupied(9,body[2].y+1))
					num++;
				if(P1.isOccupied(8,body[2].y+1))
					num++;
				if(P1.isOccupied(8,body[2].y))
					num++;
				if(P1.isOccupied(8,body[2].y-1))
					num++;
			}else{
				if(P1.isOccupied(body[2].x+1,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y))
					num++;
				if(P1.isOccupied(body[2].x,body[2].y-1))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y+1;
				body[1].x = 0;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 2;
				body[3].y = body[2].y;
			}else if(body[2].x >=7){
				body[0].x = 7;
				body[0].y = body[2].y+1;
				body[1].x = 7;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x-1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x+1;
				body[3].y = body[2].y;
			}
		}else if(form == 2){
			form = 3;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y-1;
				body[1].x = 1;
				body[1].y = body[2].y-1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 1;
				body[3].y = body[2].y+1;
			}else if(body[2].x >= 8){
				body[0].x = 8;
				body[0].y = body[2].y-1;
				body[1].x = 9;
				body[1].y = body[2].y-1;
				body[2].x = 9;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y+1;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x;
				body[1].y = body[2].y-1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y+1;
			}
		}else if(form == 3){
			form = 4;
			if(body[2].x <= 1){
				body[0].x = 2;
				body[0].y = body[2].y-1;
				body[1].x = 2;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y-1;
				body[1].x = 9;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 7;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x+1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x-1;
				body[3].y = body[2].y;
			}
		}else if(form == 4){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 1;
				body[0].y = body[2].y+1;
				body[1].x = 0;
				body[1].y = body[2].y+1;
				body[2].x = 0;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y-1;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y+1;
				body[1].x = 8;
				body[1].y = body[2].y+1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 8;
				body[3].y = body[2].y-1;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y-1;
			}
		}
		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[1].x,c[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[2].x,c[2].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(c[1].y == 19||c[2].y == 19||c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[2].x,c[2].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}L;
struct T{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x,body[i].y,5,0);
		}
	}
	void clear(void){//no need to modify
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'T';
		form = 1;
		body[0].x = 5;
		body[0].y = -1;
		body[1].x = 4;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 6;
		body[3].y = -1;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19||body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[0].x,body[0].y+1)||P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[1].y == 19)
				return 1;
			else if(P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(body[2].y == 19)
				return 1;
			else if(P1.isOccupied(body[1].x,body[1].y+1)||P1.isOccupied(body[2].x,body[2].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(body[3].y == 19)
				return 1;
			else if(P1.isOccupied(body[2].x,body[2].y+1)||P1.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x-1,body[1].y-1)||P1.isOccupied(body[2].x-1,body[2].y-1))//if left down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[2].x-1,body[2].y-1)||P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){
				if(P1.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 3&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 4&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[1].x+1,body[1].y+1)||P1.isOccupied(body[2].x+1,body[2].y+1))//if right down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P1.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P1.isOccupied(body[2].x+1,body[2].y+1)||P1.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 3&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 4&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[0].x <= 1){
				if(P1.isOccupied(1,body[0].y))
					num++;
				if(P1.isOccupied(1,body[0].y+1))
					num++;
				if(P1.isOccupied(0,body[0].y))
					num++;
				if(P1.isOccupied(1,body[0].y-1))
					num++;
			}else if(body[0].x >=8){
				if(P1.isOccupied(9,body[0].y))
					num++;
				if(P1.isOccupied(9,body[0].y+1))
					num++;
				if(P1.isOccupied(8,body[0].y))
					num++;
				if(P1.isOccupied(9,body[0].y-1))
					num++;
			}else{
				if(P1.isOccupied(body[0].x,body[0].y+1))
					num++;
			}
		}else if(form == 2){
			if(body[0].x <= 1){
				if(P1.isOccupied(1,body[0].y))
					num++;
				if(P1.isOccupied(2,body[0].y))
					num++;
				if(P1.isOccupied(1,body[0].y+1))
					num++;
				if(P1.isOccupied(0,body[0].y))
					num++;
			}else if(body[0].x >=8){
				if(P1.isOccupied(8,body[0].y))
					num++;
				if(P1.isOccupied(9,body[0].y))
					num++;
				if(P1.isOccupied(8,body[0].y+1))
					num++;
				if(P1.isOccupied(7,body[0].y))
					num++;
			}else{
				if(P1.isOccupied(body[0].x+1,body[0].y))
					num++;
			}
		}else if(form == 3){
			if(body[0].x <= 1){
				if(P1.isOccupied(0,body[0].y))
					num++;
				if(P1.isOccupied(0,body[0].y-1))
					num++;
				if(P1.isOccupied(1,body[0].y))
					num++;
				if(P1.isOccupied(0,body[0].y+1))
					num++;
			}else if(body[0].x >=8){
				if(P1.isOccupied(8,body[0].y))
					num++;
				if(P1.isOccupied(8,body[0].y-1))
					num++;
				if(P1.isOccupied(9,body[0].y))
					num++;
				if(P1.isOccupied(8,body[0].y+1))
					num++;
			}else{
				if(P1.isOccupied(body[0].x,body[0].y-1))
					num++;
			}
		}else if(form == 4){
			if(body[0].x <= 1){
				if(P1.isOccupied(1,body[0].y))
					num++;
				if(P1.isOccupied(0,body[0].y))
					num++;
				if(P1.isOccupied(1,body[0].y-1))
					num++;
				if(P1.isOccupied(2,body[0].y))
					num++;
			}else if(body[0].x >=8){
				if(P1.isOccupied(8,body[0].y))
					num++;
				if(P1.isOccupied(7,body[0].y))
					num++;
				if(P1.isOccupied(8,body[0].y-1))
					num++;
				if(P1.isOccupied(9,body[0].y))
					num++;
			}else{
				if(P1.isOccupied(body[0].x-1,body[0].y))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[0].x <= 1){
				body[0].x = 1;
				body[0].y = body[0].y;
				body[1].x = 1;
				body[1].y = body[0].y+1;
				body[2].x = 0;
				body[2].y = body[0].y;
				body[3].x = 1;
				body[3].y = body[0].y-1;
			}else if(body[0].x >=8){
				body[0].x = 9;
				body[0].y = body[0].y;
				body[1].x = 9;
				body[1].y = body[0].y+1;
				body[2].x = 8;
				body[2].y = body[0].y;
				body[3].x = 9;
				body[3].y = body[0].y-1;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x;
				body[1].y = body[0].y+1;
			}
		}else if(form == 2){
			form = 3;
			if(body[0].x <= 1){
				body[0].x = 1;
				body[0].y = body[0].y;
				body[1].x = 2;
				body[1].y = body[0].y;
				body[2].x = 1;
				body[2].y = body[0].y+1;
				body[3].x = 0;
				body[3].y = body[0].y;
			}else if(body[0].x >= 8){
				body[0].x = 8;
				body[0].y = body[0].y;
				body[1].x = 9;
				body[1].y = body[0].y;
				body[2].x = 8;
				body[2].y = body[0].y+1;
				body[3].x = 7;
				body[3].y = body[0].y;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x+1;
				body[1].y = body[0].y;
			}
		}else if(form == 3){
			form = 4;
			if(body[0].x <= 1){
				body[0].x = 0;
				body[0].y = body[0].y;
				body[1].x = 0;
				body[1].y = body[0].y-1;
				body[2].x = 1;
				body[2].y = body[0].y;
				body[3].x = 0;
				body[3].y = body[0].y+1;
			}else if(body[0].x >= 8){
				body[0].x = 8;
				body[0].y = body[0].y;
				body[1].x = 8;
				body[1].y = body[0].y-1;
				body[2].x = 9;
				body[2].y = body[0].y;
				body[3].x = 8;
				body[3].y = body[0].y+1;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x;
				body[1].y = body[0].y-1;
			}
		}else if(form == 4){
			form = 1;
			if(body[0].x <= 1){
				body[0].x = 1;
				body[0].y = body[0].y;
				body[1].x = 0;
				body[1].y = body[0].y;
				body[2].x = 1;
				body[2].y = body[0].y-1;
				body[3].x = 2;
				body[3].y = body[0].y;
			}else if(body[0].x >= 8){
				body[0].x = 8;
				body[0].y = body[0].y;
				body[1].x = 7;
				body[1].y = body[0].y;
				body[2].x = 8;
				body[2].y = body[0].y-1;
				body[3].x = 9;
				body[3].y = body[0].y;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x-1;
				body[1].y = body[0].y;
			}
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19||c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[0].x,c[0].y+1)||P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[1].y == 19)
				return 1;
			else if(P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(c[2].y == 19)
				return 1;
			else if(P1.isOccupied(c[1].x,c[1].y+1)||P1.isOccupied(c[2].x,c[2].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(c[3].y == 19)
				return 1;
			else if(P1.isOccupied(c[2].x,c[2].y+1)||P1.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}T;

struct I2{//1 for standing, while 2 for lying
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,6,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'I';
		form = 1;
		body[0].x = 5;
		body[0].y = -4;
		body[1].x = 5;
		body[1].y = -3;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 5;
		body[3].y = -1;
		findGoal();
		showGoal();
		show();
	}
	void init2(void){
		name = 'I';
		form = 2;
		body[0].x = 3;
		body[0].y = -1;
		body[1].x = 4;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -1;
		body[3].x = 6;
		body[3].y = -1;
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[3].x,body[3].y+1) == 1)
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1) == 1)
				return 1;
			else if(P2.isOccupied(body[1].x,body[1].y+1) == 1)
				return 1;
			else if(P2.isOccupied(body[2].x,body[2].y+1) == 1)
				return 1;
			else if(P2.isOccupied(body[3].x,body[3].y+1) == 1)
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y)==1)
					num++;
			}
			if(P2.isOccupied(body[3].x-1,body[3].y-1)==1)//if left down exists sth
				num++;
		}else if(form == 2){
			if(P2.isOccupied(body[0].x-1,body[0].y)==1)
				num++;
			if(P2.isOccupied(body[0].x-1,body[0].y-1)==1)//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&isLeftOccupied()==0){
			if(body[3].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&isLeftOccupied()==0){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y)==1)
					num++;
			}
			if(P2.isOccupied(body[3].x+1,body[3].y+1)==1)//if right down exists sth
				num++;
		}else if(form == 2){
			if(P2.isOccupied(body[3].x+1,body[3].y)==1)
				num++;
			if(P2.isOccupied(body[0].x+1,body[0].y+1)==1)//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&isRightOccupied()==0){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&isRightOccupied()==0){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[1].x <= 1){
				if(P2.isOccupied(0,body[1].y))
					num++;
				if(P2.isOccupied(1,body[1].y))
					num++;
				if(P2.isOccupied(2,body[1].y))
					num++;
				if(P2.isOccupied(3,body[1].y))
					num++;
			}else if(body[1].x >=7){
				if(P2.isOccupied(6,body[1].y))
					num++;
				if(P2.isOccupied(7,body[1].y))
					num++;
				if(P2.isOccupied(8,body[1].y))
					num++;
				if(P2.isOccupied(9,body[1].y))
					num++;
			}else{
				if(P2.isOccupied(body[1].x-1,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x+1,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x+2,body[1].y))
					num++;
			}
		}else if(form == 2){
			if(P2.isOccupied(body[1].x,body[1].y-1))
				num++;
			if(P2.isOccupied(body[1].x,body[1].y))
				num++;
			if(P2.isOccupied(body[1].x,body[1].y+1))
				num++;
			if(P2.isOccupied(body[1].x,body[1].y+2))
				num++;
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[1].x <= 1){
				body[0].x = 0;
				body[0].y = body[1].y;
				body[1].x = 1;
				body[1].y = body[1].y;
				body[2].x = 2;
				body[2].y = body[1].y;
				body[3].x = 3;
				body[3].y = body[1].y;
			}else if(body[1].x >=7){
				body[0].x = 6;
				body[0].y = body[1].y;
				body[1].x = 7;
				body[1].y = body[1].y;
				body[2].x = 8;
				body[2].y = body[1].y;
				body[3].x = 9;
				body[3].y = body[1].y;
			}else{
				body[0].x = body[1].x-1;
				body[0].y = body[1].y;
				body[1].x = body[1].x;
				body[1].y = body[1].y;
				body[2].x = body[1].x+1;
				body[2].y = body[1].y;
				body[3].x = body[1].x+2;
				body[3].y = body[1].y;
			}
		}else if(form == 2){
			form = 1;
			body[0].x = body[1].x;
			body[0].y = body[1].y-1;
			body[1].x = body[1].x;
			body[1].y = body[1].y;
			body[2].x = body[1].x;
			body[2].y = body[1].y+1;
			body[3].x = body[1].x;
			body[3].y = body[1].y+2;
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[3].x,c[3].y+1) == 1)
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1) == 1)
				return 1;
			else if(P2.isOccupied(c[1].x,c[1].y+1) == 1)
				return 1;
			else if(P2.isOccupied(c[2].x,c[2].y+1) == 1)
				return 1;
			else if(P2.isOccupied(c[3].x,c[3].y+1) == 1)
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}I2;
struct O2{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,3,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){//form is always 1
		name = 'O';
		form = 1;
		body[0].x = 5;
		body[0].y = -2;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 6;
		body[2].y = -1;
		body[3].x = 6;
		body[3].y = -2;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[1].y == 19||body[2].y == 19)
				return 1;
			else if(P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[3].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[2].x+1,body[2].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&isRightOccupied()==0){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[1].y == 19||c[2].y == 19)
				return 1;
			else if(P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}O2;
struct S2{//1 for lying, while 2 for standing
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,2,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'S';
		form = 1;
		body[0].x = 4;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 6;
		body[3].y = -2;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			if(P2.isOccupied(body[0].x-1,body[0].y)==1)
				num++;
			if(P2.isOccupied(body[0].x-1,body[0].y-1)||P2.isOccupied(body[2].x-1,body[2].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x+1,body[1].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 8){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[1].x <= 1){
				if(P2.isOccupied(1,body[1].y+1))
					num++;
				if(P2.isOccupied(1,body[1].y))
					num++;
				if(P2.isOccupied(0,body[1].y))
					num++;
				if(P2.isOccupied(0,body[1].y-1))
					num++;
			}else if(body[1].x >=8){
				if(P2.isOccupied(9,body[1].y+1))
					num++;
				if(P2.isOccupied(9,body[1].y))
					num++;
				if(P2.isOccupied(8,body[1].y))
					num++;
				if(P2.isOccupied(8,body[1].y-1))
					num++;
			}else{
				if(P2.isOccupied(body[1].x,body[1].y+1))
					num++;
				if(P2.isOccupied(body[1].x,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x-1,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x-1,body[1].y-1))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P2.isOccupied(0,body[2].y+1))
					num++;
				if(P2.isOccupied(1,body[2].y+1))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(2,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(7,body[2].y+1))
					num++;
				if(P2.isOccupied(8,body[2].y+1))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
			}else{
				if(P2.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[1].x <= 1){
				body[0].x = 1;
				body[0].y = body[1].y+1;
				body[1].x = 1;
				body[1].y = body[1].y;
				body[2].x = 0;
				body[2].y = body[1].y;
				body[3].x = 0;
				body[3].y = body[1].y-1;
			}else if(body[1].x >=7){
				body[0].x = 9;
				body[0].y = body[1].y+1;
				body[1].x = 9;
				body[1].y = body[1].y;
				body[2].x = 8;
				body[2].y = body[1].y;
				body[3].x = 8;
				body[3].y = body[1].y-1;
			}else{
				body[0].x = body[1].x;
				body[0].y = body[1].y+1;
				body[1].x = body[1].x;
				body[1].y = body[1].y;
				body[2].x = body[1].x-1;
				body[2].y = body[1].y;
				body[3].x = body[1].x-1;
				body[3].y = body[1].y-1;
			}
		}else if(form == 2){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y+1;
				body[1].x = 1;
				body[1].y = body[2].y+1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 2;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 7;
				body[0].y = body[2].y+1;
				body[1].x = 8;
				body[1].y = body[2].y+1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x+1;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x+1;
				body[2].y = body[2].y;
				body[3].x = body[2].x+1;
				body[3].y = body[2].y;
			}
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}S2;
struct Z2{//1 for lying, while 2 for standing
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,1,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'Z';
		form = 1;
		body[0].x = 6;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 4;
		body[3].y = -2;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[3].x-1,body[3].y-1)||P2.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[1].x <= 1){
				if(P2.isOccupied(0,body[1].y+1))
					num++;
				if(P2.isOccupied(0,body[1].y))
					num++;
				if(P2.isOccupied(1,body[1].y))
					num++;
				if(P2.isOccupied(1,body[1].y-1))
					num++;
			}else if(body[1].x >=8){
				if(P2.isOccupied(8,body[1].y+1))
					num++;
				if(P2.isOccupied(8,body[1].y))
					num++;
				if(P2.isOccupied(9,body[1].y))
					num++;
				if(P2.isOccupied(9,body[1].y-1))
					num++;
			}else{
				if(P2.isOccupied(body[1].x,body[1].y+1))
					num++;
				if(P2.isOccupied(body[1].x,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x+1,body[1].y))
					num++;
				if(P2.isOccupied(body[1].x+1,body[1].y-1))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P2.isOccupied(2,body[2].y+1))
					num++;
				if(P2.isOccupied(1,body[2].y+1))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(9,body[2].y+1))
					num++;
				if(P2.isOccupied(8,body[2].y+1))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(7,body[2].y))
					num++;
			}else{
				if(P2.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[1].x <= 1){
				body[0].x = 0;
				body[0].y = body[1].y+1;
				body[1].x = 0;
				body[1].y = body[1].y;
				body[2].x = 1;
				body[2].y = body[1].y;
				body[3].x = 1;
				body[3].y = body[1].y-1;
			}else if(body[1].x >=7){
				body[0].x = 8;
				body[0].y = body[1].y+1;
				body[1].x = 8;
				body[1].y = body[1].y;
				body[2].x = 9;
				body[2].y = body[1].y;
				body[3].x = 9;
				body[3].y = body[1].y-1;
			}else{
				body[0].x = body[1].x;
				body[0].y = body[1].y+1;
				body[1].x = body[1].x;
				body[1].y = body[1].y;
				body[2].x = body[1].x+1;
				body[2].y = body[1].y;
				body[3].x = body[1].x+1;
				body[3].y = body[1].y-1;
			}
		}else if(form == 2){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 2;
				body[0].y = body[2].y+1;
				body[1].x = 1;
				body[1].y = body[2].y+1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y+1;
				body[1].x = 8;
				body[1].y = body[2].y+1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 7;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x-1;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x-1;
				body[2].y = body[2].y;
				body[3].x = body[2].x-1;
				body[3].y = body[2].y;
			}
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}Z2;
struct J2{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,4,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'J';
		form = 1;
		body[0].x = 4;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 5;
		body[3].y = -3;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[1].x,body[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[2].x,body[2].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(body[1].y == 19||body[2].y == 19||body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[2].x,body[2].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1)||P2.isOccupied(body[1].x-1,body[1].y-1)||P2.isOccupied(body[2].x-1,body[2].y-1)||P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x-1,body[1].y-1)||P2.isOccupied(body[2].x-1,body[2].y-1)||P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 3&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 4&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1))//if right down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x+1,body[1].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 3&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 4&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[2].x <= 1){
				if(P2.isOccupied(2,body[2].y+1))
					num++;
				if(P2.isOccupied(2,body[2].y))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(9,body[2].y+1))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(7,body[2].y))
					num++;
			}else{
				if(P2.isOccupied(body[2].x+1,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P2.isOccupied(1,body[2].y-1))
					num++;
				if(P2.isOccupied(0,body[2].y-1))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
				if(P2.isOccupied(0,body[2].y+1))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(9,body[2].y-1))
					num++;
				if(P2.isOccupied(8,body[2].y-1))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(8,body[2].y+1))
					num++;
			}else{
				if(P2.isOccupied(body[2].x+1,body[2].y-1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y-1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y+1))
					num++;
			}
		}else if(form == 3){
			if(body[2].x <= 1){
				if(P2.isOccupied(0,body[2].y-1))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(2,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(7,body[2].y-1))
					num++;
				if(P2.isOccupied(7,body[2].y))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
			}else{
				if(P2.isOccupied(body[2].x-1,body[2].y-1))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y))
					num++;
			}
		}else if(form == 4){
			if(body[2].x <= 1){
				if(P2.isOccupied(0,body[2].y+1))
					num++;
				if(P2.isOccupied(1,body[2].y+1))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(1,body[2].y-1))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(8,body[2].y+1))
					num++;
				if(P2.isOccupied(9,body[2].y+1))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
				if(P2.isOccupied(9,body[2].y-1))
					num++;
			}else{
				if(P2.isOccupied(body[2].x-1,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y-1))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[2].x <= 1){
				body[0].x = 2;
				body[0].y = body[2].y+1;
				body[1].x = 2;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y;
			}else if(body[2].x >=7){
				body[0].x = 9;
				body[0].y = body[2].y+1;
				body[1].x = 9;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 7;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x+1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x-1;
				body[3].y = body[2].y;
			}
		}else if(form == 2){
			form = 3;
			if(body[2].x <= 1){
				body[0].x = 1;
				body[0].y = body[2].y-1;
				body[1].x = 0;
				body[1].y = body[2].y-1;
				body[2].x = 0;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y+1;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y-1;
				body[1].x = 8;
				body[1].y = body[2].y-1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 8;
				body[3].y = body[2].y+1;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x;
				body[1].y = body[2].y-1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y+1;
			}
		}else if(form == 3){
			form = 4;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y-1;
				body[1].x = 0;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 2;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 7;
				body[0].y = body[2].y-1;
				body[1].x = 7;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x-1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x+1;
				body[3].y = body[2].y;
			}
		}else if(form == 4){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y+1;
				body[1].x = 1;
				body[1].y = body[2].y+1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 1;
				body[3].y = body[2].y-1;
			}else if(body[2].x >= 8){
				body[0].x = 8;
				body[0].y = body[2].y+1;
				body[1].x = 9;
				body[1].y = body[2].y+1;
				body[2].x = 9;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y-1;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y-1;
			}
		}
		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[1].x,c[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[2].x,c[2].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(c[1].y == 19||c[2].y == 19||c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[2].x,c[2].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}J2;
struct L2{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,7,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'L';
		form = 1;
		body[0].x = 6;
		body[0].y = -1;
		body[1].x = 5;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 5;
		body[3].y = -3;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[1].x,body[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[0].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[2].x,body[2].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(body[1].y == 19||body[2].y == 19||body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[2].x,body[2].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1)||P2.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1))//if left down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x-1,body[0].y-1)||P2.isOccupied(body[2].x-1,body[2].y-1)||P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x-1,body[1].y-1)||P2.isOccupied(body[2].x-1,body[2].y-1)||P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 3&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 4&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x+1,body[1].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[0].x+1,body[0].y+1)||P2.isOccupied(body[1].x+1,body[1].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 3&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 4&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[2].x <= 1){
				if(P2.isOccupied(0,body[2].y+1))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(2,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(7,body[2].y+1))
					num++;
				if(P2.isOccupied(7,body[2].y))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
			}else{
				if(P2.isOccupied(body[2].x-1,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y))
					num++;
			}
		}else if(form == 2){
			if(body[2].x <= 1){
				if(P2.isOccupied(0,body[2].y-1))
					num++;
				if(P2.isOccupied(1,body[2].y-1))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(1,body[2].y+1))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(8,body[2].y-1))
					num++;
				if(P2.isOccupied(9,body[2].y-1))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
				if(P2.isOccupied(9,body[2].y+1))
					num++;
			}else{
				if(P2.isOccupied(body[2].x-1,body[2].y-1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y-1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y+1))
					num++;
			}
		}else if(form == 3){
			if(body[2].x <= 1){
				if(P2.isOccupied(2,body[2].y-1))
					num++;
				if(P2.isOccupied(2,body[2].y))
					num++;
				if(P2.isOccupied(1,body[2].y))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(9,body[2].y-1))
					num++;
				if(P2.isOccupied(9,body[2].y))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(7,body[2].y))
					num++;
			}else{
				if(P2.isOccupied(body[2].x+1,body[2].y-1))
					num++;
				if(P2.isOccupied(body[2].x+1,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x-1,body[2].y))
					num++;
			}
		}else if(form == 4){
			if(body[2].x <= 1){
				if(P2.isOccupied(1,body[2].y+1))
					num++;
				if(P2.isOccupied(0,body[2].y+1))
					num++;
				if(P2.isOccupied(0,body[2].y))
					num++;
				if(P2.isOccupied(0,body[2].y-1))
					num++;
			}else if(body[2].x >=8){
				if(P2.isOccupied(9,body[2].y+1))
					num++;
				if(P2.isOccupied(8,body[2].y+1))
					num++;
				if(P2.isOccupied(8,body[2].y))
					num++;
				if(P2.isOccupied(8,body[2].y-1))
					num++;
			}else{
				if(P2.isOccupied(body[2].x+1,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y+1))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y))
					num++;
				if(P2.isOccupied(body[2].x,body[2].y-1))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y+1;
				body[1].x = 0;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 2;
				body[3].y = body[2].y;
			}else if(body[2].x >=7){
				body[0].x = 7;
				body[0].y = body[2].y+1;
				body[1].x = 7;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x-1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x+1;
				body[3].y = body[2].y;
			}
		}else if(form == 2){
			form = 3;
			if(body[2].x <= 1){
				body[0].x = 0;
				body[0].y = body[2].y-1;
				body[1].x = 1;
				body[1].y = body[2].y-1;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 1;
				body[3].y = body[2].y+1;
			}else if(body[2].x >= 8){
				body[0].x = 8;
				body[0].y = body[2].y-1;
				body[1].x = 9;
				body[1].y = body[2].y-1;
				body[2].x = 9;
				body[2].y = body[2].y;
				body[3].x = 9;
				body[3].y = body[2].y+1;
			}else{
				body[0].x = body[2].x-1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x;
				body[1].y = body[2].y-1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y+1;
			}
		}else if(form == 3){
			form = 4;
			if(body[2].x <= 1){
				body[0].x = 2;
				body[0].y = body[2].y-1;
				body[1].x = 2;
				body[1].y = body[2].y;
				body[2].x = 1;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y-1;
				body[1].x = 9;
				body[1].y = body[2].y;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 7;
				body[3].y = body[2].y;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y-1;
				body[1].x = body[2].x+1;
				body[1].y = body[2].y;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x-1;
				body[3].y = body[2].y;
			}
		}else if(form == 4){
			form = 1;
			if(body[2].x <= 1){
				body[0].x = 1;
				body[0].y = body[2].y+1;
				body[1].x = 0;
				body[1].y = body[2].y+1;
				body[2].x = 0;
				body[2].y = body[2].y;
				body[3].x = 0;
				body[3].y = body[2].y-1;
			}else if(body[2].x >= 8){
				body[0].x = 9;
				body[0].y = body[2].y+1;
				body[1].x = 8;
				body[1].y = body[2].y+1;
				body[2].x = 8;
				body[2].y = body[2].y;
				body[3].x = 8;
				body[3].y = body[2].y-1;
			}else{
				body[0].x = body[2].x+1;
				body[0].y = body[2].y+1;
				body[1].x = body[2].x;
				body[1].y = body[2].y+1;
				body[2].x = body[2].x;
				body[2].y = body[2].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y-1;
			}
		}
		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[1].x,c[1].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[0].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[2].x,c[2].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(c[1].y == 19||c[2].y == 19||c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[2].x,c[2].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}L2;
struct T2{
	char name;
	int form;
	coord body[4],dest[4];
	void show(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_block(body[i].x+OFFSET_P2_X/2,body[i].y,5,0);
		}
	}
	void clear(void){
		for(int i=0;i<4;i++){
			if(body[i].y >= 0)
				UI.tetris_shadow(body[i].x+OFFSET_P2_X/2,body[i].y,0,0);
		}
	}
	void init(void){
		name = 'T';
		form = 1;
		body[0].x = 5;
		body[0].y = -1;
		body[1].x = 4;
		body[1].y = -1;
		body[2].x = 5;
		body[2].y = -2;
		body[3].x = 6;
		body[3].y = -1;
		findGoal();
		showGoal();
		show();
	}
	void drop(void){
		clear();
		for(int i=0;i<4;i++){
			body[i].y++;
		}
		show();
	}
	int isLanded(void){
		if(form == 1){
			if(body[0].y == 19||body[1].y == 19||body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[0].x,body[0].y+1)||P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(body[1].y == 19)
				return 1;
			else if(P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[2].x,body[2].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(body[2].y == 19)
				return 1;
			else if(P2.isOccupied(body[1].x,body[1].y+1)||P2.isOccupied(body[2].x,body[2].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(body[3].y == 19)
				return 1;
			else if(P2.isOccupied(body[2].x,body[2].y+1)||P2.isOccupied(body[3].x,body[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	int isAboveScreen(void){
		int num=0;
		for(int i=0;i<=3;i++){//above screen
			if(body[i].y <= 0)
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	int isLeftOccupied(void){
		int num=0;
		if(form == 1){//if left exists sth
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x-1,body[1].y-1))//if left down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x-1,body[1].y-1)||P2.isOccupied(body[2].x-1,body[2].y-1))//if left down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[2].x-1,body[2].y-1)||P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){
				if(P2.isOccupied(body[i].x-1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[3].x-1,body[3].y-1))//if left down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_left(void){
		clear();
		clearGoal();
		if(form == 1&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 2&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 3&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}else if(form == 4&&!isLeftOccupied()){
			if(body[0].x > 0){
				for(int i=0;i<=3;i++){
					body[i].x--;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRightOccupied(void){
		int num=0;
		if(form == 1){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}else if(form == 2){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x+1,body[1].y+1))//if right down exists sth
				num++;
		}else if(form == 3){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[1].x+1,body[1].y+1)||P2.isOccupied(body[2].x+1,body[2].y+1))//if right down exists sth
				num++;
		}else if(form == 4){
			for(int i=0;i<=3;i++){//if right exist sth
				if(P2.isOccupied(body[i].x+1,body[i].y))
					num++;
			}
			if(P2.isOccupied(body[2].x+1,body[2].y+1)||P2.isOccupied(body[3].x+1,body[3].y+1))//if right down exists sth
				num++;
		}
		if(num>=1)
			return 1;
		else
			return 0;
	}
	void shift_right(void){
		clear();
		clearGoal();
		if(form == 1&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 2&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 3&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}else if(form == 4&&!isRightOccupied()){
			if(body[3].x < 9){
				for(int i=0;i<=3;i++){
					body[i].x++;
				}
			}
		}
		findGoal();
		showGoal();
		show();
	}
	int isRotatable(void){
		int num = 0;
		if(form == 1){
			if(body[0].x <= 1){
				if(P2.isOccupied(1,body[0].y))
					num++;
				if(P2.isOccupied(1,body[0].y+1))
					num++;
				if(P2.isOccupied(0,body[0].y))
					num++;
				if(P2.isOccupied(1,body[0].y-1))
					num++;
			}else if(body[0].x >=8){
				if(P2.isOccupied(9,body[0].y))
					num++;
				if(P2.isOccupied(9,body[0].y+1))
					num++;
				if(P2.isOccupied(8,body[0].y))
					num++;
				if(P2.isOccupied(9,body[0].y-1))
					num++;
			}else{
				if(P2.isOccupied(body[0].x,body[0].y+1))
					num++;
			}
		}else if(form == 2){
			if(body[0].x <= 1){
				if(P2.isOccupied(1,body[0].y))
					num++;
				if(P2.isOccupied(2,body[0].y))
					num++;
				if(P2.isOccupied(1,body[0].y+1))
					num++;
				if(P2.isOccupied(0,body[0].y))
					num++;
			}else if(body[0].x >=8){
				if(P2.isOccupied(8,body[0].y))
					num++;
				if(P2.isOccupied(9,body[0].y))
					num++;
				if(P2.isOccupied(8,body[0].y+1))
					num++;
				if(P2.isOccupied(7,body[0].y))
					num++;
			}else{
				if(P2.isOccupied(body[0].x+1,body[0].y))
					num++;
			}
		}else if(form == 3){
			if(body[0].x <= 1){
				if(P2.isOccupied(0,body[0].y))
					num++;
				if(P2.isOccupied(0,body[0].y-1))
					num++;
				if(P2.isOccupied(1,body[0].y))
					num++;
				if(P2.isOccupied(0,body[0].y+1))
					num++;
			}else if(body[0].x >=8){
				if(P2.isOccupied(8,body[0].y))
					num++;
				if(P2.isOccupied(8,body[0].y-1))
					num++;
				if(P2.isOccupied(9,body[0].y))
					num++;
				if(P2.isOccupied(8,body[0].y+1))
					num++;
			}else{
				if(P2.isOccupied(body[0].x,body[0].y-1))
					num++;
			}
		}else if(form == 4){
			if(body[0].x <= 1){
				if(P2.isOccupied(1,body[0].y))
					num++;
				if(P2.isOccupied(0,body[0].y))
					num++;
				if(P2.isOccupied(1,body[0].y-1))
					num++;
				if(P2.isOccupied(2,body[0].y))
					num++;
			}else if(body[0].x >=8){
				if(P2.isOccupied(8,body[0].y))
					num++;
				if(P2.isOccupied(7,body[0].y))
					num++;
				if(P2.isOccupied(8,body[0].y-1))
					num++;
				if(P2.isOccupied(9,body[0].y))
					num++;
			}else{
				if(P2.isOccupied(body[0].x-1,body[0].y))
					num++;
			}
		}
		if(num==0)
			return 1;
		else
			return 0;
	}
	void flip(void){
		clear();
		clearGoal();
		if(form == 1){
			form = 2;
			if(body[0].x <= 1){
				body[0].x = 1;
				body[0].y = body[0].y;
				body[1].x = 1;
				body[1].y = body[0].y+1;
				body[2].x = 0;
				body[2].y = body[0].y;
				body[3].x = 1;
				body[3].y = body[0].y-1;
			}else if(body[0].x >=8){
				body[0].x = 9;
				body[0].y = body[0].y;
				body[1].x = 9;
				body[1].y = body[0].y+1;
				body[2].x = 8;
				body[2].y = body[0].y;
				body[3].x = 9;
				body[3].y = body[0].y-1;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x;
				body[1].y = body[0].y+1;
			}
		}else if(form == 2){
			form = 3;
			if(body[0].x <= 1){
				body[0].x = 1;
				body[0].y = body[0].y;
				body[1].x = 2;
				body[1].y = body[0].y;
				body[2].x = 1;
				body[2].y = body[0].y+1;
				body[3].x = 0;
				body[3].y = body[0].y;
			}else if(body[0].x >= 8){
				body[0].x = 8;
				body[0].y = body[0].y;
				body[1].x = 9;
				body[1].y = body[0].y;
				body[2].x = 8;
				body[2].y = body[0].y+1;
				body[3].x = 7;
				body[3].y = body[0].y;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x+1;
				body[1].y = body[0].y;
			}
		}else if(form == 3){
			form = 4;
			if(body[0].x <= 1){
				body[0].x = 0;
				body[0].y = body[0].y;
				body[1].x = 0;
				body[1].y = body[0].y-1;
				body[2].x = 1;
				body[2].y = body[0].y;
				body[3].x = 0;
				body[3].y = body[0].y+1;
			}else if(body[0].x >= 8){
				body[0].x = 8;
				body[0].y = body[0].y;
				body[1].x = 8;
				body[1].y = body[0].y-1;
				body[2].x = 9;
				body[2].y = body[0].y;
				body[3].x = 8;
				body[3].y = body[0].y+1;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x;
				body[1].y = body[0].y-1;
			}
		}else if(form == 4){
			form = 1;
			if(body[0].x <= 1){
				body[0].x = 1;
				body[0].y = body[0].y;
				body[1].x = 0;
				body[1].y = body[0].y;
				body[2].x = 1;
				body[2].y = body[0].y-1;
				body[3].x = 2;
				body[3].y = body[0].y;
			}else if(body[0].x >= 8){
				body[0].x = 8;
				body[0].y = body[0].y;
				body[1].x = 7;
				body[1].y = body[0].y;
				body[2].x = 8;
				body[2].y = body[0].y-1;
				body[3].x = 9;
				body[3].y = body[0].y;
			}else{
				body[0].x = body[0].x;
				body[0].y = body[0].y;
				body[3].x = body[2].x;
				body[3].y = body[2].y;
				body[2].x = body[1].x;
				body[2].y = body[1].y;
				body[1].x = body[0].x-1;
				body[1].y = body[0].y;
			}
		}

		findGoal();
		showGoal();
		show();
	}
	void showGoal(){
		for(int i=0;i<4;i++){
			if(dest[i].y >= 0)
				UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,7);
		}
	}
	void clearGoal(void){
		for(int i=0;i<4;i++){
			UI.tetris_shadow(dest[i].x+OFFSET_P2_X/2,dest[i].y,0,0);
		}
	}
	int isGoalLanded(coord c[4]){
		if(form == 1){
			if(c[0].y == 19||c[1].y == 19||c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[0].x,c[0].y+1)||P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 2){
			if(c[1].y == 19)
				return 1;
			else if(P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[2].x,c[2].y+1))
				return 1;
			else
				return 0;
		}else if(form == 3){
			if(c[2].y == 19)
				return 1;
			else if(P2.isOccupied(c[1].x,c[1].y+1)||P2.isOccupied(c[2].x,c[2].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}else if(form == 4){
			if(c[3].y == 19)
				return 1;
			else if(P2.isOccupied(c[2].x,c[2].y+1)||P2.isOccupied(c[3].x,c[3].y+1))
				return 1;
			else
				return 0;
		}
	}
	void findGoal(void){
		coord temp[4];
		for(int i=0;i<=3;i++){
			temp[i] = body[i];
		}

		while(1){
			if(isGoalLanded(temp)){
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				break;
			}else{
				for(int i=0;i<=3;i++){
					dest[i] = temp[i];
				}
				for(int i=0;i<4;i++){
					temp[i].y++;
				}
			}
		}
	}
	void fastDrop(void){
		clear();
		for(int i=0;i<=3;i++){
			body[i] = dest[i];
		}
		show();
	}
}T2;


struct blk_list{

	int blk[14],len;

	void rand7_generate(int n[]){

		int table[7]={0};
		for(int i=0;i<7;i++){
			int num = rand()%7;
			if(table[num]==0){
				table[num]++;
				n[i]=num;
			}else{
				i--;
			}
		}

	}
	void init(){
		rand7_generate(blk);
		rand7_generate(blk+7);
		len = 14;
	}
	void show(){
		for(int i=0;i<len;i++){
			printf("%2d ",blk[i]);
		}
	}
	int pop(){
		int value = blk[0];
		for(int i=0;i<len;i++){
			blk[i]=blk[i+1];
		}
		len--;
		if(len == 7){
			rand7_generate(blk+7);
			len = 14;
		}
		return value;
	}

}blk_list;
struct blk_list2{

	int blk[14],len;

	void rand7_generate(int n[]){

		int table[7]={0};
		for(int i=0;i<7;i++){
			int num = rand()%7;
			if(table[num]==0){
				table[num]++;
				n[i]=num;
			}else{
				i--;
			}
		}

	}
	void init(){
		rand7_generate(blk);
		rand7_generate(blk+7);
		len = 14;
	}
	void show(){
		for(int i=0;i<len;i++){
			printf("%2d ",blk[i]);
		}
	}
	int pop(){
		int value = blk[0];
		for(int i=0;i<len;i++){
			blk[i]=blk[i+1];
		}
		len--;
		if(len == 7){
			rand7_generate(blk+7);
			len = 14;
		}
		return value;
	}

}blk_list2;

//¡½

struct game_tetris_Ctrl_P1{

	void roundInit(int b){
		if(b==0){
			I.init();
		}else if(b==1){
			O.init();
		}else if(b==2){
			S.init();
		}else if(b==3){
			Z.init();
		}else if(b==4){
			J.init();
		}else if(b==5){
			L.init();
		}else if(b==6){
			T.init();
		}
	}
	void flip(int blk_type){
		if(blk_type == 0&&I.isRotatable()){
			I.flip();
		}else if(blk_type == 2&&S.isRotatable()){
			S.flip();
		}else if(blk_type == 3&&Z.isRotatable()){
			Z.flip();
		}else if(blk_type == 4&&J.isRotatable()){
			J.flip();
		}else if(blk_type == 5&&L.isRotatable()){
			L.flip();
		}else if(blk_type == 6){
			T.flip();
		}
	}
	void shiftLeft(int blk_type){
		if(blk_type == 0){
			I.shift_left();
		}else if(blk_type == 1){
			O.shift_left();
		}else if(blk_type == 2){
			S.shift_left();
		}else if(blk_type == 3){
			Z.shift_left();
		}else if(blk_type == 4){
			J.shift_left();
		}else if(blk_type == 5){
			L.shift_left();
		}else if(blk_type == 6){
			T.shift_left();
		}
	}
	void shiftRight(int blk_type){
		if(blk_type == 0){
			I.shift_right();
		}else if(blk_type == 1){
			O.shift_right();
		}else if(blk_type == 2){
			S.shift_right();
		}else if(blk_type == 3){
			Z.shift_right();
		}else if(blk_type == 4){
			J.shift_right();
		}else if(blk_type == 5){
			L.shift_right();
		}else if(blk_type == 6){
			T.shift_right();
		}
	}
	void clear(int blk_type){
		if(blk_type == 0){
			I.clear();
			I.clearGoal();
		}else if(blk_type == 1){
			O.clear();
			O.clearGoal();
		}else if(blk_type == 2){
			S.clear();
			S.clearGoal();
		}else if(blk_type == 3){
			Z.clear();
			Z.clearGoal();
		}else if(blk_type == 4){
			J.clear();
			J.clearGoal();
		}else if(blk_type == 5){
			L.clear();
			L.clearGoal();
		}else if(blk_type == 6){
			T.clear();
			T.clearGoal();
		}
	}
	void fastDrop(int blk_type){
		if(blk_type == 0){
			I.fastDrop();
		}else if(blk_type == 1){
			O.fastDrop();
		}else if(blk_type == 2){
			S.fastDrop();
		}else if(blk_type == 3){
			Z.fastDrop();
		}else if(blk_type == 4){
			J.fastDrop();
		}else if(blk_type == 5){
			L.fastDrop();
		}else if(blk_type == 6){
			T.fastDrop();
		}
	}
	void drop(int blk_type){
		if(blk_type == 0){
			I.drop();
		}else if(blk_type == 1){
			O.drop();
		}else if(blk_type == 2){
			S.drop();
		}else if(blk_type == 3){
			Z.drop();
		}else if(blk_type == 4){
			J.drop();
		}else if(blk_type == 5){
			L.drop();
		}else if(blk_type == 6){
			T.drop();
		}
	}
	void land(int *blk_type){
		int s = P1.isAnyLines();
		if(s>0){
			P1.clearlines();
			P1.redraw();
		}
		P1.score_print();
		*blk_type = blk_list.pop();
		UI.P1_icon_next(blk_list.blk);
		roundInit(*blk_type);
	}
}game_tetris_Ctrl_P1;
struct game_tetris_Ctrl_P2{

	void roundInit(int b){
		if(b==0){
			I2.init();
		}else if(b==1){
			O2.init();
		}else if(b==2){
			S2.init();
		}else if(b==3){
			Z2.init();
		}else if(b==4){
			J2.init();
		}else if(b==5){
			L2.init();
		}else if(b==6){
			T2.init();
		}
	}
	void flip(int blk_type){
		if(blk_type == 0&&I2.isRotatable()){
			I2.flip();
		}else if(blk_type == 2&&S2.isRotatable()){
			S2.flip();
		}else if(blk_type == 3&&Z2.isRotatable()){
			Z2.flip();
		}else if(blk_type == 4&&J2.isRotatable()){
			J2.flip();
		}else if(blk_type == 5&&L2.isRotatable()){
			L2.flip();
		}else if(blk_type == 6){
			T2.flip();
		}
	}
	void shiftLeft(int blk_type){
		if(blk_type == 0){
			I2.shift_left();
		}else if(blk_type == 1){
			O2.shift_left();
		}else if(blk_type == 2){
			S2.shift_left();
		}else if(blk_type == 3){
			Z2.shift_left();
		}else if(blk_type == 4){
			J2.shift_left();
		}else if(blk_type == 5){
			L2.shift_left();
		}else if(blk_type == 6){
			T2.shift_left();
		}
	}
	void shiftRight(int blk_type){
		if(blk_type == 0){
			I2.shift_right();
		}else if(blk_type == 1){
			O2.shift_right();
		}else if(blk_type == 2){
			S2.shift_right();
		}else if(blk_type == 3){
			Z2.shift_right();
		}else if(blk_type == 4){
			J2.shift_right();
		}else if(blk_type == 5){
			L2.shift_right();
		}else if(blk_type == 6){
			T2.shift_right();
		}
	}
	void clear(int blk_type){
		if(blk_type == 0){
			I2.clear();
			I2.clearGoal();
		}else if(blk_type == 1){
			O2.clear();
			O2.clearGoal();
		}else if(blk_type == 2){
			S2.clear();
			S2.clearGoal();
		}else if(blk_type == 3){
			Z2.clear();
			Z2.clearGoal();
		}else if(blk_type == 4){
			J2.clear();
			J2.clearGoal();
		}else if(blk_type == 5){
			L2.clear();
			L2.clearGoal();
		}else if(blk_type == 6){
			T2.clear();
			T2.clearGoal();
		}
	}
	void fastDrop(int blk_type){
		if(blk_type == 0){
			I2.fastDrop();
		}else if(blk_type == 1){
			O2.fastDrop();
		}else if(blk_type == 2){
			S2.fastDrop();
		}else if(blk_type == 3){
			Z2.fastDrop();
		}else if(blk_type == 4){
			J2.fastDrop();
		}else if(blk_type == 5){
			L2.fastDrop();
		}else if(blk_type == 6){
			T2.fastDrop();
		}
	}
	void drop(int blk_type){
		if(blk_type == 0){
			I2.drop();
		}else if(blk_type == 1){
			O2.drop();
		}else if(blk_type == 2){
			S2.drop();
		}else if(blk_type == 3){
			Z2.drop();
		}else if(blk_type == 4){
			J2.drop();
		}else if(blk_type == 5){
			L2.drop();
		}else if(blk_type == 6){
			T2.drop();
		}
	}
	void land(int *blk_type){
		int s = P2.isAnyLines();
		if(s>0){
			P2.clearlines();
			P2.redraw();
		}
		P2.score_print();
		*blk_type = blk_list2.pop();
		UI.P2_icon_next(blk_list2.blk);
		roundInit(*blk_type);
	}
}game_tetris_Ctrl_P2;


void kbsweep(int *blk_type,int *blk_type2,int *time_counter,char *pTxData,char *pRxData){
	if(kbhit()){
		if(int ch=getch()){
			if(ch == 224){//arrow key detect
				ch = getch();
				if(ch == 72){//press UP
					game_tetris_Ctrl_P1.flip(*blk_type);
					pTxData[0]=1;
				}
				if(ch == 80){//press DOWN
					game_tetris_Ctrl_P1.drop(*blk_type);
					pTxData[0]=2;
				}
				if(ch == 75){//press LEFT
					game_tetris_Ctrl_P1.shiftLeft(*blk_type);
					pTxData[0]=3;
				}
				if(ch == 77){//press RIGHT
					game_tetris_Ctrl_P1.shiftRight(*blk_type);
					pTxData[0]=4;
				}
			}
			else{
				if(ch == 'c'||ch == 'C'){//Hold block
					if(!UI.P1_isHold()){
						game_tetris_Ctrl_P1.clear(*blk_type);
						UI.P1_hold_next(blk_type);
						*blk_type = blk_list.pop();
						UI.P1_icon_next(blk_list.blk);
						game_tetris_Ctrl_P1.roundInit(*blk_type);
					}else{
						game_tetris_Ctrl_P1.clear(*blk_type);
						UI.P1_hold_swap(blk_type);
						UI.P1_icon_next(blk_list.blk);
						game_tetris_Ctrl_P1.roundInit(*blk_type);
					}
					pTxData[0]=5;
				}

				if(ch == ' '){
					game_tetris_Ctrl_P1.fastDrop(*blk_type);
					*time_counter = 1;
					pTxData[0]=6;
				}

			}
		}
	}
}


struct menuCtrl{

	void title(void){

		textcolor(TC_FG_INTENSIFY, 7, 0);
		gotoxy(37, 6);
		printf("ùÝùùùùùùùùùùùùùùùùùùùß\n");
		gotoxy(37, 7);
		printf("ùø  Client ùø\n");
		gotoxy(37, 8);
		printf("ùãùùùùùùùùùùùùùùùùùùùå\n");
		gotoxy(37, 16);
		printf("¡´¡´¡´¡´¡´ ¡´¡´¡´¡´ ¡´¡´¡´¡´¡´ ¡´¡´¡´¡´ ¡´¡´¡´¡´¡´ ¡´¡´¡´¡´\n");
		gotoxy(37, 17);
		printf("    ¡´     ¡´           ¡´     ¡´    ¡´     ¡´     ¡´      \n");
		gotoxy(37, 18);
		printf("    ¡´     ¡´¡´¡´¡´     ¡´     ¡´¡´¡´¡´     ¡´     ¡´¡´¡´¡´\n");
		gotoxy(37, 19);
		printf("    ¡´     ¡´           ¡´     ¡´  ¡´       ¡´           ¡´\n");
		gotoxy(37, 20);
		printf("    ¡´     ¡´¡´¡´¡´     ¡´     ¡´    ¡´ ¡´¡´¡´¡´¡´ ¡´¡´¡´¡´\n");
		gotoxy(39, 23);
		printf("¡´¡´¡´¡´ ¡´¡´¡´¡´ ¡´¡´¡´¡´¡´ ¡´¡´¡´¡´¡´ ¡´       ¡´¡´¡´¡´\n");
		gotoxy(39, 24);
		printf("¡´    ¡´ ¡´    ¡´     ¡´         ¡´     ¡´       ¡´      \n");
		gotoxy(39, 25);
		printf("¡´¡´¡´¡´ ¡´¡´¡´¡´     ¡´         ¡´     ¡´       ¡´¡´¡´¡´\n");
		gotoxy(39, 26);
		printf("¡´    ¡´ ¡´    ¡´     ¡´         ¡´     ¡´       ¡´      \n");
		gotoxy(39, 27);
		printf("¡´¡´¡´¡´ ¡´    ¡´     ¡´         ¡´     ¡´¡´¡´¡´ ¡´¡´¡´¡´\n");
	}
	

}menuCtrl;


int main(int argc, char *argv[]){

	SetConsoleTitle("Tetris Client");//set title
	system("mode con cols=165 lines=45");//set Console size
	//srand(time(NULL));//time seed

	//init
	WSADATA wsaData = {0};
	WORD wVer = MAKEWORD(2,2);
	WSAStartup(wVer, &wsaData);

	int conn_success, port_num = 10000;
	char inputIpAddr[16];

	menuCtrl.title();
	

	//socket
	SOCKET hServer; // listen socket
	hServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	gotoxy(37, 10);
	printf("ùÝùùùùùùùù½Ð¿é¤Jport¸¹:");
	scanf("%d", &port_num);
	gotoxy(37, 12);
	printf("ùãùùùùùùùù½Ð¿é¤Jip:");
	scanf("%s", &inputIpAddr);
	//connect
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_port = htons(port_num);
	saServer.sin_addr.s_addr = inet_addr(inputIpAddr);
	conn_success = connect(hServer, (sockaddr*)&saServer, sizeof(sockaddr));

	//socket data
	char pRxData[SIZE] = {0};
	char pTxData[SIZE] = {0};

	UI.dft();//set default UI

	//Key_Event setting
	HANDLE handle;
	DWORD cnt;
	DWORD mode;//Console Mode
	INPUT_RECORD input;

	//Key event handle
	handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &mode);
	SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);
	int blk_type,blk_type2;//0:I,1:O,2:S,3:Z,4:J,5:L

	int game=1;
	int P1reset = 0;
	int P2reset = 0;
	if (game == 1) {
		while (1) {

			system("cls");
			UI.init();
			UI.P1_window();
			UI.P2_window();
			if (P1reset == 1)
			{
				P1.init();
			}
			else if (P2reset == 1)
			{
				P2.init();
			}
			else
			{
				P1.init();
				P2.init();
			}
			blk_list.init();
			blk_list2.init();
			UI.P1_hold_init();
			UI.P2_hold_init();
			blk_type = blk_list.pop();
			blk_type2 = blk_list2.pop();
			UI.P1_icon_init(blk_list.blk);
			UI.P2_icon_init(blk_list2.blk);
			game_tetris_Ctrl_P1.roundInit(blk_type);
			game_tetris_Ctrl_P2.roundInit(blk_type2);
			P1.redraw();
			P2.redraw();
			P1reset = 0;
			P2reset = 0;
			P1.score_print();
			if (P1.KO == 2)
			{
				break;
			}
			P2.score_print();
			if (P2.KO == 2 )
			{
				break;
			}

			int time_counter = 1;
			int P1_KO_printed = 0;
			int P2_KO_printed = 0;
			int result_printed = 0;

			while (1) {
				if (P1.score >= 30)
				{
					break;
				}
				if (P2.score >= 30)
				{
					break;
				}
				if (P1.isGameOver())
				{
					P1reset = 1;
					break;
				}
				if (P2.isGameOver())
				{
					P2reset = 1;
					break;
				}

				if (blk_type == 0) {//I
					if (I.isLanded()) {
						P1.land(I.body, I.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}
				else if (blk_type == 1) {//O
					if (O.isLanded()) {
						P1.land(O.body, O.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}
				else if (blk_type == 2) {//S
					if (S.isLanded()) {
						P1.land(S.body, S.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}
				else if (blk_type == 3) {//Z
					if (Z.isLanded()) {
						P1.land(Z.body, Z.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}
				else if (blk_type == 4) {//J
					if (J.isLanded()) {
						P1.land(J.body, J.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}
				else if (blk_type == 5) {//L
					if (L.isLanded()) {
						P1.land(L.body, L.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}
				else if (blk_type == 6) {//T
					if (T.isLanded()) {
						P1.land(T.body, T.name);
						game_tetris_Ctrl_P1.land(&blk_type);
					}
				}

				if (blk_type2 == 0) {//I
					if (I2.isLanded()) {
						P2.land(I2.body, I2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}
				else if (blk_type2 == 1) {//O
					if (O2.isLanded()) {
						P2.land(O2.body, O2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}
				else if (blk_type2 == 2) {//S
					if (S2.isLanded()) {
						P2.land(S2.body, S2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}
				else if (blk_type2 == 3) {//Z
					if (Z2.isLanded()) {
						P2.land(Z2.body, Z2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}
				else if (blk_type2 == 4) {//J
					if (J2.isLanded()) {
						P2.land(J2.body, J2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}
				else if (blk_type2 == 5) {//L
					if (L2.isLanded()) {
						P2.land(L2.body, L2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}
				else if (blk_type2 == 6) {//T
					if (T2.isLanded()) {
						P2.land(T2.body, T2.name);
						game_tetris_Ctrl_P2.land(&blk_type2);
					}
				}


				kbsweep(&blk_type, &blk_type2, &time_counter, pTxData, pRxData);
				send(hServer, (char*)pTxData, sizeof(pTxData), 0);
				pTxData[0] = 0;

				recv(hServer, (char*)pRxData, sizeof(pRxData), 0);
				if (pRxData[0] == 1) {//press UP
					game_tetris_Ctrl_P2.flip(blk_type2);
					pRxData[0] = 0;
				}
				else if (pRxData[0] == 2) {//press DOWN
					game_tetris_Ctrl_P2.drop(blk_type2);
					pRxData[0] = 0;
				}
				else if (pRxData[0] == 3) {//press LEFT
					game_tetris_Ctrl_P2.shiftLeft(blk_type2);
					pRxData[0] = 0;
				}
				else if (pRxData[0] == 4) {//press RIGHT
					game_tetris_Ctrl_P2.shiftRight(blk_type2);
					pRxData[0] = 0;
				}
				else if (pRxData[0] == 5) {//press RIGHT
					if (!UI.P2_isHold()) {
						game_tetris_Ctrl_P2.clear(blk_type2);
						UI.P2_hold_next(&blk_type2);
						blk_type2 = blk_list2.pop();
						UI.P2_icon_next(blk_list2.blk);
						game_tetris_Ctrl_P2.roundInit(blk_type2);
					}
					else {
						game_tetris_Ctrl_P2.clear(blk_type2);
						UI.P2_hold_swap(&blk_type2);
						UI.P2_icon_next(blk_list2.blk);
						game_tetris_Ctrl_P2.roundInit(blk_type2);
					}
					pRxData[0] = 0;
				}
				else if (pRxData[0] == 6) {//press RIGHT
					game_tetris_Ctrl_P2.fastDrop(blk_type2);
					time_counter = 1;
					pRxData[0] = 0;
				}


				if (time_counter == FRAME) {
					game_tetris_Ctrl_P1.drop(blk_type);
					game_tetris_Ctrl_P2.drop(blk_type2);
					time_counter = 1;
				}
				else {
					time_counter++;
				}
				Sleep(DELAY);
			}
			if (P1.score >= 30)
			{
				break;
			}
			if (P2.score >= 30)
			{
				break;
			}
			system("cls");
			
		}
		
		if (P1.score >= 30)
		{
			system("cls");
			endgame2.title();
		}
		if (P2.score >= 30)
		{
			system("cls");
			endgame1.title();
		}

		system("pause");
		return EXIT_SUCCESS;
	}
		
}
	
void gotoxy(int x, int  y)
{
	COORD point;
	point.X = x, point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void title(void){

	printf("ùÝùùùùùùùùùùùùùùùùùùùß\n");
	printf("ùø      Client      ùø\n");
	printf("ùãùùùùùùùùùùùùùùùùùùùå\n");
}