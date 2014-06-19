#define BLANK 0
#define PLAYER1 1
#define PLAYER2 2

int board[8][8];
int currentPlayer;

void cls() {
  Serial.write(27);
  Serial.print("[2J");
}

void initGame() {
  board = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,2,1,0,0,0},
    {0,0,0,1,2,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
  };
  currentPlayer = PLAYER1;
}

void drawBoard() {
  int i,n;
  int o=0;
  int x=0;
  cls();
  Serial.println("   +---+---+---+---+---+---+---+---+");
  for (i=0;i<8;i++) {
    Serial.print(" "); 
    Serial.print(i+1);
    Serial.print(" | ");
    for (n=0;n<8;n++) {
      switch(board[i][n]) {
        case 0 :
          Serial.print(" ");
          break;
        case 1:
          Serial.print("O");
          o++;
          break;
        case 2:
          Serial.print("X");
          x++;
          break;
      }
      Serial.print(" | ");
    }
    Serial.println();
    Serial.println("   +---+---+---+---+---+---+---+---+");
  }
  Serial.println("     A   B   C   D   E   F   G   H");
  Serial.print("Player:");
  Serial.print(o);
  Serial.print(" Computer:");
  Serial.println(x);
  Serial.println();
  //printf("O: %d, X: %d\n",o,x);
}

int countNeighbours(int p,int y, int x) {
  int n = 0;
  //left  
  if ((x>0)&&(board[y][x-1] == p)) {
    n++;
  }

  //right
  if ((x<7)&&(board[y][x+1] == p)) {
    n++;
  }

  //top
  if ((y>0)&&(board[y-1][x] == p)) {
    n++;
  }

  //bottom
  if ((y<7)&&(board[y+1][x] == p)) {
    n++;
  }

  //top left
  if ((x>0)&&(y>0)&&(board[y-1][x-1] == p)) {
    n++;
  }

  //top right
  if ((x<7)&&(y>0)&&(board[y-1][x+1])) {
    n++;
  }

  //bottom left
  if ((x>0)&&(y<7)&&(board[y+1][x-1])) {
    n++;
  }

  //bottom right
  if ((x<7)&&(y<7)&&(board[y+1][x+1])) {
    n++;
  }

  return n;
}

void doFlip(int p,int y, int x) {
  int i,n;
  int tmpBoard[8][8];
  int okay = 0;
  int otherPlayer;
  if (p == PLAYER1) {
    otherPlayer = PLAYER2;
  } else {
    otherPlayer = PLAYER1;
  }

  //copy board
  for (i=0;i<8;i++) {
    for (n=0;n<8;n++) {
      tmpBoard[i][n] = board[i][n];
    }
  }
  
  //left
  okay = 0;
  for (i=x-1;i>=0;i--) {
    if (board[y][i] == p) {
      okay = 1;
      break;
    } else if (board[y][i] == BLANK) {
      break;
    }
  }  
  if (okay) {
    for (i=x-1;i>=0;i--) {
      if (board[y][i] == otherPlayer) {
         tmpBoard[y][i] = p;
      } else {
      	break;
      }	
    }
  }
  //done left

  //right
  okay = 0;
  for (i=x+1;i<8;i++) {
    if (board[y][i] == p) {
      okay = 1;
      break;
    } else if (board[y][i] == BLANK) {
      break;
    }
  }
  if (okay) {
    for (i=x+1;i<8;i++) {
      if (board[y][i] == otherPlayer) {
        tmpBoard[y][i] = p;
      } else {
        break;
      }
    }
  }

  //bottom
  okay = 0;
  for (i=y-1;i>=0;i--) {
    if (board[i][x] == p) {
      okay = 1;
      break;
    } else if (board[i][x] == BLANK) {
      break;
    }
  }
  if (okay) {
    for (i=y-1;i>=0;i--) {
      if (board[i][x] == otherPlayer) {
         tmpBoard[i][x] = p;
      } else {
          break;
      }
    }
  }

  //top
  okay = 0;
  for (i=y+1;i<8;i++) {
    if (board[i][x] == p) {
      okay = 1;
      break;
    } else if (board[i][x] == BLANK) {
      break;
    }
  }
  if (okay) {
    for (i=y+1;i<8;i++) {
      if (board[i][x] == otherPlayer) {
         tmpBoard[i][x] = p;
      } else {
          break;
      }
    }
  }

  //top right
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x+1+i < 8)&&(y-1-i >= 0)) {
      if (board[y-1-i][x+1+i] == p) {
        okay = 1;
        break;
      } else if (board[y-1-i][x+1+i] == BLANK) {
	break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x+1+i < 8)&&(y-1-i >= 0)) {
        if (board[y-1-i][x+1+i] == otherPlayer) {
          tmpBoard[y-1-i][x+1+i] = p;
        } else {
          break;
        }
      } 
    }
  }

  //bottom left
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x-1-i >= 0)&&(y+1+i < 8)) {
      if (board[y+1+i][x-1-i] == p) {
        okay = 1;
        break;
      } else if (board[y+1+i][x-1-i] == BLANK) {
        break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x-1-i >= 0)&&(y+1+i < 8)) {
        if (board[y+1+i][x-1-i] == otherPlayer) {
          tmpBoard[y+1+i][x-1-i] = p;
        } else {
          break;
        }
      }
    }
  }

  //top left
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x-1-i >= 0)&&(y-1-i >= 0)) {
      if (board[y-1-i][x-1-i] == p) {
        okay = 1;
        break;
      } else if (board[y-1-i][x-1-i] == BLANK) {
        break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x-1-i >= 0)&&(y-1-i >= 0)) {
        if (board[y-1-i][x-1-i] == otherPlayer) {
          tmpBoard[y-1-i][x-1-i] = p;
        } else {
          break;
        }
      }
    }
  }
  
  //bottom right
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x+1+i < 8)&&(y+1+i < 8)) {
      if (board[y+1+i][x+1+i] == p) {
        okay = 1;
        break;
      } else if (board[y+1+i][x+1+i] == BLANK) {
        break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x+1+i < 8)&&(y+1+i < 8)) {
        if (board[y+1+i][x+1+i] == otherPlayer) {
          tmpBoard[y+1+i][x+1+i] = p;
        } else {
          break;
        }
      }
    }
  }

  //copy board back
  for (i=0;i<8;i++) {
    for (n=0;n<8;n++) {
      board[i][n] = tmpBoard[i][n];
    }
  }
}

int flipCount(int p,int y, int x) {
  int i,n;
  int okay = 0;
  int otherPlayer;
  int count = 0;
  if (p == PLAYER1) {
    otherPlayer = PLAYER2;
  } else {
    otherPlayer = PLAYER1;
  }
  
  //left
  okay = 0;
  for (i=x-1;i>=0;i--) {
    if (board[y][i] == p) {
      okay = 1;
      break;
    } else if (board[y][i] == BLANK) {
      break;
    }
  }  
  if (okay) {
    for (i=x-1;i>=0;i--) {
      if (board[y][i] == otherPlayer) {
         count++;
      } else {
      	break;
      }	
    }
  }
  //done left

  //right
  okay = 0;
  for (i=x+1;i<8;i++) {
    if (board[y][i] == p) {
      okay = 1;
      break;
    } else if (board[y][i] == BLANK) {
      break;
    }
  }
  if (okay) {
    for (i=x+1;i<8;i++) {
      if (board[y][i] == otherPlayer) {
        count++;
      } else {
        break;
      }
    }
  }

  //bottom
  okay = 0;
  for (i=y-1;i>=0;i--) {
    if (board[i][x] == p) {
      okay = 1;
      break;
    } else if (board[i][x] == BLANK) {
      break;
    }
  }
  if (okay) {
    for (i=y-1;i>=0;i--) {
      if (board[i][x] == otherPlayer) {
         count++;
      } else {
          break;
      }
    }
  }

  //top
  okay = 0;
  for (i=y+1;i<8;i++) {
    if (board[i][x] == p) {
      okay = 1;
      break;
    } else if (board[i][x] == BLANK) {
      break;
    }
  }
  if (okay) {
    for (i=y+1;i<8;i++) {
      if (board[i][x] == otherPlayer) {
         count++;
      } else {
          break;
      }
    }
  }

  //top right
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x+1+i < 8)&&(y-1-i >= 0)) {
      if (board[y-1-i][x+1+i] == p) {
        okay = 1;
        break;
      } else if (board[y-1-i][x+1+i] == BLANK) {
	break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x+1+i < 8)&&(y-1-i >= 0)) {
        if (board[y-1-i][x+1+i] == otherPlayer) {
          count++;
        } else {
          break;
        }
      } 
    }
  }

  //bottom left
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x-1-i >= 0)&&(y+1+i < 8)) {
      if (board[y+1+i][x-1-i] == p) {
        okay = 1;
        break;
      } else if (board[y+1+i][x-1-i] == BLANK) {
        break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x-1-i >= 0)&&(y+1+i < 8)) {
        if (board[y+1+i][x-1-i] == otherPlayer) {
          count++;
        } else {
          break;
        }
      }
    }
  }

  //top left
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x-1-i >= 0)&&(y-1-i >= 0)) {
      if (board[y-1-i][x-1-i] == p) {
        okay = 1;
        break;
      } else if (board[y-1-i][x-1-i] == BLANK) {
        break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x-1-i >= 0)&&(y-1-i >= 0)) {
        if (board[y-1-i][x-1-i] == otherPlayer) {
          count++;
        } else {
          break;
        }
      }
    }
  }
  
  //bottom right
  okay = 0;
  for (i=0;i<8;i++) {
    if ((x+1+i < 8)&&(y+1+i < 8)) {
      if (board[y+1+i][x+1+i] == p) {
        okay = 1;
        break;
      } else if (board[y+1+i][x+1+i] == BLANK) {
        break;
      }
    }
  }
  if (okay) {
    for (i=0;i<8;i++) {
      if ((x+1+i < 8)&&(y+1+i < 8)) {
        if (board[y+1+i][x+1+i] == otherPlayer) {
          count++;
        } else {
          break;
        }
      }
    }
  }
  return count;
}

int isValidMove(int p, int y, int x) {
  int otherPlayer;
  if (p == PLAYER1) {
    otherPlayer = PLAYER2;
  } else {
    otherPlayer = PLAYER1;
  }
  if (board[y][x] != BLANK) {
    return 0;
  } else if (countNeighbours(otherPlayer,y,x) == 0) {
    return 0;
  } 

  int c = flipCount(p,y,x);

  return c;
}

void ai(int p) {
  Serial.println("My turn ...");
  delay(3000);
  int i,n,y,x;
  int maxFlips = 0;
  for (i=0;i<8;i++) {
    for (n=0;n<8;n++) {
      int c = isValidMove(p,i,n);
      if (c > maxFlips) {
        maxFlips = c;
        y = i;
        x = n;
      }
    }
  }
  doFlip(p,y,x);
  board[y][x] = p;
}

int openBlocks() {
  int i,n;
  for (i=0;i<8;i++) {
    for (n=0;n<8;n++) {
      if (board[i][n] == BLANK) {
        return 1;
      }
    }
  }
  return 0;
}

int validMovesLeft(int p) {
  int i,n;
  for (i=0;i<8;i++) {
    for (n=0;n<8;n++) {
      if (isValidMove(p,i,n) > 0) {
	return 1;
      }
    }
  }
  return 0;
}

int winner() {
  int i,n;
  int o = 0;
  int x = 0;
  for (i=0;i<8;i++) {
    for (n=0;n<8;n++) {
      if (board[i][n] == PLAYER1) {
        o++;
      } else if (board[i][n] == PLAYER2) {
        x++;
      }
    }
  }
  if (o > x) {
    return PLAYER1;
  } else if (o < x) {
    return PLAYER2;
  }
  return -1;
}

char getChar() {
  char c = 'x';
  while (c == 'x') {
    if (Serial.available() > 0) {
      c = Serial.read();
    }
  }
  return c;
}

void doMove(int p) {
  int validMove = 0;
  while (validMove == 0) {
    Serial.print("Please enter your move: ");
    char row,col;
    row = getChar();
    Serial.write(row);
    col = getChar();
    Serial.write(col);
    Serial.println();
    int x,y;
    switch(row) {
      case '1': y = 0; break;
      case '2': y = 1; break;
      case '3': y = 2; break; 
      case '4': y = 3; break;
      case '5': y = 4; break;
      case '6': y = 5; break;
      case '7': y = 6; break;
      case '8': y = 7; break;
      default: y = -1;
    }
    switch(col) {
      case 'a': x = 0; break;
      case 'b': x = 1; break;
      case 'c': x = 2; break;
      case 'd': x = 3; break;
      case 'e': x = 4; break;
      case 'f': x = 5; break;
      case 'g': x = 6; break;
      case 'h': x = 7; break;
      default: x = -1;
    }
    if ((x == -1)||(y == -1)) {
      Serial.println("Invalid input");
    } else if (isValidMove(p,y,x) != 0) {
      validMove = 1;
      doFlip(p,y,x);
      board[y][x] = p;
    } else {
      Serial.println("That is not a valid move!");
    } 
  }
}


void setup() {
  Serial.begin(9600);
  initGame();
  do {
    cls();
    Serial.println("Press esc to continue!");
  } while (getChar() != (char) 27);
  drawBoard();
}

void loop() {
  int gameCanContinue = 1;
  while (gameCanContinue) {
    if (currentPlayer == PLAYER1) {
      if (validMovesLeft(PLAYER1)) {
        doMove(PLAYER1);
      } else if (!validMovesLeft(PLAYER2)) {
        gameCanContinue = 0;
      }
      currentPlayer = PLAYER2;
    } else {
      if (validMovesLeft(PLAYER2)) {
        ai(PLAYER2);
      } else if (!validMovesLeft(PLAYER1)) {
        gameCanContinue = 0;
      }
      currentPlayer = PLAYER1;
    }
    
    if (gameCanContinue) {
      gameCanContinue = openBlocks();
    }
    drawBoard();
  }

  if (winner() == PLAYER1) {
    Serial.println("You won! Well done! :)");
  } else if (winner() == PLAYER2) {
    Serial.println("lol, better luck next time ;)");
  } else {
    Serial.println("it's a tie!");
  }
  
  do {
    Serial.println("Press esc to start new game!");
  } while (getChar() != (char) 27);
  initGame();
  drawBoard();
}


