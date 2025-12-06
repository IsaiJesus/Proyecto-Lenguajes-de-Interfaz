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
  int ar = 1, de = 0, ab = 0, iz = 1;
  video(6);

  printf("Introduce la altura de la linea (1 - 199): ");
  scanf("%d", &linY);
  printf("Introduce la longitud de la linea (1 - 640): ");
  scanf("%d", &longitud);
  printf("Pulsa cualquier tecla para salir");

  // Borra el enter del printf y espera a que se pulse una tecla
  fflush(stdin); 
  getch();

  clear();

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

    if(ar == 1 && iz == 1){
      ballX ++;
      ballY ++;
    }
    if(ar == 1 && de == 1){
      ballX --;
      ballY ++;
    }
    if(ab == 1 && iz == 1){
      ballX ++;
      ballY --;
    }
    if(ab == 1 && de == 1){
      ballX --;
      ballY --;
    }

    if(ballX + radio == 640){
      de = 1;
      iz = 0;
    }
    if(ballY + radio == 200){
      ab = 1;
      ar = 0;
    }
    if(ballX - radio == 0){
      iz = 1;
      de = 0;
    }
    if(ballY - radio == 0){
      ar = 1;
      ab = 0;
    }
    // Colisiones con línea horizontal
    if(ballY - radio == linY && ab == 1 && ballX >= j && ballX <= (j + longitud)){
      ar = 1;
      ab = 0;
    }
    if(ballY + radio == linY && ar == 1 && ballX >= j && ballX <= (j + longitud)){
      ar = 0;
      ab = 1;
    }
    
    lineaH(j, linY, longitud, 1);
    circulo(ballX, ballY, radio, 1);
  }

  getch();
  return 0;
}