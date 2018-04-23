/*int p1_state1;
int p1_state2;

int p2_state1;
int p2_state2;*/

int p1_value = 100;
int p2_value = 100;

int h1_value = 127;
int h2_value = 127;

int val[2][4];

int diff1 = 0;
int diff2 = 0;
/*
Val:
ID: 			0						1						 2							3
Name: p1_state1, p1_state2, p1speed_state1, p1speed_state2		0
Name: p2_state1, p2_state2, p2speed_state1, p2speed_state2		1

eks: p1_state2 == val[0][1]
*/

int sendstat = 0;
int overflow = 0;

int smart[8] = {
	1, 2, 4, 8, 16, 32, 64, 128, 256
};

void rot1()
{
  //Placerring encoder 1
	if (!(PINC & smart[0]) && !(PINC & smart[1])){
		val[0][1] = 1;
	}
	else if ((PINC & smart[0]) && !(PINC & smart[1])) {
		val[0][1] = 2;
	}
	else if ((PINC & smart[0]) && (PINC & smart[1])) {
		val[0][1] = 3;
	}
	else if (!(PINC & smart[0]) && (PINC & smart[1])){
		val[0][1] = 4;
	}

	//pos
	if (val[0][0] == 1 && val[0][1] == 4) //Takker under bunden
	{
		if (p1_value>0){
			p1_value--;
		}
	}
	else if (val[0][0] == 4 && val[0][1] == 1) //Takker over toppen
	{
		if (p1_value<255){
			p1_value++;
		}
	}
  /*else if(val[1][0] > val[1][1]) //Drejer ned:
  {
    if (p1_value>0){
			p1_value--;
		}
  }
  else if (val[1][0] < val[1][1]) //Drejer op:
  {
    if (p1_value<255){
			p1_value++;
		}
  }*/

  val[0][0] = val[0][1];
}

void speed1()
{
  //Placerring encoder 1
	if (!(PINC & smart[2]) && !(PINC & smart[3])){
		val[0][3] = 1;
	}
	else if ((PINC & smart[2]) && !(PINC & smart[3])) {
		val[0][3] = 2;
	}
	else if ((PINC & smart[2]) && (PINC & smart[3])) {
		val[0][3] = 3;
	}
	else if (!(PINC & smart[2]) && (PINC & smart[3])){
		val[0][3] = 4;
	}

	//SPEED
	if (val[0][2] == 1 && val[0][3] == 4) //Takker under bunden
	{
		h1_value--;
	}
	else if (val[0][2] == 4 && val[0][3] == 1) //Takker over toppen
	{
		h1_value++;
	}
	else if(val[0][2] > val[0][3]) //Drejer ned:
  {
		h1_value--;
  }
  else if (val[0][2] < val[0][3]) //Drejer op:
  {
		h1_value++;
  }

	val[0][2] = val[0][3];
}

void rot2()
{
  // Placering encoder 2
	if (!(PINC & smart[4]) && !(PINC & smart[5])){
		val[1][1] = 1;
	}
	else if ((PINC & smart[4]) && !(PINC & smart[5])) {
		val[1][1] = 2;
	}
	else if ((PINC & smart[4]) && (PINC & smart[5])) {
		val[1][1] = 3;
	}
	else if (!(PINC & smart[4]) && (PINC & smart[5])){
		val[1][1] = 4;
	}

	//Pos
	if (val[1][0] == 1 && val[1][1] == 4){
		if (p2_value>0){
			p2_value --;
		}
	}
	else if (val[1][0] == 4 && val[1][1] == 1){
		if (p2_value<255){
			p2_value++;
		}
	}
	/*else if(p2_state1 > p2_state2) //Drejer ned:
	{
	if (p2_value>0){
	p2_value--;
	}
	}
	else if (p2_state1 < p2_state2) //Drejer op:
	{
	if (p2_value<255){
	p2_value++;
	}
	}*/
	val[1][0] = val[1][1];
}

void speed2()
{
  //Placerring encoder 1
	if (!(PINB & smart[1]) && !(PINB & smart[2])){
		val[1][3] = 1;
	}
	else if ((PINB & smart[1]) && !(PINB & smart[2])) {
		val[1][3] = 2;
	}
	else if ((PINB & smart[1]) && (PINB & smart[2])) {
		val[1][3] = 3;
	}
	else if (!(PINB & smart[1]) && (PINB & smart[2])){
		val[1][3] = 4;
	}

	//SPEED
	if (val[1][2] == 1 && val[1][3] == 4) //Takker under bunden
	{
		h2_value--;
	}
	else if (val[1][2] == 4 && val[1][3] == 1) //Takker over toppen
	{
		h2_value++;
	}
	else if(val[1][2] > val[1][3]) //Drejer ned:
  {
		h2_value--;
  }
  else if (val[1][2] < val[1][3]) //Drejer op:
  {
		h2_value++;
  }

	val[1][2] = val[1][3];
}
