// x = 640, y = 200
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
  int i, radio = 4, ballX = 0, ballY = 0;
  int j = 0, longitud = 80, lat = 0;
  video(6);

  while(!kbhit()){
    circulo(ballX, ballY, radio, 0);
    lineaH(j, 100, longitud, 0);

    if(lat == 0){
      j++;
      if(j >= (640 - longitud)) lat = 1;
    } else if(lat == 1){
      if(j <= 0) lat = 0;
      j--;
    }
    ballX ++;
    ballY ++;
    
    lineaH(j, 100, longitud, 1);
    circulo(ballX, ballY, radio, 1);
  }

  getch();
  return 0;
}