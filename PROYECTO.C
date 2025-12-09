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
  int linX, linY, longitud = 100;
  // Círculo
  int radio = 4, ballX = 0, ballY = 0;
  // Booleanos
  int top = 1, left = 1, escPressed = 0;
  
  clear();
  printf("Introduce la posicion en X de la linea (1 - 539): ");
  scanf("%d", &linX);
  printf("Introduce la posicion en Y de la linea (1 - 199): ");
  scanf("%d", &linY);
  printf("Pulsa ESC para salir");

  video(6);

  while(escPressed == 0){
    circulo(ballX, ballY, radio, 0);
    lineaH(linX, linY, longitud, 0);

    if(kbhit()){
      char tecla = getch();

      if(tecla == 27) escPressed = 1;
      if(tecla == 0){
        tecla = getch();
        // Izquierda
        if(tecla == 75){
          if(linX > 1){
            linX -= 3;
          }
        }
        // Derecha
        if(tecla == 77){
          if(linX < (639 - longitud)){
            linX += 3;
          }
        }
      }
    }

    if(top == 1 && left == 1){
      ballX += 2;
      ballY += 2;
    }
    if(top == 1 && left == 0){
      ballX -= 2;
      ballY += 2;
    }
    if(top == 0 && left == 1){
      ballX += 2;
      ballY -= 2;
    }
    if(top == 0 && left == 0){
      ballX -= 2;
      ballY -= 2;
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
    if(ballY - radio == linY && top == 0 && ballX >= linX && ballX <= (linX + longitud)){
      top = 1;
    }
    if(ballY + radio == linY && top == 1 && ballX >= linX && ballX <= (linX + longitud)){
      top = 0;
    }
    
    lineaH(linX, linY, longitud, 1);
    circulo(ballX, ballY, radio, 1);
  }

  //getch();
  return 0;
}