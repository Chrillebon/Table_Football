///Debug.h
//Bruges til at skrive værdier til vores midlertidige 4x7 segments display

void rensinput() // renser input, så vi kan bruge det
{
	int i, val;
	for(i = 0; i < globsize; i++)
	{
		//mellemrum bliver oversat
		if(SoonToBe[i] == ' ')
		{
			SoonToBe[i] = 0b00000000;
		}
		//bindestrej bliver oversat
		if(SoonToBe[i] == '@')
		{
			SoonToBe[i] = 0b01000000;
		}
		//indsæt flere her hvis behov:
		if(SoonToBe[i] == ',')
		{
			SoonToBe[i] = 0b00010000;
		}
		val = SoonToBe[i];
		if(val > 57)
		{
			SoonToBe[i] = 0x00;
		}
	}
}


int givemechar(char tegn) //Brugt i forbindelse med display
{
  //Ascii værdier til 7 segmentsdisplay værdier
	if(tegn == 44){ return 16; } //Komma
	if(tegn<64) //Tal
	{
		return NUMBERS[tegn-48];
	}
	if(tegn==64) return 64; //Snabel-a (aftalt som bindestrej)
	return ALPHABET[tegn-65]; //Bogstaver, hvis de skal bruges
}

void display(int t) //Oversættelse fra hvad man skal læse til hvad der står på displayet
{
	//løkker der går gennem de fire cifre på displayet
	int i;
	for(i = 0; i < 4; i++)
	{
		//sætter dette ciffer til at være hvad der står i variablen
		//Så at det ser ud somom at det bevæger sig.
		char local = SoonToBe[t+i];
		if(t+i > globsize+3)
		{
			char local = SoonToBe[t-globsize+i-4];
			choices[i] = givemechar(local);

		}
		else if(local <= 43 || local >= 100)
		{
			choices[i] = 0b00000000;
		}
		else
		{
			char local = SoonToBe[t+i];
			choices[i] = givemechar(local);
		}
	}
}

void Light_It_Up(int i)
{
	rensinput();
	if(i!=3)
	{
		PORTC = PORTC | 0b01111111;
		PORTD = PORTD & 0b10000111;
		PORTD = PORTD | DISPLAYS[i];
		PORTC = PORTC & ((~ choices[i]) | 0b10000000);
	}
	//Timere der tæller opad
	Global_Time++;
}

int size(char Input[])
{
	int size=0;
	for(int i=0;i<100;i++)
	{
		char tegn = Input[i];
		if(tegn>0)
		{
			size++;
		}
		else
		{
			return size;
		}
	}
	return 0;
}

void debug()
{
	char SoonSoonToBe[5];   //Display Values!!
	sprintf(SoonSoonToBe, "%d", handle[3]);

	SoonToBe = SoonSoonToBe;
	globsize = size(SoonToBe);
	rensinput();

	display(t); //Gør klar til hvad der skal stå på display

	Light_It_Up(this); //Tænder rent faktisk lyset i displays


	if(Global_Time > 1.5*1000) //rykker bogstaver og tal på display efter tid
	{
		if(globsize>4) t++;
		Global_Time = 0;
	}

	//Går igennem alle mulige bogstaver/tal til der er blankt display, og starter igen.
	if(t > globsize+3)
	{
		t = 0;
	}


	//Tæller display op
	this++;
	if(this>=4)
	{
		this = 0;
	}
}
