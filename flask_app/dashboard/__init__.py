import os
import json

from flask import (
    Flask, Blueprint, flash, g, jsonify, redirect, render_template, request, session, url_for
)

def create_app(test_config=None):
    # create and configure the app
    app = Flask(__name__)
    app.config.from_mapping(
        SECRET_KEY='dev',
        DATABASE=os.path.join(app.instance_path, 'dashboard.sqlite'),
    )

    # ensure the instance folder exists
    try:
        os.makedirs(app.instance_path)
    except OSError:
        pass

    # a simple page that says hello
    @app.route('/hello')
    def hello():
        return 'Hello, World!'

    from . import db
    db.init_app(app)

    # Webhooks
    @app.route('/send_sensor_data', methods=['POST'])
    def send_sensor_data():
        data = request.get_json(silent=True)
        if request.method == 'POST':
            print("Webhook recieved")
            request_json = request.json
        
            print("Payload: ")
            print(json.dumps(request_json, indent=4))

            return 'Webhook notification received', 202
        else:
            return 'POST Method not supported', 405

    @app.route('/get_sensor_data/<type>', methods=['GET'])
    def get_sensor_data(type):
        data = {"value": 0}
        if type == "temperature":
            data["value"] = 75
        elif type == "humidity":
            data["value"] = 35
        elif type == "pressure":
            data["value"] = 29.99
        elif type == "wind_speed":
            data["value"] = 5
        else:
            return 'Not a valid type', 400

        return data, 200

    # Visible web pages
    @app.route('/')
    def home():
        temperature = 32
        return render_template('home.html', temperature=temperature)

    @app.route('/graphs')
    def graphs():
        return render_template('graphs.html')

    @app.route('/about')
    def about():
        return render_template('about.html')

    return app