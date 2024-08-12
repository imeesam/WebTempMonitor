from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

data_history = {'labels': [], 'temperatures': []}

# API endpoint to receive DHT11 data and update data_history
@app.route('/api/update-dht-data', methods=['POST'])
def update_dht_data():
    dht_data = request.json
    temperature = dht_data.get('temperature')

    if temperature is not None:
        data_history['labels'].append(len(data_history['temperatures']))
        data_history['temperatures'].append(temperature)
        
    return "Data received successfully!", 200

@app.route('/')
def index():
    return render_template('graph2.html')

@app.route('/api/get-graph-data', methods=['GET'])
def get_graph_data():
    dht_data = {"labels": data_history['labels'], "temperatures": data_history['temperatures']}
    return jsonify(dht_data)

if __name__ == "__main__":
    app.run(port=3000)
