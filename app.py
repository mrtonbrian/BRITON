import subprocess

from flask import Flask, render_template, request, jsonify

app = Flask(__name__)


@app.route('/')
def main_page():
    return render_template("Chess.html")


@app.route('/move', methods=["POST"])
def move():
    # print "START MOVE"
    r = request.get_json(force=True)
    time = r['time']
    fen = r['fen']
    process = subprocess.Popen(['./chess \"' + fen + '\" ' + str(time)], stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                               shell=True)
    stdout, stderr = process.communicate()
    #print stdout
    stdout = stdout.split('\n')
    from_sq = stdout[0][0:2]
    to_sq = stdout[0][2:4]
    eval = int(stdout[1])
    # print "END MOVE"
    return jsonify({'move': stdout[0], 'from': from_sq, 'to': to_sq, 'eval': eval})


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=int("5000"))

