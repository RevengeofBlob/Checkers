#include "checkers.h"
#include "checkers.cpp"
using namespace std;

class Tester{
public:
  //Tests if a board is correctly generated using default values
  bool validateDefaultPre(Checkers & checkers){
    bool result = true;

    //Before any changes, we expect a WDISK in (1, 4)
    result = result && (checkers.m_game[1][4] == WDISK);
    //Before any changes, we expect a WCELL in (3, 2)
    result = result && (checkers.m_game[3][2] == WCELL);
    //Before any changes, we expect a BCELL in (6, 6)
    result = result && (checkers.m_game[6][6] == BCELL);
    //Before any changes, we expect a BDISK in (7, 0)
    result = result && (checkers.m_game[7][0] == BDISK);
    //Before any changes, we expect the player to be BPLAYER
    result = result && (checkers.m_currPlayer == BPLAYER);
    
    return result;
  }
  //Tests if a default board is correctly updated after setGameState()
  bool validateDefaultSetState(Checkers & checkers){
    bool result = true;

    //After set state, we expect a WKING in (0, 5)
    result = result && (checkers.m_game[0][5] == BKING);
    //After set state, we expect a BDISK in (2, 1)
    result = result && (checkers.m_game[2][1] == BDISK);
    //After set state, we expect a WDISK in (5, 2)
    result = result && (checkers.m_game[5][2] == WDISK);
    //After set state, we expect a BCELL in (7, 0)
    result = result && (checkers.m_game[7][0] == BCELL);
    //After set state, we expect a WCELL in (4, 2)
    result = result && (checkers.m_game[4][2] == WCELL);
    //After set state, we expect the player to be WPLAYER
    result = result && (checkers.m_currPlayer == WPLAYER);
    
    return result;
  }
  //Tests if a default board and member variables are correctly updated after play()
  bool validateDefaultPlay(Checkers & checkers){
    bool result = true;
    int opponentDisks = checkers.m_blackDisks;
    
    //After play, we expect a WDISK in (6, 5)
    result = result && (checkers.m_game[6][5] == WDISK);
    //After play, we expect a BCELL in (5, 4) the captured disk
    result = result && (checkers.m_game[5][4] == BCELL);
    //After play, we expect a BCELL in (4, 3)
    result = result && (checkers.m_game[4][3] == BCELL);
    //After play, we expect the player to be BPLAYER
    result = result && (checkers.m_currPlayer == BPLAYER);
    //After play, we expect the number of black disks to decrease by 1
    result = result && (checkers.m_blackDisks == (opponentDisks - 1));
    
    return result;
  }

  //Tests if a board is correctly generated using overloaded values
  bool validateOverloadedPre(Checkers & checkers){
    bool result = true;

    //Before any changes, we expect a WDISK in (0, 7)
    result = result && (checkers.m_game[0][7] == WDISK);
    //Before any changes, we expect a WCELL in (5, 5)
    result = result && (checkers.m_game[5][5] == WCELL);
    //Before any changes, we expect a BCELL in (5, 0)
    result = result && (checkers.m_game[5][0] == BCELL);
    //Before any changes, we expect a BDISK in (9, 4)
    result = result && (checkers.m_game[9][4] == BDISK);
    //Before any changes, we expect the player to be BPLAYER
    result = result && (checkers.m_currPlayer == BPLAYER);

    return result;
  }
  //Tests if overloaded board is correctly updated after setGameState()
  bool validateOverloadedSetState(Checkers & checkers){
    bool result = true;

    //After set state, we expect a WKING
    result = result && (checkers.m_game[0][5] == WKING);
    //After set state, we expect a BDISK in (2, 1)
    resul = result && (checkers.m_game[2][1] == BDISK);
    //After set state, we expect a WDISK in (5, 2)
    result = result && (checkers.m_game[5][2] == WDISK);
    //After set state, we expect a BCELL in (7, 0)
    result = result && (checkers.m_game[9][6] == BCELL);
    //After set state, we expect a WCELL in (4, 2)
    result = result && (checkers.m_game[8][4] == WCELL);
    //After set state, we expect the player to be WPLAYER
    result = result && (checkers.m_currPlayer == WPLAYER);
    

    return result;
  }

  //Tests if overloaded board and member variables are correctly updated after play()
  bool validateOverloadedPlay(Checkers & checkers){
    bool result = true;
    int opponentDisks - checkers.m_blackDisks;

    //After play, we expect a WDISK in (6, 5)
    result = result && (checkers.m_game[6][5] == WDISK);
    //After play, we expect a BCELL in (5,4) the captured disk
    result = result && (checkers.m_game[5][4] == BECELL);
    //After play, we expect a BECELL in (4, 3)
    result = result && (checkers.m_game[4][3] == BECELL);
    //After play, we expect the player to be BPLAYER
    result = result && (checkers.m_currPlayer == BPLAYER);
    //After play, we expect the umber of black disks to decrease by 1
    result = result && (checkers.m_blackDisks == (oponentDisks - 1));
    

    return true;
  }
  
  //Tests if a board with parameters smaller than 8 or non-equal parameters creates an empty object
  bool checkTooSmallOrUneven(Checkers & checkers){
    bool result = true;

    //We expect the game array to be nullptr
    result = result && (checkers.m_game == nullptr);
    //We expect the number of rows to be set to default values
    result = result && (checkers.m_numRows == DEFBOARDSIZE);
    //We expect the number of columns to be default
    result = result && (checkers.m_numColumns == DEFBOARDSIZE);
    //We expect the player to be BPLAYER
    result = result && (checkers.m_numColumns == DEFBOARDSIZE);
    
    return result;
  }
};

int main(){
  Tester tester;
  Checkers defaultBoard(DEFBOARDSIZE, DEFBOARDSIZE); //Test board for default values

  //Sets the squares and pieces. Displays each step
  defaultBoard.initBoard();
  cout << "Board showing the default starting squares without pieces:\n\n";
  defaultBoard.dumpGame();
  defaultBoard.initGame();
  cout << "Board showing the default starting piece positions:\n\n";
  defaultBoard.dumpGame();

  //Checks if the default board is set up correctly
  if (tester.validateDefaultPre(defaultBoard)){
    cout << "\tvalidateDefaultPre() returned true\n";
  }
  else {
    cout << "\tvalidateDefaultPre() returned false\n";
  }

  int size = DEFBOARDSIZE * DEFBOARDSIZE;
  //New game state
  CELL game[size] = {"", "", "", "", "", BKING, "", ""
		     "", "", "", "", "", "", "", ""
		     "", BDISK, "", "", BDISK, "", "", ""
		     "", "", "", "", "", "", "", ""
		     "", "", "", WDISK, "", "", "", ""
		     "", "", WDISK, "", BDISK, "", "", ""
		     "", "", "", "", "", "", "", ""
		     "", "", "", "", "", "", "", ""};
  
  defaultBoard.setGameState(game, size, WPLAYER);
  cout << "Shows the board after the pieces have been removed/replaced\n\n";
  defaultBoard.dumpGame();

  //Checks if the default board updates according to the new game state
  if (tester.validateDefaultSetState(defaultBoard)){
    cout << "\tvalidateDefaultSetState() returned true\n";
  }
  else {
    cout << "\tvalidateDefaultSetState() returned false\n";
  }

  //Calls play to jump a BDISK with a WDISK and displays the new board
  defaultBoard.play(pair<int, int>(4, 3), pair<int, int>(6, 5));
  cout << "Shows the board after a jump move has been made\n\n";
  defaultBoard.dumpGame();

  //Checks if the board updates after the play and the member variables reflect it
  if (tester.validateDefaultPlay(defaultBoard)){
    cout << "\tvalidteDefaultPlay() returned true\n";
  }
  else {
    cout << "\tvalidateDefaultPlay() returned false\n";
  }

  Checkers squareBoard(11, 11); //Checker board with valid values over 8
  squareBoard.initBoard();
  cout << "Shows the board of size 11x11 without pieces on\n\n";
  squareBoard.dumpGame();
  squareBoard.initGame();
  cout << "Shows the board of size 11x11 wit pieces in starting positions\n\n";
  squareBoard.dumpGame();

  if (tester.validateOverloadedPre(squareBoard)){
    cout << "\tvalidateOverloadedPre() returned true\n";
  }
  else {
    cout << "\tvalidateOverloadedPre() returned false\n";
  }

  size = 11 * 11;
  //New game state for overloaded board
  CELL game[size] = {"", "", "", "", "", BKING, "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""
		     "", BDISK, "", "", BDISK, "", "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""
		     "", "", "", WDISK, "", "", "", "", "", "" , ""
		     "", "", WDISK, "", BDISK, "", "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""
		     "", "", "", "", "", "", "", "", "", "" , ""};

  squareBoard.setGameState(game, size, WPLAYER);
  cout << "Shows the board after the pieces have been removed/replaced\n\n";
  squareBoard.dumpGame();
  
  //Checks if the default board updates according to the new game state
  if (tester.validateOverloadedSetState(squareBoard)){
    cout << "\tvalidateOverloadedSetState() returned true\n";
  }
  else {
    cout << "\tvalidateOverloadedSetState() returned false\n";
  }

  //Calls play to jump a BDISK with a WDISK and displays the new board
  squareBoard.play(pair<int, int>(4, 3), pair<int, int>(6, 5));
  cout << "Shows the board after a jump move has been made\n\n";
  squareBoard.dumpGame();

  //Checks if the board updates after the play and the member variables reflect it
  if (tester.validateOverloadedPlay(squareBoard)){
    cout << "\tvalidateOverloadedPlay() returned true\n";
  }
  else {
    cout << "\tvalidateOverloadedPlay() returned false\n";
  }
  
  Checkers smallBoard(5, 5); //Test board for size less than minimum size

  if (tester.checkTooSmallOrUneven(smallBoard)){
    cout << "\tcheckTooSmallOrUneven() returned true\n";
  }
  else {
    cout << "\tcheckTooSmallOrUneven() returned false\n";
  }
  
  Checkers unequalBoard(9, 12); //Test board for two different sizes

  if (tester.checkTooSmallOrUneven(unequalBoard)){
    cout << "\tcheckTooSmallOrUneven() returned true\n";
  }
  else {
    cout << "\tcheckTooSmallOrUneven() returned false\n";
  }
  
  return 0;
}
