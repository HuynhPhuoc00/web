from flask import Flask, request, jsonify, send_from_directory

app = Flask(__name__, static_folder="static")

@app.route("/")
def index():
    return app.send_static_file("index.html")

@app.route("/bulb", methods=["POST"])
def bulb():
    data = request.get_json()
    print("Lệnh điều khiển nhận được:", data)
    return jsonify({"status": data.get("BULB_01", "UNKNOWN")})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
