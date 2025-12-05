# include <stdio.h>
# include <math.h>

void video(char n){
  asm {
    MOV AH, 0;
    MOV AL, n;
    INT 10H;
  }
}

void pixel(int x, int y, char color){
  asm {
    MOV AH, 12;
    MOV DX, y;
    MOV CX, x;
    MOV AL, color;
    INT 10H;
  }
}

void circulo(int x, int y, int r, char color){
  int i;
  for(i = 0; i < 360; i++){
    pixel(x + r * cos(i * M_PI / 180), y + r * sin(i * M_PI / 180), color);
  }
}

void lineaH(int x, int y, int longitud, char c){
  int i;
  for(i = x; i < (x + longitud); i++){
    pixel(i, y, c);
  }
}

int main(){
  int i, j, longitud = 80;
  video(6);

  while(!kbhit()){
    delay(50);
    for(i = 4; i > 0; i--){
      circulo(4, 4, i, 1);
    }
    for(j = 0; j < (640 - longitud); j++){
      if(kbhit()) break;
      lineaH(j, 100, longitud, 1);
      lineaH(j, 100, longitud, 0);
    }
    for(j = (640 - longitud); j > 0; j--){
      if(kbhit()) break;
      lineaH(j, 100, longitud, 1);
      lineaH(j, 100, longitud, 0);
    }
  }

  getch();
  return 0;
}