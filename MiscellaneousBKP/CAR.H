#include<graphics.h>
#include<string.h>

int pos_x[4]={26,32,38,44};

class Score
{ public:
    int scr[5];
    int min_scr;
    Score();
    int get_minscore();

};
Score :: Score()
    {
      int i=0;

      while(i<5)
      { scr[i]=0;
	i++;
      }
      min_scr=0;
    }

int Score :: get_minscore()
{
  return  min_scr;
}




class car
{ int x, y;
 public:

  car(){x=pos_x[(rand()%4)];y=0;}
  car(int x1,int y1)
  { x=x1;
    y=y1;
  }
  car(car &ob)
  {
   x=ob.x;
   y=ob.y;
  }
  void update(int,int,int);
  int increment(int,car);
  void setxy(int,int);
  int posy();
  int posx();
  friend int compare(car,car);
};

void car::update(int x,int y,int flg)
{char a=7,d=-49,e=-51,f=-59,b;
if(flg)
 b=-37;
else
 b=-78;
 gotoxy(x+1,y);
 cout<<a<<b<<f<<b;
 gotoxy(x,y+1);
 cout<<b<<e<<d<<e<<b;
 setxy(x,y);
}

int car::increment(int s,car ob)
{static int fl=1;
 char a=7,b=-79,d=-49,e=-51,f=-59;
  if(y>23)
    { y=1;
      fl=1;
      x=pos_x[(rand()%4)];
    }
  else
    y++;
  if(y+2>ob.y && fl==1)
   {s++;
    fl=0;
   }
// setcolor(2);
 gotoxy(x+1,y);
 cout<<a<<b<<f<<b;
 gotoxy(x,y+1);
 cout<<b<<e<<d<<e<<b;
 return s;
}

void car::setxy(int x0,int y0)
{  x=x0;
   y=y0;
}
int car :: posy()
{ return y;}

int car :: posx()
{ return x;}

int compare(car ob1,car ob2)
{ if((ob1.x==ob2.x)&&(ob1.y==ob2.y+1 || ( (ob1.y+1)==ob2.y) ))
      return 1;
  return 0;
}