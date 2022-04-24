#include <reg51.h>
#define LCD P3

sbit rs = P2^5;
sbit en = P2^7;
sbit in1 = P1^0;
sbit in2 = P1^1;
sbit en1 = P1^2;
sbit in3 = P1^6;
sbit in4 = P1^7;
sbit en2 = P1^5;

void forward();
void back();
void fb();
void bf();


void lcddata (unsigned char dat);
void lcdcmd (unsigned char cmd);
void msg (unsigned char b[]);


void delay (int time);

void main()
{
	lcdcmd(0x38);
	lcdcmd(0x0e);
	while(1)
	{
		forward();
		delay(500);
		back();
		delay(500);
		fb();
		delay(500);
		bf();
		delay(500);
	}
}

void forward()
{
	en1 = 1;
	en2 = 1;
	in1 = 1;
	in2 = 0;
	in3 = 1;
	in4 = 0;
	lcdcmd(0x80);
	msg("Motor 1 & 2 are");
	lcdcmd(0xC0);
	msg("Moving Forward");
}

void back()
{
	en1 = 1;
	en2 = 1;
	lcdcmd(0x80);
	msg("Motor 1 & 2 are");
	lcdcmd(0xC0);
	msg("Moving Backward");
	in1 = 0;
	in2 = 1;
	in3 = 0;
	in4 = 1;	
}

void fb()
{
	en1 = 1;
	en2 = 1;
	lcdcmd(0x80);
	msg("Motor 1-Forward");
	in1 = 1;
	in2 = 0;
	lcdcmd(0xC0);
	msg("Motor 2-Backward");
	in3 = 0;
	in4 = 1;	
}

void bf()
{
	en1 = 1;
	en2 = 1;
	lcdcmd(0x80);
	msg("Motor 1-Backward");
	in1 = 0;
	in2 = 1;
	lcdcmd(0xC0);
	msg("Motor 2-Forward");	
	in3 = 1;
	in4 = 0;
}

void lcddata (unsigned char dat)
{
	LCD = dat;
	rs = 1;
	en = 1;
	delay(10);
	en = 0;
}

void lcdcmd (unsigned char cmd)
{
	LCD = cmd;
	rs = 0;
	en = 1;
	delay(10);
	en = 0;
}


void msg(unsigned char b[]) // send string to lcd
  {
      		unsigned char s,count=0;
      		for(s=0;b[s]!='\0';s++)
        {	 
          lcddata(b[s]);
        }
  }


void delay (int time)
{
	int i, j;
	for (i=0; i<time; i++)
	for (j=0; j<1275; j++);
}
