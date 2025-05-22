from flask import Flask, request, jsonify, send_from_directory

app = Flask(__name__, static_url_path='', static_folder='static')

bulb_status = {"BULB_01": "OFF"}

@app.route("/bulb", methods=["GET", "POST"])
def bulb_control():
    global bulb_status
    if request.method == "POST":
        data = request.get_json()
        bulb_status["BULB_01"] = data.get("BULB_01", "OFF")
        print("Đèn:", bulb_status["BULB_01"])
        return jsonify({"status": "ok"})
    return jsonify(bulb_status)

@app.route("/")
def root():
    return app.send_static_file("index.html")

if __name__ == "__main__":
    app.run(port=8080)