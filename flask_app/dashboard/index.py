import os

from flask import (
    Flask, Blueprint, flash, g, redirect, render_template, request, session, url_for
)

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

@app.route('/hello')
def hello():
    return 'Hello World'

import db
db.init_app(app)

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

if __name__ == "__main__":
    app.debug = True
    app.run()