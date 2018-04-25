bool last[240][128];
bool clean[240][128];
bool next[240][128];
int Koor[3][2];
int OKoor[3][2];
int r;
/*
Koordinates:
				0				1					2
0			Ballx		Player1x	Player2x
1			Bally		Player1y	Player2y
*/

void RDY_Ball(unsigned char cx, unsigned char cy, unsigned char radius)
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
      next[cx+i][cy+y] = 1;
      next[cx+i][cy-y] = 1;
      next[cx+y][cy+i] = 1;
      next[cx-y][cy+i] = 1;
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
  if(next[x][y] && last[x][y] == 0 && clean[x][y] == 0)
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
  if(next[x][y] == 0 && last[x][y] == 1 && clean[x][y] == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void MOVE_Ball()
{
  int cx, cy;
  //9 scenarier:
  //Ny x == Gammel x, Ny y == Gammel y, samme sted
  if(Koor[0][0] == OKoor[0][0] && Koor[0][1] == OKoor[0][1])
  {
    //Gør intet
  }
  //Ny x == Gammel x, Ny y > Gammel y, lige over
  else if(Koor[0][0] == OKoor[0][0] && Koor[0][1] > OKoor[0][1])
  {
    //Tilføger nederst på nye bold (x):
    cx = Koor[0][0]-r; // tager prikker tættest på gammel bold (x)
    cy = Koor[0][1]-r; // helt ude i den ene side (y)
    //Går over alle rækker (y)
    for(int o=0;o<=r*2;o++) //o <= da den også skal have midten med
    {
      //Går over alle pixels i denne række (x)
      for(int i=0;i<=r*2;i++) //i <= da den også skal have midten med
      {
        //Skal denne prik være sort?
        if(may_change(cx+i,cy+o))
        {
          //Sæt til sort
          GLCD_SetPixel(cx+i, cy+o, 1);
        }
        // Finder samme sted på anden cirkel
        if(should_change(cx+i,cy+o+(OKoor[0][1]-Koor[0][1])))
        {
          //Sæt til hvid
          GLCD_SetPixel(cx+i,cy+o+(OKoor[0][1]-Koor[0][1]),0);
        }
      }
    }
  }
  //Ny x == Gammel x, Ny y < Gammel y, lige under
  else if(Koor[0][0] == OKoor[0][0] && Koor[0][1] < OKoor[0][1])
  //Ny x > Gammel x, Ny y == Gammel y, lige højre
  else if(Koor[0][0] > OKoor[0][0] && Koor[0][1] == OKoor[0][1])
  //Ny x < Gammel x, Ny y == Gammel y, lige venstre
  else if(Koor[0][0] < OKoor[0][0] && Koor[0][1] == OKoor[0][1])
  //Ny x > Gammel x, Ny y > Gammel y, op højre, 1. kvadrant
  else if(Koor[0][0] > OKoor[0][0] && Koor[0][1] > OKoor[0][1])
  {

  }
  //Ny x < Gammel x, Ny y > Gammel y, op venstre, 2. kvadrant
  else if(Koor[0][0] < OKoor[0][0] && Koor[0][1] > OKoor[0][1])
  //Ny x < Gammel x, Ny y < Gammel y, ned venstre, 3. kvadrant
  else if(Koor[0][0] < OKoor[0][0] && Koor[0][1] < OKoor[0][1])
  //Ny x > Gammel x, Ny y < Gammel y, ned højre, 4- kvadrant
  else if(Koor[0][0] > OKoor[0][0] && Koor[0][1] < OKoor[0][1])
}
