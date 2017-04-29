#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>
#include <conio.h> 
#define ESC 0x1b
#define LTARROW 75
#define RTARROW 77
#define UPARROW 72
#define DNARROW 80
void show();  
void continuee();
       //4x4 lük diziyi oyun ekranýndaki yerlere kutu olarak yerleþtirir
int control();           //boþta kutu olup olmadýðýný ve oynanacak hamle olup olmadýðýný kontrol eder
int control2();          /*kullanýcý tuþa bastýðýnda oyunda deðiþiklik olup olmadýðýný kontrol eder.
Kutulardan biri deðiþtiyse yeni kutu atar.Deðiþmediyse yeni kutu atamaz.*/
      //timer modunu kontrol eder(yapým aþamasýnda) 
void start();    //baslatýr
int control3();        
void firstmoveLeft();	 //kutularý sol tarafa hareket ettirir
void computeLeft();      //yanyana olan ayný kutularý sol tarafta toplar
void moveLeft();         //kutularý sol tarafa hareket ettirir
void firstmoveRight();	 //kutularý sað tarafa hareket ettirir
void computeRight();     //yanyana olan kutularý sað tarafta toplar
void moveRight();        //kutularý sað tarafa hareket ettirir
void firstmoveDown();    //kutularý aþaðýya hareket ettirir
void computeDown();      //altalta olan ayný kutularý toplayýp altta toplar
void moveDown();         //kutularý aþaðýya hareket ettirir
void firstmoveUp();	     //kutularý yukarýya hareket ettirir
void computeUp();	     //altalta olan ayný kutularý toplayýp yukarda toplar
void moveUp();           //kutularý yukarýya hareket ettirir
void loading();			 //loading ekraný
void ana();              //anamenu ekraný
void how();              //howtoplay ekraný
void credits();          //yapýmcý vb.. ekraný
void play();             //play ekraný
void play2048();         //2048 modunu oynama ekraný
 	     //timer modu (yapým aþamasýnda) 

int i,j,c;
int score=0;
int board[5][5]={0};
int temp[5][5]={0};

int main( )
{
    initwindow(570, 630, "2048");
    loading();        //loading ekraný
    cleardevice();
	ana();          //anamenu ekraný
	
    
    return 0;
}

void loading()          //loading ekraný
{
	
	cleardevice();       
	readimagefile("loading.bmp", 0, 0, 570, 630); /*oyunun açýlmadan önceki bekleme ekraný*/
	rectangle(100, 350, 430, 380);
	for (i = 100; i <= 430; i++)
	   {
		bar(100, 350, i, 380);
		delay(4);
	   }

} 
void ana()             //anamenu ekraný
{
 	 int d, f;
 	 
 	 cleardevice();
 	
 	 while (1)
	  {
	 readimagefile("ana.bmp", 0, 0, 570, 630);
	 readimagefile("cikis.jpg", 540, 5, 570, 35);
	 
	 
  	  	   	  getmouseclick(WM_LBUTTONDOWN, d, f);
						if (d>540 && d<570 && f>5 && f < 35)
			   						{
					  				    exit(1);
					  
				   	                 }	  

					else if (d>325 && d<550 && f>325 && f < 425)
			   						{
					  				    credits();
					  					swapbuffers();
				   	                 }	  

					
	 
					else if (d>350 && d<550 && f>50 && f < 150)
			   						{
					  				    play2048();
					  					swapbuffers();
				   	                 }	  

					else if (d>350 && d<550 && f>175 && f < 275)
			   						{
					  				    how();
					  					swapbuffers();
				   	                 }	  
 	 swapbuffers();
	 clearviewport();
	 cleardevice();
 	 
 	  }	//while fonk bitis
	 } //ana fonk.paarantezi



void play2048()      //2048 modunu oynama ekraný
 {

  	  int keyPress;
  	  

     readimagefile("arkaekran.jpg", 0, 0, 570, 630);
 	 
	 readimagefile("grid.jpg", 45, 150, 515, 600);	
	 
	start();  //baslatýr ve kutu atar
	
	memcpy(temp,board,sizeof(board)); //normal diziyi temp dizisine atar(contol2 ye yollayýp deðiþiklik durumuna bakar	     
	
	while(control()==1)    //boþta kutu olup olmadýðýný ve oynanacak hamle olup olmadýðýný kontrol eder
	
	  {
		keyPress = getch();
		 		         if(keyPress == LTARROW )    //sol komutu
		                     {
							  
								 	 
		                       firstmoveLeft();	
		                       computeLeft();
		                       moveLeft(); 
		                     }
		   			   else if(keyPress == RTARROW) //sað komutu
                             {
							   
							  	
		                       firstmoveRight();	
		                       computeRight();
		                       moveRight();
		                      }	
						else if(keyPress == DNARROW)  //aþaðý komutu
			 		        {
							
							  			 			 
							   firstmoveDown();
							   computeDown();
							   moveDown();
							}		
						else if(keyPress == UPARROW)  //yukarý komutu
			 		     	 {
							  
								  swapbuffers();	 
							    firstmoveUp();	
								computeUp();	
								moveUp();
							 }
						else if(keyPress == 83)   //hile
			 		   	  	{
							 	 		 
							     board[3][3]=1024;
								 temp[3][3]=1024;
								 board[3][2]=1024;
								 temp[3][2]=1024;
								 board[3][0]=1024;
								 temp[3][0]=1024;
								 board[3][1]=1024;
								 temp[3][1]=1024;
								 show();

							}
						else if(keyPress == 79)
			 		        {
							 	
								 for(j=1;j<4;j++)
								  		{
										 	board[0][0]=2;
											board[0][j]=board[0][j]*2; 
											temp[0][0]=2;
											board[0][j]=board[0][j-1]*2; 
										}
									for(j=1;j<4;j++)
								  		{
										 	board[1][0]=32;
											board[1][j]=board[1][j]*2; 
											temp[1][0]=32;
											board[1][j]=board[1][j-1]*2; 
										}	
								  	for(j=1;j<4;j++)
								  		{
										 	board[2][0]=512;
											board[2][j]=board[2][j]*2; 
											temp[2][0]=512;
											board[2][j]=board[2][j-1]*2; 
										}
									for(j=1;j<4;j++)
								  		{
										 	board[3][0]=4096;
											board[3][j]=board[3][j]*2; 
											temp[3][0]=4096;
											board[3][j]=board[3][j-1]*2; 
										}					 
												 
								 
			  show();
			  		        }					
	    }	
		if(control()==0) //boþta kutu olup olmadýðýný ve oynanacak hamle olup olmadýðýný kontrol eder
		{ 				 
		ana();
		for(i=0;i<5;i++)
		{
		 		for(j=0;j<5;j++)
				 {
				  	board[i][j]=0;
					temp[i][j]=0;		
 				 }		
		}
		
		
		}
		
		if(control()==2) //kazanma durumu
						 {
						  		   
						  	 	PlaySound("win.wav", NULL, SND_NODEFAULT);
						  		continuee();	
						  	   	
						  	 	
	  	   				 }
 	 swapbuffers();
	 clearviewport();
	 cleardevice();
		
	 
	
 }//play2048 bitis
 void continuee()
 {
  	  char c;
	  int keyPress;
     readimagefile("arkaekran.jpg", 0, 0, 570, 630);
 	 
	 readimagefile("grid.jpg", 45, 150, 515, 600);	
	 
	
	
	memcpy(temp,board,sizeof(board)); //normal diziyi temp dizisine atar(contol2 ye yollayýp deðiþiklik durumuna bakar	     
	
	while(control3()==1)    //boþta kutu olup olmadýðýný ve oynanacak hamle olup olmadýðýný kontrol eder
	
	  {
	   	 keyPress = getch();					
	
		 		         if(keyPress == 75 || keyPress == 30)    //sol komutu
		                     {
		                       firstmoveLeft();	
		                       computeLeft();
		                       moveLeft(); 
		                     }
		   			   else if(keyPress == 77 || keyPress == 32) //sað komutu
                             {
		                       firstmoveRight();	
		                       computeRight();
		                       moveRight();
		                      }	
						else if(keyPress == 80 || keyPress == 31)  //aþaðý komutu
			 		        {
							   firstmoveDown();
							   computeDown();
							   moveDown();
							}		
						else if(keyPress == 72 || keyPress == 17)  //yukarý komutu
			 		     	 {
							    firstmoveUp();	
								computeUp();	
								moveUp();
							 }
	
				
	    }	
		if(control3()==0) //boþta kutu olup olmadýðýný ve oynanacak hamle olup olmadýðýný kontrol eder
		ana();
		
	
 	 swapbuffers();
	 clearviewport();
	 cleardevice();
		
 } 	  
 void how()       //howtoplay ekraný
{
 	 
    swapbuffers();
	clearviewport();
	cleardevice();
	int d, f, a, b, x, y;

 	
	while (1)
	{
	 	  readimagefile("arkaekran.jpg", 0, 0, 570, 630);
	 	  readimagefile("how.jpg", 0, 0, 570, 630);
		  readimagefile("cikis.jpg", 540, 5, 570, 35);
		  readimagefile("geri.jpg", 15, 5, 35, 25);
		  	getmouseclick(WM_LBUTTONDOWN, a, b);
 			if (a > 15 && a < 35 && b > 5 && b < 25)
				{
				  	ana();/*geri resmine týkladýðýnda ana ekrana gönderen kod*/
				}
			else if (a > 540 && a < 570 && b > 5 && b < 35)
	 	     {	
				 exit(1); /*çýkýþ tuþuna basýldýðýnda oyundan çýkaran kod*/
		     }	
        swapbuffers();
		clearviewport();
		cleardevice();
 	 }
 	  	  

 }	//howun bitiþi
 
 void credits()     //yapýmcý vb.. ekraný
{
 	 swapbuffers();
	 clearviewport();
	 cleardevice();
	 int a, b;
 	 
 	 	while (1)
	{
      readimagefile("credit.jpg", 0, 0, 570, 630);
 	  readimagefile("cikis.jpg", 540, 5, 570, 35);
	  readimagefile("geri.jpg", 15, 5, 35, 25);
		  	getmouseclick(WM_LBUTTONDOWN, a, b);
 			if (a > 15 && a < 35 && b > 5 && b < 25)
				{
			 	  	ana();/*geri resmine týkladýðýnda ana ekrana gönderen kod*/
				}
			else if (a > 540 && a < 570 && b > 5 && b < 35)
	 	     {	
				 exit(1); /*çýkýþ tuþuna basýldýðýnda oyundan çýkaran kod*/
		     }	
        swapbuffers();
		clearviewport();
		cleardevice();
 	 }

 } //credits bitiþ
 
 void show()        //4x4 lük diziyi oyun ekranýndaki yerlere kutu olarak yerleþtirir
{
 	 char scoree[30];
 	 
	int a,b,x,y;	

	 readimagefile("arkaekran.jpg", 0, 0, 570, 630);
     readimagefile("grid.jpg", 45, 150, 515, 600);	
	  itoa (score,scoree,10); //int chara cevirir.
	  settextstyle(10, HORIZ_DIR, 1);
  	  outtextxy(250,50,"Score="); 
	  outtextxy(325,50,scoree);   
	 for(i=0;i<4;i++)
				{
					for(j=0;j<4;j++)
					{
						if(board[i][j]==2)
						  readimagefile("boxes\\2.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);                    
						else if	(board[i][j]==4)
	 					  readimagefile("boxes\\4.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
	 					else if	(board[i][j]==8)	 
					      readimagefile("boxes\\8.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==16)	 
						  readimagefile("boxes\\16.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==32)	 
						  readimagefile("boxes\\32.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==64)	 
						  readimagefile("boxes\\64.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==128)	 
						  readimagefile("boxes\\128.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==256)	 
						  readimagefile("boxes\\256.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==512)	 
						  readimagefile("boxes\\512.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==1024)	 
						  readimagefile("boxes\\1024.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);
						else if	(board[i][j]==2048)	 
						  readimagefile("boxes\\2048.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);	
				   		else if	(board[i][j]==4096)	 
						  readimagefile("boxes\\4096.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);	
						else if	(board[i][j]==8192)	 
						  readimagefile("boxes\\8192.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);  
						else if	(board[i][j]==16384)	 
						  readimagefile("boxes\\16384.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);   
						else if	(board[i][j]==32768)	 
						  readimagefile("boxes\\32768.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);   
						else if	(board[i][j]==65536)	 
						  readimagefile("boxes\\65536.bmp",(j*115)+57, ((i+1)*109)+56,(j*115)+157, ((i+1)*109)+148);   
						  
						  
						  
						  
						  
						  
					} 	
					
				}	
				
	 	swapbuffers();	 
	     
 }
 void computeLeft()       //yanyana olan ayný kutularý sol tarafta toplar
{
	
	for(i=0;i<4;i++)
						for(j=0;j<3;j++)
						{
							if(board[i][j]==board[i][j+1])
							{
								
								board[i][j]+=board[i][j+1];
								board[i][j+1]=0;
								score=score+board[i][j];
							}
						}
}	
void computeRight()         //yanyana olan kutularý sað tarafta toplar
{
	
	for(i=0;i<4;i++)
						for(j=3;j>0;j--)
						{
							if(board[i][j]==board[i][j-1])
							{
								
								board[i][j]+=board[i][j-1];
								board[i][j-1]=0;
								score=score+board[i][j];
							}
						}
}
void computeUp()      //altalta olan ayný kutularý toplayýp yukarda toplar
{
	
	for(i=0;i<4;i++)
						for(j=0;j<3;j++)
						{
							if(board[j][i]==board[j+1][i])
							{
								
								board[j][i]+=board[j+1][i];
								board[j+1][i]=0;
								score=score+board[i][j];
								
							}
						}
}
void computeDown()      //altalta olan ayný kutularý toplayýp altta toplar
{
	
	for(i=0;i<4;i++)
						for(j=3;j>0;j--)
						{
							if(board[j][i]==board[j-1][i])
							{
								
								board[j][i]+=board[j-1][i];
								board[j-1][i]=0;
								score=score+board[j][i];
							}
						}
}
void firstmoveLeft()   //kutularý sol tarafa hareket ettirir
{
	
	
	for(i=0;i<4;i++)
						for(j=0;j<4;j++)
						{
							if(!board[i][j])
							{
								for(c=j+1;c<4;c++)
									if(board[i][c])
									{
										board[i][j]=board[i][c];
										board[i][c]=0;
										break;
									}
							}
 
						}
}
void firstmoveRight()		//kutularý sað tarafa hareket ettirir
{
	

	for(i=0;i<4;i++)
						for(j=3;j>=0;j--)
						{
							if(!board[i][j])
							{
								for(c=j-1;c>=0;c--)
									if(board[i][c])
									{
										board[i][j]=board[i][c];
										board[i][c]=0;
										break;
									}
							}
 
						} 
}
void firstmoveUp()          //kutularý yukarýya hareket ettirir
{
	
	
	for(i=0;i<4;i++)
						for(j=0;j<4;j++)
						{
							if(!board[j][i])
							{
								for(c=j+1;c<4;c++)
									if(board[c][i])
									{
										board[j][i]=board[c][i];
										board[c][i]=0;
										break;
									}
							}
 
						}
}
void firstmoveDown()	 //kutularý aþaðýya hareket ettirir
{

	
	for(i=0;i<4;i++)
						for(j=3;j>=0;j--)
						{
							if(!board[j][i])
							{
								for(c=j-1;c>=0;c--)
									if(board[c][i])
									{
										board[j][i]=board[c][i];
										board[c][i]=0;
										break;
									}
							}
 
						}
}
void moveLeft()      //kutularý sol tarafa hareket ettirir

{
	
	
	
	for(i=0;i<4;i++)
						for(j=0;j<4;j++)
						{
							if(!board[i][j])
							{
								for(c=j+1;c<4;c++)
									if(board[i][c])
									{
										board[i][j]=board[i][c];
										board[i][c]=0;
										break;
									}
							}
 
						}
						
		
	

		if(control2()==1)
		{
			start();
			memcpy(temp,board,sizeof(board));
					
	}
	else
			show();	
	
	
}
void moveRight()	//kutularý sað tarafa hareket ettirir
{
	
	
	
	for(int i=0;i<4;i++)
						for(j=3;j>=0;j--)
						{
							if(!board[i][j])
							{
								for(c=j-1;c>=0;c--)
									if(board[i][c])
									{
										board[i][j]=board[i][c];
										board[i][c]=0;
										break;
									}
							}
 
						} 
						
 		if(control2()==1)
		{
			start();
			memcpy(temp,board,sizeof(board));			
	}
	else
			show();	
}
void moveUp()  //kutularý yukarýya hareket ettirir
{
	
	
	
	for(i=0;i<4;i++)
						for(j=0;j<4;j++)
						{
							if(!board[j][i])
							{
								for(c=j+1;c<4;c++)
									if(board[c][i])
									{
										board[j][i]=board[c][i];
										board[c][i]=0;
										break;
									}
							}
 
						}
			if(control2()==1)
		{
			start();
			memcpy(temp,board,sizeof(board));			
	}
	else
			show();	
}
void moveDown()       //kutularý aþaðýya hareket ettirir
{
	
		
	
	for(i=0;i<4;i++)
						for(j=3;j>=0;j--)
						{
							if(!board[j][i])
							{
								for(c=j-1;c>=0;c--)
									if(board[c][i])
									{
										board[j][i]=board[c][i];
										board[c][i]=0;
										break;
									}
							}
 
						}
				if(control2()==1)
		{
			start();
			memcpy(temp,board,sizeof(board));			
	}
	else
			show();	
}
void start()    //baslatýr ve bos yere kutu atar
{
	srand(time(NULL));
	int random,random1,random2;
		random1=0+rand()%3;
		random2=0+rand()%3;
	while(board[random1][random2]!=0)
	{
		 random1=0+rand()%3;
		random2=0+rand()%3;								 
   }
		if(board[random1][random2]==0)
	{
	 	random=2*(1+rand()%2);
			board[random1][random2]=random;
	 	}
		
	show();       //4x4 lük diziyi oyun ekranýndaki yerlere kutu olarak yerleþtirir
}

int control2()/*kullanýcý tuþa bastýðýnda oyunda deðiþiklik olup olmadýðýný kontrol eder.
Kutulardan biri deðiþtiyse yeni kutu atar.Deðiþmediyse yeni kutu atamaz.*/
{
	
	int control2=0;
	for(i=0;i<4;i++)
			{

					for(j=0;j<4;j++)
				       {
	
					     if(board[i][j]!=temp[i][j])
	                          {
			                      	control2=1;
			                        break;
	                           }
	                    }

	     	}
	
		return control2;
}
int control()     //boþta kutu olup olmadýðýný ve oynanacak hamle olup olmadýðýný kontrol eder
{
	int control=0;
	for(i=0;i<4;i++)   //bosta kutu olup olmadýðýna bakar
		{
			for(j=0;j<4;j++)
				{
					if(temp[i][j]==0 || temp[i][j]==temp[i][j+1] || temp[i][j]==temp[i+1][j])
						{
							control=1;
							
						}
				}
		}
	
		
	for(i=0;i<4;i++)        //2048 e ulasýlmýssa bitirir
		{
			for(j=0;j<4;j++)
				{
					if(temp[i][j]==2048)
						{
						control=2;
							
						}
				}
		}
	return control;	
	
}
int control3()
{
 	int control=0;
	for(i=0;i<4;i++)   //bosta kutu olup olmadýðýna bakar
		{
			for(j=0;j<4;j++)
				{
					if(board[i][j]==0 || board[i][j]==board[i][j+1] || board[i][j]==board[i+1][j])
						{
							control=1;
							
						}
				}
		}
		return control;
}
