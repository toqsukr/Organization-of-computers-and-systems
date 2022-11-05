#include <conio.h>
#include <dos.h>
#include <string.h>

enum {ENTIRE, UP = 6, DOWN};

void scroll(int dir, char lRow, char lCol, char rRow, char rCol, char attr){
	union REGS r;
	if (dir)
	{
		r.h.ah = dir + 1;
		r.h.al = 1;
	} else {
		r.h.ah = 6;
		r.h.al = 0;
	}
	r.h.bh = attr;
	r.h.ch = lRow;
	r.h.cl = lCol;
	r.h.dh = rRow;
	r.h.dl = rCol;
	int86(0x10, &r, &r);
}

void clear_scr(){
	for(int k = 0;k < 5;k++){
		gotoxy(1, 9 - 2*k);
		clreol();
		delay(1400);
	}
	textbackground(BLACK);
	clrscr();
}

int main(){
	
	enum colors {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY,
		DARKGRAY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};
	
	char color_name[][16] = {
		"BLACK",
		"BLUE",
		"GREEN",
		"CYAN",
		"RED",
		"MAGENTA",
		"BROWN",
		"LIGHTGRAY",
		"DARKGRAY",
		"LIGHTBLUE",
		"LIGHTGREEN",
		"LIGHTCYAN",
		"LIGHTRED",
		"LIGHTMAGENTA",
		"YELLOW",
		"WHITE"
	};
	
	int x1 = 15, y1 = 10, x2 = 65, y2 = 20;
	window(x1, y1, x2, y2);
	for(int i = 0;i < 8;i++){
		textbackground(colors(i));
		for(int j = 0;j < 16;j++){
			textcolor(colors(j));
			insline();
			cprintf("\r");
			cprintf("Background color num: %d, Text color: %s\r\n\n", i, color_name[j]);
			delay(1400);
			scroll(DOWN, x1 - 1, y1 - 1, x2 - 1, y2 - 1, colors(i));
		}	
	}
	clear_scr();
	delay(1400);
	return 0;
}
