from flask import Flask, request, jsonify
import control

app = Flask(__name__, static_url_path='', static_folder='static')

# Trạng thái tất cả thiết bị
device_states = {
    "BULB_01"   : "OFF",
    "FAN_01"    : "OFF",
    "TV_01"     : "OFF",
    "LOCK_01"   : "OFF",
    "AIR_01"    : "OFF",
    "SPEAKER_01": "OFF"
}

@app.route("/")
def root():
    return app.send_static_file("index.html")

@app.route("/device/<device_id>", methods=["GET", "POST"])
def control_device(device_id):
    device_id = device_id.upper()

    if device_id not in device_states:
        return jsonify({"error": f"Unknown device: {device_id}"}), 404

    if request.method == "POST":
        data = request.get_json()
        if device_id in data:
            device_states[device_id] = data[device_id]
            control.update_device_state(device_id, data[device_id])
            return jsonify({"status": "ok", device_id: device_states[device_id]})
        else:
            return jsonify({"error": f"Missing {device_id} key"}), 400
    else:
        return jsonify({device_id: device_states[device_id]})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
