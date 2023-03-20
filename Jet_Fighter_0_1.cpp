#include <iostream>
#include<windows.h>
#include <conio.h>
#include <chrono>
#include <ctime>
using namespace std;

class ATARI_GAMES{
	private:
		int Fuel=6;
		int Score = 0;
		int X_arena=10;
		int Y_arena=25;
		int sn = 2;
		int X_a=20;
		int Y_a=20;
		int X_e;
		int Y_e;
		int X_f;
		int Y_f;
		int X_s[25]={X_a};
		int Y_s[25]={Y_a};
		int ShootCounter;
		enum eDirecton {STOP, LEFT,RIGHT, UP, DOWN,SHOOT}; // Controls
		eDirecton emove;
		bool GameOver = false;
		bool ShootBool[25] = {false};
		clock_t begin = clock();
		clock_t end;
		int elapsed_secs = 0;
		int elapsed_msecs = 0;
		int count = 0;
		int t = 0, u = 0;
		bool Enemy_Distroy = false;
		
		
		
	public:	
		ATARI_GAMES();
		void about();
		void setting();
		bool gameover(); // define an access function to GameOver
		void initialization();
		void screen();
		void controls();
		void update_arena();		
};


bool continue_bool = true;
string user_response;
string user_response_start;
char game_difficulty='e';

int speed;
ATARI_GAMES atari;

int main(){

atari.about();


while(continue_bool)	{

	ATARI_GAMES atari;
	
	atari.setting();	
	atari.initialization();	
	
	while(!atari.gameover())	{
	
		
	atari.screen();
	
	atari.controls();
	
	atari.update_arena();
	Sleep(speed);
	}
	
	if(atari.gameover()){
		atari.screen();
		Beep(300, 1500);
	}

	cout<<"GameOver"<<endl;
	cout <<"Play Again?(y/n)";
	cin >> user_response;
	
	if(user_response=="y")
		continue_bool = true;
	else
		continue_bool = false;
	
}
if(!continue_bool)
system("cls");
cout << "Jet Fighter-V-1.0"<<endl<<"Programmed by A.Nekoonam.";
Sleep(700);

	return 0;
}





// Implementations

ATARI_GAMES::ATARI_GAMES(){

}

void ATARI_GAMES::about(){
	int  descrip_waiting_time = 200;
	cout<<"Jet Fighter-V-1.0"<<endl;
	Sleep(descrip_waiting_time);
	cout<<"Help:"<<endl;
	Sleep(descrip_waiting_time);
	cout<<"Press 'W', 'A', 'D', 'S' to control the aircraft"<<endl;
	Sleep(descrip_waiting_time);
	cout<<"Take the @ for in-flight refuelling"<<endl;
	Sleep(descrip_waiting_time);
	cout<<"Hit the enemies(#) with 'P'."<<endl;
	Sleep(descrip_waiting_time);
	
}

void ATARI_GAMES::setting(){

	cout<<"Difficulty Level; Easy, Normal, Hard, Expert: (e/n/h/x)?";
	cin >> game_difficulty;
	switch(game_difficulty){
		case 'e':
			speed = 300;
			break;
		case 'n':
			speed = 100;
			break;
		case 'h':
			speed = 50;
			break;		
		case 'x':
			speed = 10;
			break;				
		}	
	
}

void ATARI_GAMES::initialization(){
	X_a = X_arena/2;
	Y_a = Y_arena - Y_arena/4;
	
	X_e = rand()%X_arena;
	Y_e = rand()%Y_arena;
	
	X_f = rand()%X_arena;
	Y_f = rand()%Y_arena;
	

	clock_t end = clock();	
	
	elapsed_secs = int(double(end - begin) / CLOCKS_PER_SEC);
	elapsed_msecs = int(double(end - begin));
	
}

bool ATARI_GAMES::gameover(){return GameOver; }

void ATARI_GAMES::screen(){
	system("cls");
	for (int j=0;j<=Y_arena;j++){
			
		for (int i=0;i<=X_arena;i++)	{
				if (i==0){
					u++;

					if (u>15)
						u=0;
					if (u==5)
						
							cout <<".";
					
					else if (u==10)
						
							cout <<".";

					else if (u==15)

							cout <<".";
					else
							cout <<"|";
				}
			bool white_space = false;
				
			    //fighter
				if (i==X_a && j==Y_a){
					if (!GameOver)
						cout << "^";
					else
						cout << ":.";
					white_space = true;
				}

				
				//enemy
				if (i==X_e && j==Y_e){
					if (!Enemy_Distroy)
						cout << "#";
					else{
						cout << ".:";
						Sleep(100);
						Y_e=0;
						X_e = rand()%X_arena;
					}
						
						
					white_space = true;
				}
				
				//fuel
				if (i==X_f && j==Y_f){
					cout << "@";
					white_space = true;
				}
				
				//shoots	
				for(int q=0;q<sn+1;q++)
				if(i==X_s[q] && j==Y_s[q] && Y_s[q]!=Y_a){
					cout<<'.';
					white_space = true;
					
				}			
				
				if (i==X_arena && j == 0){
				
				for(int f=1;f<=Fuel;f++)
					 cout<< "|";
				cout <<"-"<<" "<<Score;	 
				}
				if (!white_space)
					cout << " ";
					
					
				if (i==X_arena){	
					t++;

					if (t>15)
						t=0;
					if (t==5)
						
							cout <<"+";
					
					else if (t==10)
						
							cout <<"+";

					else if (t==15)

							cout <<"+";
					else
							cout <<"|";

							
				}
				
				

			}
			
			
		cout << endl;
		
	
	
	
	}
	
}

void ATARI_GAMES::controls(){
	if(_kbhit()){
		
		switch(_getch()){
			case 'a':
				emove = LEFT;
				break;
			case 'd':
				emove = RIGHT;
				break;	
			case 'w':
				emove = UP;	
				break;
			case 's':
				emove = DOWN;
				break;	
			case 'p':
				emove = SHOOT;
				ShootCounter++;
				break;	
			default:
				break;					
		}
	}
}

void ATARI_GAMES::update_arena(){
	Enemy_Distroy = false;
	switch(emove){
		
		case RIGHT:
			X_a++;
			emove=STOP;
			break;
		case LEFT:
			X_a--;
			emove=STOP;
			break;
		case UP:
			if(Y_a>Y_arena/2)
				Y_a--;
			emove=STOP;
			break;
		case DOWN:
			if(Y_a<=Y_arena-3)
				Y_a++;
			emove=STOP;
			break;	
		case SHOOT:
		for(int i=0;i<sn+1;i++)
			if(!ShootBool[i]){
				
				ShootBool[i] = true;
				X_s[i]=X_a;
				Beep(300, 100);
				emove=STOP;
				break;
			}
				
		default:
			break;	
	}
	for(int i=0;i<sn+1;i++)
	if(ShootBool[i]&&Y_s[i]>0){
		
		Y_s[i]--;
	}
	else{
		ShootBool[i] = false;
		Y_s[i]=Y_a;
		X_s[i]=X_a;	
	}	
	for(int i=0;i<sn+1;i++)
	if(X_s[i] == X_e && Y_s[i] == Y_e && Y_a != Y_e)
	{
		Enemy_Distroy = true;
		ShootBool[i] = false;

		
		Y_s[i]=-1;
		Score++;
		Beep(250, 30);
		
	}
	
	if(X_a>X_arena || X_a<0){
		GameOver=true;
		if (X_a<0)
			X_a = 0;
		if (X_a>X_arena)
		    X_a = X_arena;
			
	}
		
	if(X_a == X_e && Y_a == Y_e){
		//Fuel--;
		Beep(8000, 300);
		GameOver = true;	
	}

		//GameOver = true;
	if(X_a == X_f && Y_a == Y_f){
				Fuel+=2;	
		Beep(1000, 20);
	}

	if (Y_e<=Y_arena)
		Y_e++;	
	else{
		Y_e=0;
		X_e = rand()%X_arena;
	}
	
	
	if (Y_f<=Y_arena)
		Y_f++;	
	else{
		Y_f=0;
		X_f = rand()%X_arena;
	}
	clock_t end = clock();
	elapsed_secs =int( double(end - begin) / CLOCKS_PER_SEC ); 
	elapsed_msecs =int( double(end - begin)); 
	if (elapsed_secs%10==0){
		count++;
		if(count==1)
			Fuel--;
		
	}
	else
	count = 0;
	
	switch (Fuel){

	case 1:
		
		Beep(300, 100);
		break;
	case 0:
		GameOver=true;
		break;
		
	}
	
					
}