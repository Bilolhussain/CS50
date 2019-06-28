from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
import csv
import os
import urllib.request

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Renders message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):

    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(Title):
    """Look up price etc for Title."""

    # Configure CS50 Library to use SQLite database
    db = SQL("sqlite:///finance.db")

    Price = db.execute("""SELECT Price FROM journal2
        WHERE Title = :Title""", Title = Title)

    Author = db.execute("""SELECT Author FROM journal2
        WHERE Title = :Title""",Title=Title)

    return {
                "Title":Title,
                "Price":Price,
                "Author":Author
            }


def usd(value):
    """Formats value as USD."""
    return f"${value:,.2f}"
