from flask import Flask, request, jsonify, send_from_directory

app = Flask(__name__, static_url_path='', static_folder='static')

bulb_status = {"BULB_01": "OFF"}

@app.route("/bulb", methods=["GET", "POST"])

@app.route("/")
def root():
    return app.send_static_file("index.html")

if __name__ == "__main__":
    app.run(port=5000)