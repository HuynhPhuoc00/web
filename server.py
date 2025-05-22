from flask import Flask, request, jsonify
import control 

app = Flask(__name__, static_url_path='', static_folder='static')

led_state = {"BULB_01": "OFF"}

@app.route("/")
def root():
    return app.send_static_file("index.html")

@app.route("/bulb", methods=["GET", "POST"])
def bulb():
    global led_state

    if request.method == "POST":
        data = request.get_json()
        if data and "BULB_01" in data:
            led_state["BULB_01"] = data["BULB_01"]
            
            control.update_led_state(led_state["BULB_01"])

            return jsonify({"status": "ok", "LED": led_state["BULB_01"]})
        else:
            return jsonify({"error": "Missing BULB_01 key"}), 400

    elif request.method == "GET":
        return jsonify(led_state)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
