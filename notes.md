# chess
- [chess](#chess)
  - [TODO](#todo)
  - [In Progress](#in-progress)
    - [Move validation](#move-validation)

## TODO
- Get the AWS side + DB side set-up
  - Client/server?
  - For DB, we want to fetch games by ID; can we hash the entire game, and then if same game, just store to same ID?
- Figure out how to parse JSON/write JSON in C++; are there libraries?
  - Figure out how Lichess/Chess.com store games - want to be able to import into lichess/chess.com
- Algebraic notation
- Manipulate console/shell
- Hash function for sending game state
- Preview moves

## In Progress

### Move validation

Brainstorming:

1. Illegal moves that would put king in check (and thus opponent can "take" king);
To check for "move-piece-then-king-is-in-check" kind of illegal moves, the plan is to check the diagonals/ranks/files for pieces that can check the king. **For player A's king, we check these moves _not_ when it's player A's turn, but when player B finishes their turn.** For example, player B plays rook to file _i_, rank _j_; we check if player A is in check, and what pieces _cannot_ move.

    Firstly, we examine cases where a piece is pinned;

   If a move _does_ put the king in check, we access that piece, and modify its moves (i.e. we _inhibit_ its movement). Note that if a piece is being pinned, it can only pinned in one direction; i.e. if a rook is pinning a bishop, the bishop cannot also be pinned by another bishop, since there is no such situations. When we inhibit moves, we exclusively take _away_ moves, not add.

    - If the player B piece that is delivering the pin is a rook, then the piece that is being inhibited is checked for if it is a rook; if the inhibited piece is a rook, we only allow the same rank/file. Same thing for queen. If the inhibited piece is a bishop, we just make its possible moves nothing.
     - So, if queen or rook is delivering pin through **rank**, we limit **rooks** and **queens** to only be able to move along that rank. Bishops and knights have all moves taken away.
     - If queen or rook is delivering pin through **file**, we limit **rooks**, **queens**, and **pawns** to only be able to move along that file. Bishops and knights have all moves taken away.
     - If queen or bishop is delivering pin, rooks and knights have all moves taken away. **Pawn** can only take, and **queen** or **bishop** can only move in that diagonal.

    Secondly, we examine cases where the king stumbles into a bad spot;

2. Deciding available moves in general; once a player makes a move, the full list of moves for all the other pieces that belong to that player is calculated. Maybe we evaluate the possible moves a piece can make; we check its rank, and if we encounter a rook, we change the rook, and then we check that rook, recursively. Once a piece is done, we set it to a pointer that is marked "done"; if it's in progress, we mark it in progress, and once it's finished evaluating, we change to done. Once the all pieces evaluation status point to done, we change that pointer to "undone", we change the undone pointer to done, and repeat.