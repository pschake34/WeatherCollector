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
        if request.method == 'POST':
            request_json = request.json
            json_object = json.loads(json.dumps(request_json))
            valid_types = ["temperature", "humidity", "pressure", "windSpeed"]
            database = db.get_db()

            print("Payload: ")
            print(json.dumps(request_json, indent=4))
            print(json_object["value"])

            if valid_types.index(json_object["name"]) != -1:
                try:
                    database.execute(
                        "INSERT INTO {} (value) VALUES (?)".format(json_object["name"]),
                        (json_object["value"],)
                    )
                    database.commit()
                except database.IntegrityError:
                    print("Database Integrity Error")
                else:
                    return 'Webhook notification received', 202
        else:
            return 'POST Method not supported', 405

    @app.route('/get_sensor_data/<type>', methods=['GET'])
    def get_sensor_data(type):
        data = {"value": 0}
        database = db.get_db()
        valid_types = ["temperature", "humidity", "pressure", "windSpeed"]

        if valid_types.index(type) != -1:
            database_table = type
            database_values = database.execute(
                "SELECT * FROM {} ORDER BY time DESC LIMIT 0, 1".format(database_table)
            ).fetchone()
            print("Database values")
            print(database_values["value"])
            data["value"] = database_values["value"]
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