#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int r = 2;
bool last[12][24] = {
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0
};
bool clean[12][24] = {
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0
};
bool newboard[12][24];
int Koor[3][2];
int OKoor[3][2];
/*
Koordinates:
0				1					2
0			Ballx		Player1x	Player2x
1			Bally		Player1y	Player2y
*/
bool BFSvisited[12][24];
queue<tuple<int,int,int>> pixel;
// <x, y, dybde>

void print()
{
  for(int i=0;i<12;i++)
  {
    for(int o=0;o<24;o++)
    {
      if(last[i][o])
      {
        std::cout << "#" << " ";
      }
      else
      {
        std::cout << "." << " ";
      }
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void RDY_Circle(unsigned char cx, unsigned char cy, unsigned char radius)
{
int x, y, xchange, ychange, radiusError;
x = radius;
y = 0;
xchange = 1 - 2 * radius;
ychange = 1;
radiusError = 0;
while(x >= y)
  {
    for(int i=-x;i<=x;i++)
    {
      newboard[cy+y][cx+i] = 1;
      newboard[cy-y][cx+i] = 1;
      newboard[cy+i][cx+y] = 1;
      newboard[cy+i][cx-y] = 1;
    }
    y++;
    radiusError += ychange;
    ychange += 2;
    if ( 2*radiusError + xchange > 0 )
    {
      x--;
    	radiusError += xchange;
    	xchange += 2;
  	}
  }
}

bool may_change(int x, int y)
{
  //Skal ændres fra hvid til sort for at returnere true
  if(newboard[y][x] && last[y][x] == 0 && clean[y][x] == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool should_change(int x, int y)
{
  //Skal ændres fra sort til hvid for at returnere true
  if(newboard[y][x] == 0 && last[y][x] == 1 && clean[y][x] == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void change(int x, int y)
{
  int difx = OKoor[0][0]-Koor[0][0]; //ændringen i x
  int dify = OKoor[0][1]-Koor[0][1]; //ændringen i y
  std::cout << "vil gerne ændre: " <<x<<", "<<y<< '\n';
  if(may_change(x,y))
  {
    last[y][x] = 1; //Skriv til display
  }
  std::cout << "vil gerne ændre: " <<x+difx<<", "<<y+dify<< '\n';
  if(should_change(x+difx,y+dify))
  {
    last[y+dify][x+difx] = 0; //Skriv til display
  }
}

void BFSset()
{
  while(!pixel.empty()) //Fjerner alle elementer
  {
    pixel.pop();
  }
  for(int i=0;i<24;i++)
  {
    for(int o=0;o<12;o++)
    {
      BFSvisited[o][i] = 0; //Nu har den ikke besøgt nogen overhovedet
    }
  }
}

void BFS(int x, int y, int cx, int cy, int dx, int dy)
{
  int d = get<2>(pixel.front()), negativx = 1,negativy = 1;
  pixel.pop();
  if(BFSvisited[y][x] || x < cx-r || x > cx+r || y < cy-r || y > cy+r) //Har været her før, eller er uden for
  {
    return; //Stop denne gren
  }
  BFSvisited[y][x] = true; //Nu har den været her
  change(x,y); //Skift pixel på display

  if(dx < 0) //Hvilken retning den skal gå x:
  {
    negativx = -1;
  }
  else
  {
    negativx = 1;
  }
  if(dy < 0) //Hvilken retning den skal gå y:
  {
    negativy = -1;
  }
  else
  {
    negativy = 1;
  }
  //Gå videre omkring
  for(int i=0;abs(i)<abs(dx);i=i+negativy) //Gå antallet dx i retningen y
  {
    if(y+i >= 0 && y+i < 12) //Inden for grænserne af displayet/Spillebanen
    {
      pixel.push(make_tuple(x,y+i,d+1)); //Ny pixel i puljen
    }
  }
  for(int i=0;abs(i)<abs(dy);i=i+negativx) //Gå antallet dy i retningen x
  {
    if(x+i >= 0 && x+i < 24) //Inden for grænserne af displayet/Spillebanen
    {
      pixel.push(make_tuple(x+i,y,d+1)); //Ny pixel i puljen
    }
  }
  //Slut
}

void MOVE_Ball()
{
  int dx = Koor[0][0]-OKoor[0][0];
  int dy = Koor[0][1]-OKoor[0][1];

  BFSset(); //Så skal vi i gang med BFS
  //9 scenarier:
  //Ny x == Gammel x, Ny y == Gammel y, samme sted--------------------------------------------------
  if(Koor[0][0] == OKoor[0][0] && Koor[0][1] == OKoor[0][1])
  {
    //Gør intet
  }
  //Ny x == Gammel x, Ny y > Gammel y, lige over----------------------------------------------------
  else if(Koor[0][0] == OKoor[0][0] && Koor[0][1] < OKoor[0][1])
  {
    //Tilføger nederst på nye bold (y):
    // tager prikker tættest på gammel bold (y)
    // helt ude i den ene side (x)
    int l = 0;
    pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]+r,0));
    while(!BFSvisited [Koor[0][1]+r] [Koor[0][0]+r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(!pixel.empty()) //Skal blive ved til der ikke er flere i køen
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      l++; //Gå videre til næste lag
      // Tag den næste (Næste er op, hvilket reducerer y)
      pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]+r-l,l));
    }
  }
  //Ny x == Gammel x, Ny y < Gammel y, lige under----------------------------------------------------
  else if(Koor[0][0] == OKoor[0][0] && Koor[0][1] > OKoor[0][1])
  {
    //Tilføger øverst på nye bold (y):
    // tager prikker tættest på gammel bold (y)
    // helt ude i den ene side (x)
    int l = 0;
    pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]-r,0));
    while(!BFSvisited [Koor[0][1]-r] [Koor[0][0]+r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(!pixel.empty()) //Skal blive ved til der ikke er flere i køen
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      l++; //Gå videre til næste lag
      // Tag den næste (Næste er ned, hvilket øger y)
      pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]-r+l,l));
    }
  }
  //Ny x > Gammel x, Ny y == Gammel y, lige højre----------------------------------------------------
  else if(Koor[0][0] > OKoor[0][0] && Koor[0][1] == OKoor[0][1])
  {
    // Tilføger venstre på nye bold (x):
    // tager prikker tættest på gammel bold (x)
    // helt ude i den ene side (y)
    int l = 0;
    pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]-r,0));
    while(!BFSvisited [Koor[0][1]+r] [Koor[0][0]+r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(!pixel.empty()) //Skal blive ved til der ikke er flere i køen
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      l++; //Gå videre til næste lag
      // Tag den næste (næste er højre, hvilket øger x)
      pixel.push(make_tuple(Koor[0][0]-r+l,Koor[0][1]-r,l));
    }
  }
  //Ny x < Gammel x, Ny y == Gammel y, lige venstre----------------------------------------------------
  else if(Koor[0][0] < OKoor[0][0] && Koor[0][1] == OKoor[0][1])
  {
    // Tilføger højre på nye bold (x):
    // tager prikker tættest på gammel bold (x)
    // helt ude i den ene side (y)
    int l = 0;
    pixel.push(make_tuple(Koor[0][0]+r,Koor[0][1]-r,0));
    while(!BFSvisited [Koor[0][1]+r] [Koor[0][0]-r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(!pixel.empty()) //Skal blive ved til der ikke er flere i køen
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      l++; //Gå videre til næste lag
      // Tag den næste (næste er venstre, hvilket reducerer x)
      pixel.push(make_tuple(Koor[0][0]+r-l,Koor[0][1]-r,l));
    }
  }
  //Ny x > Gammel x, Ny y > Gammel y, op højre, 1. kvadrant----------------------------------------------------
  else if(Koor[0][0] > OKoor[0][0] && Koor[0][1] < OKoor[0][1])
  {
    // Tilføger ned venstre på nye bold (x,y):
    // tager prikker tættest på gammel bold (x,y)
    int d = 0;
    pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]+r,d));
    while(!BFSvisited [Koor[0][1]-r] [Koor[0][0]+r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(get<2>(pixel.front()) <= d) //Så længe den kan holde sig i samme dybde
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      d++; //Gå videre til næste dybde
    }
  }
  //Ny x < Gammel x, Ny y > Gammel y, op venstre, 2. kvadrant----------------------------------------------------
  else if(Koor[0][0] < OKoor[0][0] && Koor[0][1] < OKoor[0][1])
  {
    // Tilføger ned højre på nye bold (x,y):
    // tager prikker tættest på gammel bold (x,y)
    int d = 0;
    pixel.push(make_tuple(Koor[0][0]+r,Koor[0][1]+r,d));
    while(!BFSvisited [Koor[0][1]-r] [Koor[0][0]-r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(get<2>(pixel.front()) <= d) //Så længe den kan holde sig i samme dybde
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      d++; //Gå videre til næste dybde
    }
  }
  //Ny x < Gammel x, Ny y < Gammel y, ned venstre, 3. kvadrant----------------------------------------------------
  else if(Koor[0][0] < OKoor[0][0] && Koor[0][1] > OKoor[0][1])
  {
    // Tilføger op højre på nye bold (x,y):
    // tager prikker tættest på gammel bold (x,y)
    int d = 0;
    pixel.push(make_tuple(Koor[0][0]+r,Koor[0][1]-r,d));
    while(!BFSvisited [Koor[0][1]+r] [Koor[0][0]-r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      while(get<2>(pixel.front()) <= d) //Så længe den kan holde sig i samme dybde
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      d++; //Gå videre til næste dybde
    }
  }
  //Ny x > Gammel x, Ny y < Gammel y, ned højre, 4- kvadrant----------------------------------------------------
  else if(Koor[0][0] > OKoor[0][0] && Koor[0][1] > OKoor[0][1])
  {
    // Tilføger op venstre på nye bold (x,y):
    // tager prikker tættest på gammel bold (x,y)
    int d = 0;
    pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]-r,d));
    while(!BFSvisited [Koor[0][1]+r] [Koor[0][0]+r] )//Så længe den ikke har besøgt modsatte hjørne
    {
      std::cout << "starter i: " <<get<0>(pixel.front())<<", "<<get<1>(pixel.front())<< '\n';
      while(get<2>(pixel.front()) <= d) //Så længe den kan holde sig i samme dybde
      {
        BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy);
      }
      print();
      d++; //Gå videre til næste dybde
    }
  }
}

/*
Gennerel purpose:--------------------------------------------------------------------------------------------)

//Tilføger nederst på nye bold (x):
// tager prikker tættest på gammel bold (x)
// helt ude i den ene side (y)
int d = 0;
pixel.push(make_tuple(Koor[0][0]-r,Koor[0][1]-r,d));
while(!BFSvisited [Koor[0][1]+r] [Koor[0][0]+r] )//Så længe den ikke har besøgt modsatte hjørne
{
  while(get<2>(pixel.front()) <= d) //Så længe den kan holde sig på samme lag
  {
    BFS(get<0>(pixel.front()), get<1>(pixel.front()), Koor[0][0], Koor[0][1], dx, dy)
    // Tag den næste
  }
  //Hvis den forbliver i samme række/kolonne
  //Ellers
  d++; //Gå videre til næste dybde
}
*/


int main()
{
  OKoor[0][0] = 3;
  OKoor[0][1] = 6;
  int changex, changey;
  std::cout << "velkommen til min test af dette program" << '\n';
  std::cout << "indtast venligt hvor du vil hen herfra:" << '\n'<< '\n';
  print();
  std::cout << "indtast først x: ";
  std::cin >> changex;
  std::cout << "Og så skal du indtaste y: ";
  std::cin >> changey;
  std::cout << '\n';
  Koor[0][0] = changex;
  Koor[0][1] = changey;
  RDY_Circle(changex, changey, r);
  MOVE_Ball();
  std::cout << "virker så godt" << '\n';
  return 0;
}
