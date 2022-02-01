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