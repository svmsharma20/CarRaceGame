#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <dos.h>
#include <fstream.h>
#include <myfiles/car.h>

int spd=80,level=1,score=0,Esc;

void road(int);                           //make the road
void GAME();                              //start the game
int MENU();                               //display tne menu and returns the postition of selected item
void CONTROLS();                 	  //display the contorl window
int Arrow(int,int,int);                   //retuns the postion of selected item from the menu
void Score_Sort(Score &);
void WALL(int,int);




void main()
{ clrscr();
  Score HS;
  int ch;
  while(1)
  { clrscr();

    ch=MENU();
    clrscr();
    switch(ch)
    {
     case 1:
	  score=0;
	  Esc=1;
	  GAME();

	  fstream f;
	  f.open("High_Score.DAT",ios::in | ios::out | ios::binary );
	  ofstream g("temp.dat",ios::binary);
	  if(f.fail())
	    cout<<"Unable to open the file";
	  f.seekg(0,ios::beg);
	  f.read((char*)&HS,sizeof(HS));

	  if(score>=HS.min_scr && Esc==1)
	  {
	    gotoxy(19,15);
	    cout<<"Congrtulation you have a High score";
	    delay(1000);
	    HS.scr[4]=score;

	    Score_Sort(HS);
	    HS.min_scr=HS.scr[4];

	    g.write((char*)&HS,sizeof(HS));
	    gotoxy(79,25);
	    cout<<" ";

	    getch();
	  }
	  f.close();
	  g.close();
	  remove("High_Score.DAT");
	  rename("temp.dat","High_Score.DAT");
	  break;
     case 2:
	 CONTROLS();
	 getch();
	 break;

     case 3:
	  ifstream f2;
	  f2.open("High_Score.DAT",ios::out | ios::binary);
	  if(f2.fail())
	    cout<<"unable to open the file";
	  else
	  {  gotoxy(34,5);
	     cout<<"High score";

	    f2.seekg(0,ios::beg);
	    f2.read((char*)&HS,sizeof(HS));
	    int x=19,y=6;
	    WALL(x,y);

	    for(int i=0;i<5;i++)
	    {    gotoxy(x+14,y+3+(i*2));
		 cout<<"("<<i+1<<") "<<HS.scr[i];
	    }
	  }
	  f2.close();
	   gotoxy(79,25);
	   cout<<" ";

	  getch();
	  break;

     case 4:
	 exit(0);
    };
  }
}

void Score_Sort(Score &ob)
{int s;
 for(int i=0;i<5;i++)
  for(int j=0;j<(4-i);j++)
  { if(ob.scr[j]<ob.scr[j+1])
    { s=ob.scr[j];
      ob.scr[j]=ob.scr[j+1];
      ob.scr[j+1]=s;

    }
  }
}



int MENU()
{
 int ch,f=1,x=32,y=10,opt=4;
  gotoxy(x-2,y);
  cout<<"->";
  int choice=1,k=0;
while(1)
{delay(100);
 clrscr();
 road(f);
 f=f?0:1;
 char c=18;
 gotoxy(33,7);
 cout<<"CAR RACING";
 gotoxy(32,10);
 cout<<"(1). Play";
 gotoxy(32,12);
 cout<<"(2). Controls";
 gotoxy(32,14);
 cout<<"(3). High Scores";
 gotoxy(32,16);
 cout<<"(4). Exit";
 gotoxy(26,19);
 cout<<"Select "<<c;
 gotoxy(41,19);
 c=-82;
 cout<<"Enter "<<c;
 c=-39;
 cout<<c;

 gotoxy(x-2,(y+k));
 cout<<"->";
 gotoxy(79,25);
 cout<<" ";

 if(kbhit())
 {
    union REGS i,o;
      i.h.ah=0;
      int86(22,&i,&o);

  if(o.h.ah==72 && choice>1)
  {		    //up key
      choice--;
      y=y-2;
       sound(2700);
      delay(100);
     nosound();


  }
  else if(o.h.ah==80 && choice<opt)
  {   choice++;		    //down key
       y=y+2;
       sound(2700);
       delay(100);
       nosound();

  }
  else if(o.h.ah==28)
      return (choice);

 }


}
// return (Arrow(30,10,4));
}




int Arrow(int x,int y,int opt)
{int ch=1,k=0;
 gotoxy(x-2,y);
 cout<<"->";

 while(1)
 {  gotoxy(79,25);
    cout<<" ";

    union REGS i,o;
      i.h.ah=0;
      int86(22,&i,&o);

  if(o.h.ah==72 && ch>1)
  {		    //up key
      ch--;
      gotoxy(x-2,y+k);
      cout<<"  ";
      k=k-2;
      gotoxy((x-2),(y+k));
      cout<<"->";

  }
  else if(o.h.ah==80 && ch<opt)
  {   ch++;
			    //down key
      gotoxy(x-2,y+k);
      cout<<"  ";
      k=k+2;
      gotoxy((x-2),(y+k));
      cout<<"->";

  }
  else if(o.h.ah==28)
      return (ch);

 }
}




void GAME()
{ int f=1,x=26,y=22,snd=2000,set=1;
  register int count=0;
  clrscr();
  flushall();
  car mycar(x,y),c1[6];

  while(count<6)
  {int x1=rand()%4;                  //initialising the array of car
   c1[count].setxy(pos_x[x1],0);
   count++;
  }

 while(1)
  {
    count=0;

    if(score>50 && score<100)
     {spd=75;
      level=2;
     }
    else if(score>100 && score<150)
     { spd=70;
       level=3;
     }
    else if(score>150 && score<250)
     { spd=55;
       level=4;
     }
    else if(score>250)
    { spd=50;
      level=5;
    }




    if(c1[0].posy()>4 && set<2 )
     set=2;                               //positioing 2,3,4 car with respact to each other and 1st car
    if(c1[0].posy()>4 && set<3 )
     set=3;                               //positioing 2,3,4 car with respact to each other and 1st car
    if(c1[1].posy()>4 && set<4 )
     set=4;
    if(c1[2].posy()>4 && set<5 )
     set=5;
    if(c1[3].posy()>4 && set<6 )
     set=6;                               //positioing 2,3,4 car with respact to each other and 1st car

    switch(set)
    {
     case 6:
	    score=c1[5].increment(score,mycar);
	    gotoxy(59,5);
	    cout<<score;

     case 5:
	    score=c1[4].increment(score,mycar);
	    gotoxy(59,5);
	    cout<<score;

     case 4:
	   score=c1[3].increment(score,mycar);
	   gotoxy(59,5);
	   cout<<score;

     case 3:
	   score=c1[2].increment(score,mycar);
	   gotoxy(59,5);
	   cout<<score;

     case 2:
	   score=c1[1].increment(score,mycar);
	   gotoxy(59,5);
	   cout<<score;

     case 1:
	   score=c1[0].increment(score,mycar);
	   gotoxy(59,5);
	   cout<<score;

    };
    sound(snd);

    road(f);
    f=f?0:1;
    gotoxy(58,6);
    cout<<"Score";
    gotoxy(60,40);
    gotoxy(58,8);
    cout<<(500-spd)<<" mph";
    gotoxy(58,9);
    cout<<"Speed";
    gotoxy(60,11);
    cout<<level;
    gotoxy(58,12);
    cout<<"level";

    mycar.update(x,y,f);
    if(kbhit())
    {
      union REGS i,o;
      i.h.ah=0;
      int86(22,&i,&o);
      if(o.h.ah==25)
      {
	gotoxy(30,13);
	printf("  PAUSED  ");
	nosound();
	while(kbhit()==0);             //for pausing
	gotoxy(2,1);
	printf("         ");
      }
     if(o.h.ah==1)
      {  nosound();
	 Esc=0;
	 return;
      }
     else if(o.h.ah==77)
     {  if(x<=40)                           //right key
	 x=x+6;
     }
     else if(o.h.ah==75)
     {
       if(x>=29)                            //left key
	x=x-6;
     }
     else if(o.h.ah==72)
     {  if(y>=1)                           //up key
	 y=y-1;

     }
     else if(o.h.ah==80)
     {
       if(y<=23)                            //down key
	y=y+1;
     }
     else if(o.h.ah==19)
     {int k=0;

       spd=80;
       level=1;
       set=1;
       score=0;
       while(k<6)
       { c1[k].setxy(pos_x[(rand()%4)],0);
	 k++;
       }

       clrscr();
       road(1);
       delay(500);	 				    //reset key
       x=26,y=22;
     }
    }

  while(count<set)
   {
     if(compare(mycar,c1[count]))
     {   nosound();
	 gotoxy(59,5);
	 cout<<"    ";

	 gotoxy(31,13);
	 printf("  Game Over  ");
	 gotoxy(28,14);
	 cout<<"  Total score : "<<score<<"  ";
	  gotoxy(58,6);
	  cout<<"     ";
	  gotoxy(58,8);
	  cout<<"                ";
	  gotoxy(58,9);
	  cout<<"       ";
	  gotoxy(60,11);
	  cout<<"      ";
	  gotoxy(58,12);
	  cout<<"        \n\n\n\n\n\n\n ";
	 return ;
     }
      count++;
   }
     gotoxy(79,25);
     cout<<" ";

    delay(spd);
    clrscr();

    snd+2;

 }
}



void CONTROLS()
{int x=19,y=6;
 char cl;
 gotoxy(34,5);
 cout<<"CONTROLS";


 WALL(x,y);

 cl=24;
 gotoxy(x+3,y+2);
 cout<<"Up             -              "<<cl;

 cl=25;
 gotoxy(x+3,y+4);
 cout<<"Down           -              "<<cl;

 gotoxy(x+3,y+6);
 cout<<"Left           -             <-";

 gotoxy(x+3,y+8);
 cout<<"Right          -             ->";

 gotoxy(x+3,y+10);
 cout<<"Restart        -              R";

 gotoxy(x+3,y+12);
 cout<<"Pause          -              P";

 gotoxy(x+3,y+14);
 cout<<"Exit           -             Esc";

 gotoxy(79,25);
 cout<<" ";
}


void WALL(int x,int y)
{int i=1;
 char cl2=-70,cl=-51;

 gotoxy(x,y);
 cl=-55;
 cout<<cl;

 gotoxy(x+36,y);
 cl=-69;
 cout<<cl;

 gotoxy(x,y+15);
 cl=-56;
 cout<<cl;

 gotoxy(x+36,y+15);
 cl=-68;
 cout<<cl;

 cl=-51;

 while(i<15)
 {
   gotoxy(x+i,6);
   cout<<cl;
   gotoxy(x+i,y+15);
   cout<<cl;

   gotoxy(x,y+i);
   cout<<cl2;
   gotoxy(x+36,y+i);
   cout<<cl2;
   i++;
 }
 while(i<36)
 {
   gotoxy(x+i,6);
   cout<<cl;
   gotoxy(x+i,y+15);
   cout<<cl;
   i++;
 }
}





void road(int flag)
{ int x=37;
register int y=2;
  char a=-77;
  int k=flag;
  for(y=1;y<=25;y++)
  {  gotoxy(x-12,y);
     cout<<a;
     gotoxy(x+12,y);
     cout<<a;
      if(k)
      {
       gotoxy(x,y);
       cout<<"|";
       k=0;
      }
     else
       k=1;
   }
}
