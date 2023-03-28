// UMBC - CMSC 341 - Spring 2023 - Proj0
#include "checkers.h"

const double DISK_MULTIPLIER = 3 / 2; //Multiplied by the rows to get the # of disks
const int MIN_SIZE = 8; //Minimum size a length can be
const int WHITE_STARTING_ROWS = 3; //Rows 0-2 start off containing white disks
const int REGULAR_MOVE = 1; //1 diagonal space on a regular move
const int JUMP_MOVE = 2; //2 diagonal spaces when the player jumps a piece

//Checkers
//Constructor (Default). Sets the # of rows and columns to the default size, sets current player to no player
//Sets the number of disks for each player and generates a new board using the # of rows
Checkers::Checkers(){
  m_numRows = DEFBOARDSIZE;
  m_numColumns = DEFBOARDSIZE;
  m_currPlayer = BPLAYER;
  m_whiteDisks = m_numRows * DISK_MULTIPLIER;
  m_blackDisks = m_numRows * DISK_MULTIPLIER;
  m_game = nullptr;
}

//Checkers
//Constructor (overloaded). Sets # of rows and columns to passed values, sets current player to no player
//Sets the number of disks for each player and generates a new game board using the # of rows.
Checkers::Checkers(int rows, int columns){
  //If the rows or columns are less than the minimum size or if the # of rows don't equal the # of columns, creates an empty object
  if (rows < MIN_SIZE || columns < MIN_SIZE || rows != columns){
    m_numRows = DEFBOARDSIZE;
    m_numColumns = DEFBOARDSIZE;
    m_currPlayer = BPLAYER;
    m_whiteDisks = m_numRows * DISK_MULTIPLIER;
    m_blackDisks = m_numRows * DISK_MULTIPLIER;
    m_game = nullptr;
  }

  //Else uses passed values to initialize member variables
  else{
    m_numRows = rows;
    m_numColumns = columns;
    m_currPlayer = BPLAYER;
    m_whiteDisks = m_numRows * DISK_MULTIPLIER;
    m_blackDisks = m_numRows * DISK_MULTIPLIER;
    m_game = new CELL* [m_numRows];
  }
}

//~Checkers
//Destructor. Loops through the game array and deletes each index, then deletes the entire array.
Checkers::~Checkers(){
  for (int i = 0; i < m_numRows; i++){
    delete m_game[i];
    m_game[i] = nullptr;
  }
  delete[] m_game;
  m_game = nullptr;
}

//clear
//Deletes each index in game array and then deletes the array. Reinitializes each member variable to default. m_game becomes an empty object
void Checkers::clear(){
  for (int i = 0; i < m_numRows; i++){
    delete m_game[i];
    m_game[i] = nullptr;
  }

  delete[] m_game;
  m_game = nullptr;

  m_numRows = DEFBOARDSIZE;
  m_numColumns = DEFBOARDSIZE;
  m_currPlayer = NONE;
  m_whiteDisks = m_numRows * DISK_MULTIPLIER;
  m_blackDisks = m_numRows * DISK_MULTIPLIER;
  m_game = nullptr;
}

//initBoard
//Creates a blank game board of white and black squares. Alternates each index in the game array from a white cell to a black cell
void Checkers::initBoard(){
  bool whiteCell = true;

  for (int i = 0; i < m_numRows; i++){
    for (int j = 0; j < m_numColumns; j++){
      if (whiteCell){
	m_game[i][j] = WCELL;
      }
      else{
	m_game[i][j] = BCELL;
      }

      whiteCell = !whiteCell;
    }
  }
}

//reportLostDisks
//Outputs to console if there are any tokens removed by either color
void Checkers::reportLostDisks(){
  int whiteLost = -(m_whiteDisks - (m_numRows * DISK_MULTIPLIER));
  int blackLost = -(m_blackDisks - (m_numRows * DISK_MULTIPLIER));

  cout << "White player lost disks : " << whiteLost << "\n" << "Black player lost disks: " << blackLost << "\n";
}

//initGame
//Sets the first three rows of the board to have white disks and the last 3 rows to have black disks
void Checkers::initGame(){
  for (int i = 0; i < m_numRows; i++){
    //If the row index is 0-2 and the value is a black cell, set it to a white disk
    if (i < WHITE_STARTING_ROWS){
      for (int j = 0; j < m_numColumns; j++){
	if (m_game[i][j] == BCELL){
	  m_game[i][j] = WDISK;
	}
      }
    }
    //If the row index is (last row - 3) - last row and the value is a black cell, set it to a black disk
    if (i >= m_numRows - 3){
      for (int k = 0; k < m_numColumns; k++){
	if (m_game[i][k] == BCELL){
	  m_game[i][k] = BDISK;
	}
      }
    }
  }
}

//play
//takes in an x,y pair for the piece you want to move and an x,y pair for where you want it to go
//If the move is valid, completes the move and returns true. Else nothing changes on the board and returns false
bool Checkers::play(pair<int, int> origin, pair<int, int> destination){
  bool originInBounds = origin.first >= 0 && origin.first < m_numRows && origin.second >= 0 && origin.second < m_numColumns;
  bool destinationInBounds = destination.first >= 0 && destination.first < m_numRows && destination.second >= 0 && destination.second < m_numColumns;
  if (originInBounds && destinationInBounds){
    string piece = m_game[origin.first][origin.second];
    if (piece != WCELL || piece != BCELL){
      if (isValidMove(m_currPlayer, origin, destination, piece)){
	movePiece(origin, destination, piece);
	if (m_currPlayer == BPLAYER){
	  m_currPlayer = WPLAYER;
	}
	else if (m_currPlayer == WPLAYER){
	  m_currPlayer = BPLAYER;
	}
      }
    }
  }

  return false;
}

bool Checkers::isValidMove(PLAYER currPlayer, pair<int, int> start, pair<int, int> end, string token){
  int xChange = start.first - end.first;
  int yChange = start.second - end.second;

  if (currPlayer == BPLAYER){
    if (token == BDISK){
      if (abs(xChange) == REGULAR_MOVE && yChange == -REGULAR_MOVE){
	return true;
      }
      else if (abs(xChange) == JUMP_MOVE && yChange == -JUMP_MOVE){
	return validateJump(start, end, token);
      }
    }
    if (token == BKING){
      if (abs(xChange) == REGULAR_MOVE && abs(yChange) == REGULAR_MOVE){
	return true;
      }
    }
    else if (abs(xChange) == JUMP_MOVE && abs(yChange) == JUMP_MOVE){
      return validateJump(start, end, token);
    }
  }
  else if (currPlayer == WPLAYER){
    if (token == WDISK){
      if (abs(xChange) == REGULAR_MOVE && yChange == REGULAR_MOVE){
	return true;
      }
      else if (abs(xChange) == JUMP_MOVE && yChange == JUMP_MOVE){
	return validateJump(start, end, token);
      }
    }
    else if (token == WKING){
      if (abs(xChange) == REGULAR_MOVE && abs(yChange) == REGULAR_MOVE){
	return true;
      }
      else if (abs(xChange) == JUMP_MOVE && abs(yChange) == JUMP_MOVE){
	return validateJump(start, end, token);
      }
    }
  }
  return false;
}

void Checkers::movePiece(pair<int, int> start, pair<int, int> end, string cell){
  m_game[start.first][start.second] = BCELL;
  m_game[end.first][end.second] = cell;
}

bool Checkers::validateJump(pair<int, int> begin, pair<int, int> finish, string piece){
  string jumpCell; //Value of the cell between begin and finish
  int vertical = 1; //Positive for down, negative for up
  int horizontal = 1; //Positive for right, negative for left

  //If finish is above beginning
  if (finish.second < begin.second){
    vertical = -1;
  }
  //If the finish is to the left of beginning
  if (finish.first < begin.first){
    horizontal = -1;
  }

  if (piece == BDISK && vertical == -1){
    jumpCell = m_game[begin.first + horizontal][begin.second + vertical];
    
    if (jumpCell == WDISK || jumpCell == WKING){
      m_game[begin.first + horizontal][begin.second + vertical] = BCELL;
      return true;
    }
  }
  else if (piece == WDISK && vertical == 1){
    jumpCell = m_game[begin.first + horizontal][begin.second + vertical];

    if (jumpCell == BDISK || jumpCell == BKING){
      m_game[begin.first + horizontal][begin.second + vertical] = BCELL;
      return true;
    }
  }
  else if (piece == BKING){
    jumpCell = m_game[begin.first + horizontal][begin.second + vertical];

    if (jumpCell == WDISK || jumpCell == WKING){
      m_game[begin.first + horizontal][begin.second + vertical] = BCELL;
      return true;
    }
  }
  else if (piece == WKING){
    jumpCell = m_game[begin.first + horizontal][begin.second + vertical];

    if (jumpCell == BDISK || jumpCell == BKING){
      m_game[begin.first + horizontal][begin.second + vertical] = BCELL;
      return true;
    }
  }
  
  return false;
}
  
//setGameState
//
void Checkers::setGameState(CELL game[], int n, PLAYER player){
  if(n == (m_numRows * m_numColumns)){
    int row = 0;
    m_currPlayer = player;

    for (int i = 0; i < n; i++){
      if (game[i] != ""){
	if ((m_game[row][i % m_numColumns] == BDISK || m_game[row][i % m_numColumns] == BKING) && game[i] == BCELL){
	  m_blackDisks--;
	}
	else if ((m_game[row][i % m_numColumns] == WDISK || m_game[row][i % m_numColumns] == WKING) && game[i] == BCELL){
	  m_whiteDisks--;
	}
	if (game[i] == BDISK || game[i] == BKING){
	  m_blackDisks++;
	}
	else if (game[i] == WDISK || game[i] == WKING){
	  m_whiteDisks++;
	}
	m_game[row][i % m_numColumns] = game[i];
	row++;
      }
    }
  }
}

//dumpGame
//outputs a visual representation of the game board
void Checkers::dumpGame(){
  if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr){
    cout << "  ";
    for (int k=0;k<m_numColumns;k++){
      cout << k << " ";
    }
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
      cout << i-1 << " ";
      for (int j=1;j<=m_numColumns;j++){
	cout << m_game[i-1][j-1];
      }
      cout << endl;
    }
    cout << endl;
  }
}
