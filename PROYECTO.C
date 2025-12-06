// x = 640, y = 200
# include <stdio.h>
# include <math.h>

void clear(){
  asm {
    MOV AH, 0;
    MOV AL, 3;
    INT 10H;
  }
}

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
  // Línea horizontal
  int linY;
  int j = 0, longitud, lat = 0;
  // Círculo
  int i, radio = 4, ballX = 0, ballY = 0;
  int top = 1, left = 1;
  
  clear();
  printf("Introduce la altura de la linea (1 - 199): ");
  scanf("%d", &linY);
  printf("Introduce la longitud de la linea (1 - 640): ");
  scanf("%d", &longitud);
  printf("Pulsa cualquier tecla para salir");

  video(6);

  while(!kbhit()){
    circulo(ballX, ballY, radio, 0);
    lineaH(j, linY, longitud, 0);

    if(lat == 0){
      j++;
      if(j >= (640 - longitud)) lat = 1;
    } else if(lat == 1){
      if(j <= 0) lat = 0;
      j--;
    }

    if(top == 1 && left == 1){
      ballX ++;
      ballY ++;
    }
    if(top == 1 && left == 0){
      ballX --;
      ballY ++;
    }
    if(top == 0 && left == 1){
      ballX ++;
      ballY --;
    }
    if(top == 0 && left == 0){
      ballX --;
      ballY --;
    }

    if(ballX + radio == 640){
      left = 0;
    }
    if(ballY + radio == 200){
      top = 0;
    }
    if(ballX - radio == 0){
      left = 1;
    }
    if(ballY - radio == 0){
      top = 1;
    }
    // Colisiones con línea horizontal
    if(ballY - radio == linY && top == 0 && ballX >= j && ballX <= (j + longitud)){
      top = 1;
    }
    if(ballY + radio == linY && top == 1 && ballX >= j && ballX <= (j + longitud)){
      top = 0;
    }
    
    lineaH(j, linY, longitud, 1);
    circulo(ballX, ballY, radio, 1);
  }

  getch();
  return 0;
}