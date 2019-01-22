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
    stdout = stdout.strip('\n')
    from_sq = stdout[0:2]
    to_sq = stdout[2:4]
    # print "END MOVE"
    return jsonify({'move': stdout, 'from': from_sq, 'to': to_sq})


if __name__ == '__main__':
    app.run()
