#include <conio.h>
#include <dos.h>
#include <string.h>

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
		}	
	}
	clear_scr();
	delay(1400);
	return 0;
}
