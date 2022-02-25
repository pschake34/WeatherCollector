import datetime
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

    # Shared array for webhooks
    valid_types = ["temperature", "humidity", "pressure", "windSpeed"]
    valid_timespans = ["year", "half_year", "month", "week", "day", "hour"]

    # Webhooks
    @app.route('/send_sensor_data', methods=['POST'])
    def send_sensor_data(): # recieves json string and saves value in database if the type is correct
        if request.method == 'POST':
            request_json = request.json
            json_object = json.loads(json.dumps(request_json))
            database = db.get_db()

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
    def get_sensor_data(type): # sends the most recent value of the type if the type is valid
        data = {"value": 0}
        database = db.get_db()

        if valid_types.index(type) != -1:
            database_table = type
            database_values = database.execute(
                "SELECT * FROM {} ORDER BY time DESC LIMIT 0, 1".format(database_table)
            ).fetchone()
            data["value"] = database_values["value"]
        else:
            return 'Not a valid type', 400
        return data, 200

    @app.route('/get_graph_data/<timespan>/<datatype>', methods=['GET'])
    def get_graph_data(timespan, datatype):
        data = {"values": [], "times": []}
        database = db.get_db()

        if valid_timespans.index(timespan) > -1:
            if valid_types.index(datatype) > -1:
                database_table = datatype
                tz = pytz.timezone("US/Eastern")

                if timespan == "half_year":
                    timespan = "6 months"
                elif timespan == "week":
                    timespan = "7 days"
                else:
                    timespan = "1 " + timespan

                database_values = database.execute(
                    "SELECT * FROM {} WHERE time > datetime('now', '-{}') ORDER BY time DESC".format(database_table, timespan)
                ).fetchall()
                if timespan == "1 year" or timespan == "6 months" or timespan == "1 month":
                    day_cnt = 0
                    day_total = 0
                    current_day = datetime.datetime.now().date()
                    i = 0
                    while i < len(database_values):
                        current_time = database_values[i]["time"].date()
                        if current_time < current_day:
                            data["times"].append(current_day)
                            data["values"].append(day_total/day_cnt)
                            current_day = current_time
                            day_cnt = 0
                            day_total = 0
                        
                        day_total += database_values[i]["value"]
                        day_cnt += 1
                        i += 1
                    data["times"].append(current_day)
                    data["values"].append(day_total/day_cnt)
                else:
                    data["values"] = [value["value"] for value in database_values]
                    data["times"] = [value["time"].astimezone() for value in database_values]
            else:
                return 'Not a valid type', 400
        else:
            return 'Not a valid timespan', 400
        return data, 200

    # Visible web pages
    @app.route('/')
    def home():
        return render_template('home.html')

    @app.route('/graphs')
    def graph_redirect():
        return redirect('/graphs/hour/temperature')

    @app.route('/graphs/<timespan>/<datatype>')
    def graphs(timespan, datatype):
        timespan_active = ["", "", "", "", "", ""]
        datatype_active = ["", "", "", ""]
        timespan_index = valid_timespans.index(timespan)
        datatype_index = valid_types.index(datatype)

        if timespan_index > -1:
            if datatype_index > -1:
                timespan_active[timespan_index] = "active"
                datatype_active[datatype_index] = "active"
            else:
                return 'Not a valid type', 400
        else:
            return 'Not a valid timespan', 400
        return render_template('graphs.html', timespan_active=timespan_active, datatype_active=datatype_active, timespan=timespan, datatype=datatype)

    @app.route('/about')
    def about():
        return render_template('about.html')

    return app