import subprocess
import sys
import os
import os.path
import io
import chess.pgn
import chess.engine as e
import chess

from flask import Flask, render_template, request, jsonify

application = Flask(__name__)

files = [f for f in os.listdir('.') if os.path.isfile(f)]

ENGINE_FILE = '/chess.exe'

@application.route('/')
def main_page():
    return render_template("Chess.html")


@application.route('/move', methods=["POST"])
def move():
    sys.stdout.flush()
    r = request.get_json(force=True)
    time = r['time']
    pgn = r['pgn']
    c = chess.pgn.read_game(io.StringIO(pgn))
    
    engine = e.SimpleEngine.popen_uci(os.path.dirname(os.path.abspath(__file__))+ENGINE_FILE)
    board = chess.Board()
    if c:
        for i in c.mainline_moves():
            board.push(i)
    res = engine.play(board, e.Limit(time=time), info=chess.engine.INFO_ALL)
    engine.quit()
    return jsonify({'move': str(res.move), 'from': str(res.move)[0:2], 'to': str(res.move)[2:], 'eval': str(res.info['score'])})

if __name__ == '__main__':
    application.run(host="0.0.0.0", port=int("5000"))
