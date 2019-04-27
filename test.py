import chess
import chess.pgn

game = chess.pgn.read_game(open("NERO-Chess.pgn"))
for i in game.mainline_moves():
    print(i)
