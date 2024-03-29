# **BRITON**

A small chess engine I wrote in C++ and a (very) basic frontend.

### **How The Frontend Interfaces With the Backend (Simply)**

First, the user interacts with the [chessboard.js](https://chessboardjs.com) board, which updates the chess.js game representation.

#### **_TODO: Migrate to Ornicar's [Chessground UI (Which Allows for Mobile)](https://github.com/ornicar/chessground) or add support for Caustique's [Chessboard-JS (Which Allows for Mobile but does not allow for Drag-Drop)](https://github.com/caustique/chessboard-js)_**

Then, after the user makes the initial move, the chessboard gets locked, so that the user cannot make moves on the board, and a POST request is sent to the _/move_ path with the [PGN](https://en.wikipedia.org/wiki/Portable_Game_Notation) of the current game and the time the user requested, which waits until the server returns the best move with the format:

```
{'move': <...>, 'from': <...>, 'to': <...>, 'eval': <...>}
```

Note: _move_ is in the long algebraic notation, _from_ and _to_ are the move to and move from squares, and _eval_ is the score that the chess engine scored the position as.

#### **_TODO: Add ability to select depth, rather than time_**

Finally, the game.js game representation and the _chessboard.js_ board are updated, and the square highlights are made using the code:

```js
game.move(data["move"], {
  sloppy: true
});
removeHighlights("white");
removeHighlights("black");
boardEl.find(".square-" + data["from"]).addClass("highlight-black");
boardEl.find(".square-" + data["to"]).addClass("highlight-black");
board.position(game.fen()); // update the board to the new position
```

### **How the engine works**

The engine is a UCI engine that communicates with the Flask webapp engine package from python-chess.

Essentially, the engine uses an Alpha-Beta search with move ordering and quiescent search, a Principal Variation table, a combined 120 square array and bitboard data structure, and a material and Piece-Square table evaluation.
