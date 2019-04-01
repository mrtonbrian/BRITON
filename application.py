import subprocess
import sys
import os
import os.path

from flask import Flask, render_template, request, jsonify

application = Flask(__name__)

files = [f for f in os.listdir('.') if os.path.isfile(f)]
print files
print os.path.isfile(os.path.dirname(os.path.abspath(__file__))+'/chess') 



@application.route('/')
def main_page():
    return render_template("Chess.html")


@application.route('/move', methods=["POST"])
def move():
    print("START MOVE")
    sys.stdout.flush()
    r = request.get_json(force=True)
    time = r['time']
    fen = r['fen']
    process = subprocess.Popen([os.path.dirname(os.path.abspath(__file__))+'/chess \"' + fen + '\" ' + str(time)], stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                               shell=True)
    stdout, stderr = process.communicate()
    print(os.path.dirname(os.path.abspath(__file__))+'/chess \"' + fen + '\" ' + str(time))
    sys.stdout.flush()
    stdout = stdout.split('\n')
    print(stdout)
    sys.stdout.flush()
    from_sq = stdout[1][0:2]
    to_sq = stdout[1][2:4]
    eval = int(stdout[2])
    print(stdout)
    print("END MOVE")

    return jsonify({'move': stdout[1], 'from': from_sq, 'to': to_sq, 'eval': eval})

if __name__ == '__main__':
    application.run(host="0.0.0.0", port=int("5000"))
