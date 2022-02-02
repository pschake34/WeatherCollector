import functools

from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
)

from dashboard.db import get_db

bp = Blueprint('dashboard', __name__)

@bp.route('/')
def home():
    db = get_db()
    return render_template('home.html')

@bp.route('/graphs')
def graphs():
    return render_template('graphs.html')

@bp.route('/about')
def about():
    return render_template('about.html')