
/*	This is a default program--
	Use File->Load Prog to load a different program
*/
//A0=05
//A1=04
//A2=03
//A3=02
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(0);

const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
int velocity = 1000;


//////////////////
void setup()
{
	//leduri
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	
	//butoan	
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	
	lcd.begin(16,2); // sixteen characters across - 2 lines
	lcd.setBacklight(HIGH);
	lcd.setCursor(0,0);
	lcd.print("Press Button ");
	// 2nd line 
	lcd.setCursor(1,1);
	lcd.print("to start game");
	
	
}

void loop()
{
	
	if (level == 1 && digitalRead(11) == LOW ){	// generate a sequence if button is pressed
		lcd.clear();
		generateSequence();//generate a sequence;
	}
	
	
	if (digitalRead(11) == LOW || level != 1) //If start button is pressed or you're winning
	{  
		showSequence();    //show the sequence
		getSequence();     //wait for your sequence
	}
	
}


//////////////////////show_sequence
void showSequence()
{
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	
	for (int i = 0; i < level; i++)
	{
		digitalWrite(sequence[i], HIGH);
		delay(velocity);
		digitalWrite(sequence[i], LOW);
		delay(500);
	}
}

/////////////////////////generate_sequence
void generateSequence()
{
	
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		sequence[i] = random(2,6);//gener. random seq from 2 to 5 
	}
}
////////////////////////////

void getSequence()
{
	int flag = 0; //this flag indicates if the sequence is correct
	
	for (int i = 0; i < level; i++)
	{
		flag = 0;
		while(flag == 0)
		{
			if (digitalRead(A0) == LOW)
			{
				digitalWrite(5, HIGH);
				your_sequence[i] = 5;
				flag = 1;
				delay(1500);
				if (your_sequence[i] != sequence[i])
				{
					wrongSequence();
					return;
				}
				digitalWrite(5, LOW);
			}
			
			if (digitalRead(A1) == LOW)
			{
				digitalWrite(4, HIGH);
				your_sequence[i] = 4;
				flag = 1;
				delay(1500);
				if (your_sequence[i] != sequence[i])
				{
					wrongSequence();
					return;
				}
				digitalWrite(4, LOW);
			}
			
			if (digitalRead(A2) == LOW)
			{
				digitalWrite(3, HIGH);
				your_sequence[i] = 3;
				flag = 1;
				delay(1500);
				if (your_sequence[i] != sequence[i])
				{
					wrongSequence();
					return;
				}
				digitalWrite(3, LOW);
			}
			
			if (digitalRead(A3) == LOW)
			{
				digitalWrite(2, HIGH);
				your_sequence[i] = 2;
				flag = 1;
				delay(1500);
				if (your_sequence[i] != sequence[i])
				{
					wrongSequence();
					return;
				}
				digitalWrite(2, LOW);
			}
			
		}
	}
	rightSequence();
}
////////////////////////////

void wrongSequence()
{
	for (int i = 0; i < 3; i++)
	{
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Game Over!");
		delay(250);
		digitalWrite(2, HIGH);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
		digitalWrite(5, HIGH);
		delay(500);
		////////////////////
		digitalWrite(2, LOW);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		delay(500);
	}
	level = 1;
	velocity = 1000;
}


///////////////////////right_sequence
void rightSequence()
{
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	delay(500);
	digitalWrite(2, HIGH);
	digitalWrite(3, HIGH);
	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	delay(500);
	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	delay(500);
	
	if (level < MAX_LEVEL)
		level++;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Nivelul curent: ");
	// 2nd line 
	lcd.setCursor(8,1);
	lcd.print(level);
	
	velocity -= 50; //increase difficulty
}
