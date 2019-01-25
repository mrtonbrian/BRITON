var board,
    boardEl = $('#board'),
    game = new Chess(),
    squareToHighlight;

var count = 1;

var removeGreySquares = function () {
    $('#board .square-55d63').css('background', '');
};

var greySquare = function (square) {
    var squareEl = $('#board .square-' + square);

    var background = '#a9a9a9';
    if (squareEl.hasClass('black-3c85d') === true) {
        background = '#696969';
    }

    squareEl.css('background', background);
};

var removeHighlights = function (color) {
    boardEl.find('.square-55d63')
        .removeClass('highlight-' + color);
};

// do not pick up pieces if the game is over
// only pick up pieces for White
var onDragStart = function (source, piece, position, orientation) {
    if (game.in_checkmate() === true || game.in_draw() === true) {
        return false;
    }
};

var onMouseoverSquare = function (square, piece) {
    // get list of possible moves for this square
    var moves = game.moves({
        square: square,
        verbose: true
    });

    // exit if there are no moves available for this square
    if (moves.length === 0) return;

    // highlight the square they moused over
    greySquare(square);

    // highlight the possible squares for this piece
    for (var i = 0; i < moves.length; i++) {
        greySquare(moves[i].to);
    }
};

var onMouseoutSquare = function (square, piece) {
    removeGreySquares();
};

var onDrop = function (source, target) {
    // see if the move is legal
    var move = game.move({
        from: source,
        to: target,
        promotion: 'q' // NOTE: always promote to a queen for example simplicity
    });

    // illegal move
    if (move === null) return 'snapback';

    // highlight white's move
    boardEl.find('.square-' + source).addClass('highlight-white');
    boardEl.find('.square-' + target).addClass('highlight-white');
    // Call To POST Request
    var t = JSON.stringify({
        'time': parseFloat(document.getElementById('seconds').value) * 1000,
        'fen': game.fen()
    });
    $.post("/move", t, function (data, status) {
        game.move(data['move'], {
            sloppy: true
        });
	console.log('EVAL: ' + data['eval']);
        // highlight comp's move
        removeHighlights('white');
        removeHighlights('black');
        boardEl.find('.square-' + data['from']).addClass('highlight-black');
        boardEl.find('.square-' + data['to']).addClass('highlight-black'); // update the board to the new position
        board.position(game.fen());
    });
};

var resetBoard = function () {
    document.getElementById("reset").innerHTML = '';
    game.reset();
    board.position(game.fen());
    var stuff = chooseSide();
}

var onMoveEnd = function () {
    boardEl.find('.square-' + squareToHighlight).addClass('highlight-black');
    removeGreySquares();
    if (game.in_checkmate()) {
        alert("YOU HATH BEEN MATED");

    } else if (game.in_draw()) {
        alert("There is a draw :|");
    }

    if (game.game_over()) {
        var resetButt = document.createElement("input");
        resetButt.type = "button";
        resetButt.value = "Reset!"
        resetButt.onclick = resetBoard;

        document.getElementById("reset").appendChild(resetButt);
    }
};

// update the board position after the piece snap
// for castling, en passant, pawn promotion
var onSnapEnd = function () {
    board.position(game.fen());
};

var cfg = {
    draggable: true,
    position: 'start',
    onDragStart: onDragStart,
    onDrop: onDrop,
    onMoveEnd: onMoveEnd,
    onSnapEnd: onSnapEnd,
    onMouseoutSquare: onMouseoutSquare,
    onMouseoverSquare: onMouseoverSquare
};

var getPlayerTurn = function () {
    if (count - 1 % 2 === 1) {
        return 'w';
    } else {
        return 'b';
    }
}

var undo = function () {
    removeHighlights();
    if (game.turn() === getPlayerTurn()) {
        game.undo();
        game.undo();
    } else {
        game.undo();
    }
    board.position(game.fen());
}


function setVal() {
    document.getElementById('seconds').value = "0.5";
    document.getElementById('tb').onclick = undo;
}

window.onload = setVal();

board = ChessBoard('board', cfg);

var chooseSide = function () {
    if (count % 2 === 1) {
        board.orientation('white');
    } else {
        board.orientation('black');
        var t = JSON.stringify({
            'time': parseFloat(document.getElementById('seconds').value) * 1000,
            'fen': game.fen()
        });
        $.post("/move", t, function (data, status) {
            game.move(data['move'], {
                sloppy: true
            });
	    console.log('EVAL: ' + data['eval']);
            // highlight comp's move
            removeHighlights('white');
            removeHighlights('black');
            boardEl.find('.square-' + data['from']).addClass('highlight-black');
            boardEl.find('.square-' + data['to']).addClass('highlight-black'); // update the board to the new position
            board.position(game.fen());
        });
    }
    count++;
}


var stuff = chooseSide();
