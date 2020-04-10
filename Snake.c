#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<termios.h>
#include<fcntl.h>
#include<stdio.h>

#define MAT matrix[STAR_ROW[0]][STAR_COL[0]] 
#define ROW 20
#define COL 20
#define NEWLINE write(1,"\n",1)
#define TAB write(1,"\t",1)
#define SPACE write(1," ",1)
#define STAR_ROW star_pos[0]
#define STAR_COL star_pos[1]
#define SYMB '.'
#define SYMBS "."
#define SYM ' '
#define SNAK '@'
#define BITE 'O'
#define RIGHT 'R'
#define LEFT 'L'
#define DOWN 'B'
#define UP 'F'
#define EOM -1
#define COUNT_DOWN 1000

//void *getch_dir(void*);
char getch_dir(void);
void print(char mat[ROW][COL]);
int arr_cpy(char dir);
void update(void);
void print_int(int [2][ROW*COL]);

int star_pos[2][ROW*COL];
char matrix[ROW][COL];
int count=0;
int score=0;
int delay_t;
int Uniqe_bite=0;
char buf;
char dir='\0';
int flg=1,z=0;
int set=1;
int main(){
	int i,j;
	char dir;
	int row=ROW-10,col=COL-10;
	char ch;
	system("clear");
	while(1){
		dir='\0';
		score=0;
		//dir=RIGHT;
		delay_t=10000;
		star_pos[0][0]=0;
		star_pos[0][1]=0;
		star_pos[1][0]=0;
		star_pos[1][1]=1;
		for(i=0;i<2;i++){
			for(j=0;j<ROW*COL;j++){
				if(j>=2)
					star_pos[i][j]=-1;
			}
		}
		for(i=0;i<ROW;i++){
			for(j=0;j<COL;j++){
				if(i==0||j==0||i==ROW-1||j==COL-1)
				matrix[i][j]=SYMB;
				else
				matrix[i][j]=SYM;
			}
		}
		matrix[0][0]=SNAK;
		matrix[0][1]='>';
		int blink=0;
	//	printf("%c\n",dir);
	//	do{
		blink=blink+1;
		system("clear");
		NEWLINE;
		NEWLINE;
		NEWLINE;
		NEWLINE;
		TAB;TAB;TAB;
	//	TAB;TAB;TAB;
		printf("SNAKE\n");
		print(matrix);
	//	TAB;TAB;TAB;
		TAB;TAB;TAB;SPACE;
		printf("SCORE=%d\n",score);
		TAB;
	//	TAB;TAB;TAB;
		printf("......PRESS NUM DIR KEY TO CONTINUE.....\n");

		TAB;TAB;TAB;
		SPACE;SPACE;
		set=1;
		dir=getch_dir();
		Uniqe_bite=0;
		set=0;
		//		sleep(2);
		while(dir=getch_dir()){
			if(delay_t > 1)
			usleep(delay_t);
			else
			usleep(1);
			system("clear");


			if(arr_cpy(dir)){
				while(Uniqe_bite==0){
					int f=0;
					z++;
					srand(getpid()+score+10+z);
					row=rand()%ROW;
					srand(getpid()+score+100+z);
					col=rand()%COL;
					for(j=0;(STAR_ROW[j]!=EOM)&&(STAR_ROW[j]!=(ROW*COL));j++){
						if(STAR_ROW[j]==row)
							if(STAR_COL[j]==col){
								f=1;
								break;
							}
					}
					if(f==0){
						Uniqe_bite=1;
					}
					if(Uniqe_bite==1)
						matrix[row][col]=BITE;
				}
				NEWLINE;
				NEWLINE;
				NEWLINE;
				NEWLINE;
				TAB;TAB;TAB;
				//TAB;TAB;TAB;
				printf("SNAKE\n");
				print(matrix);
				//TAB;TAB;TAB;
				TAB;TAB;TAB;SPACE;
				printf("SCORE=%d\n",score);
			}
			else{
				system("clear");
				NEWLINE;
				NEWLINE;
				NEWLINE;
				NEWLINE;
				//TAB;TAB;TAB;
				TAB;TAB;TAB;
				printf("SNAKE\n");
				print(matrix);
				//TAB;TAB;TAB;
				TAB;TAB;TAB;SPACE;
				printf("SCORE=%d\n",score);
				//TAB;TAB;TAB;
				TAB;TAB;TAB;
				printf("GAME OVER\n");
				sleep(2);
				break;
			}											
		}
	}

}
/*
   void print_int(int arr[2][ROW*COL]){
   int i,j;
   for(i=0;i<2;i++){
   for(j=0;j<ROW*COL&&STAR_ROW[j]!=EOM;j++){
   printf("%4d",arr[i][j]);
   }
   printf("\n\n");       
   }
   }
   */
void update(void){
	count=0;
	if(STAR_ROW[0]!=0&&STAR_ROW[0]!=ROW-1&&STAR_COL[0]!=0&&STAR_COL[0]!=COL-1)
		MAT=SYM;
	else
		MAT=SYMB;
	while(STAR_ROW[count+1]!=EOM){
		STAR_ROW[count]=STAR_ROW[count+1];
		STAR_COL[count]=STAR_COL[count+1];
		count=count+1;

	}
}



int arr_cpy(char dir){
	int i,j;
	count=0;
	while(STAR_ROW[count+1]!=EOM)
		count=count+1;
	if(dir==RIGHT){
		if((STAR_COL[count]+1)==COL)
			return 0;
		if(matrix[STAR_ROW[count]][STAR_COL[count]+1]==SNAK)
			return 0;
		if(matrix[STAR_ROW[count]][STAR_COL[count]+1]==BITE){
			matrix[STAR_ROW[0]][STAR_COL[0]]=SNAK;
			STAR_ROW[count+1]=STAR_ROW[count];
			STAR_COL[count+1]=STAR_COL[count]+1;
			score=score+1;
			count=count+1;
			Uniqe_bite=0;
			delay_t=delay_t-COUNT_DOWN;
			//delay_t=delay_t-10;
		}
		else{
			update();
			STAR_COL[count]=STAR_COL[count]+1;
		}
		matrix[STAR_ROW[count-1]][STAR_COL[count-1]]='@';
		matrix[STAR_ROW[count]][STAR_COL[count]]='>';
		return 1;
	}
	else if(dir==DOWN){
		if((STAR_ROW[count]+1)==ROW)
			return 0;
		if(matrix[STAR_ROW[count]+1][STAR_COL[count]]==SNAK)
			return 0;
		if(matrix[STAR_ROW[count]+1][STAR_COL[count]]==BITE){
			matrix[STAR_ROW[0]][STAR_COL[0]]='@';
			STAR_ROW[count+1]=STAR_ROW[count]+1;
			STAR_COL[count+1]=STAR_COL[count];
			score=score+1;
			count=count+1;
		//	delay_t=delay_t-10;
			delay_t=delay_t-COUNT_DOWN;
			Uniqe_bite=0;
		}
		else{
			update();
			STAR_ROW[count]=STAR_ROW[count]+1;
		}
		matrix[STAR_ROW[count]][STAR_COL[count]]='v';
		matrix[STAR_ROW[count-1]][STAR_COL[count-1]]='@';
		return 1;
	}
	else if(dir==UP){
		if((STAR_ROW[count]-1)==EOM)
			return 0;
		if(matrix[STAR_ROW[count]-1][STAR_COL[count]]==SNAK)
			return 0;
		if(matrix[STAR_ROW[count]-1][STAR_COL[count]]==BITE){
			matrix[STAR_ROW[0]][STAR_COL[0]]='@';
			STAR_ROW[count+1]=STAR_ROW[count]-1;
			STAR_COL[count+1]=STAR_COL[count];
			score=score+1;
			count=count+1;
		//	delay_t=delay_t-10;
			delay_t=delay_t-COUNT_DOWN;
			Uniqe_bite=0;
		}
		else{
			update();
			STAR_ROW[count]=STAR_ROW[count]-1;
		}
		matrix[STAR_ROW[count-1]][STAR_COL[count-1]]='@';
		matrix[STAR_ROW[count]][STAR_COL[count]]='^';
		return 1;
	}
	if(dir==LEFT){
		if((STAR_COL[count]-1)==EOM)
			return 0;
		if(matrix[STAR_ROW[count]][STAR_COL[count]-1]==SNAK)
			return 0;
		if(matrix[STAR_ROW[count]][STAR_COL[count]-1]==BITE){
			matrix[STAR_ROW[0]][STAR_COL[0]]='@';
			STAR_ROW[count+1]=STAR_ROW[count];
			STAR_COL[count+1]=STAR_COL[count]-1;
			score=score+1;
			count=count+1;
			delay_t=delay_t-COUNT_DOWN;
			Uniqe_bite=0;
		}
		else{
			update();
			STAR_COL[count]=STAR_COL[count]-1;
		}
		matrix[STAR_ROW[count-1]][STAR_COL[count-1]]='@';
		matrix[STAR_ROW[count]][STAR_COL[count]]='<';
		return 1;
	}
}


void print(char matrix[ROW][COL]){
	int i,j;
	NEWLINE;SPACE;TAB;
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++){
			write(1,&matrix[i][j],1);
			SPACE;
		}
		NEWLINE;SPACE;TAB;
	}	
	NEWLINE;
}

char getch_dir(void){
	//	while(1){
	//		if(flg==0){
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0,&old)<0)
		perror("tcgetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=set;
	old.c_cc[VTIME]=1;

	if(tcsetattr(0,TCSANOW,&old)<0)
		perror("tcsetattr ICANOCN()");
	if(read(1,&buf,1)<0)
		perror("read()");


	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;


	if(tcsetattr(0,TCSADRAIN,&old)<0)
		perror("tcsetattr ~ICANOCN()");
//	usleep(10000);
	//			flg=1;
	switch(buf){
		case '8':
			//dir=UP;
			return UP;
			break;
		case '5':
			//dir=DOWN;
			return DOWN;
			break;
		case '6':
			//dir=RIGHT;
			return RIGHT;
			break;
		case '4':
			//dir=LEFT;
			return LEFT;
			break;
		default:
			dir=dir;
			break;

	}
	//		}
	//	}
}
