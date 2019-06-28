from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from re import sub
from decimal import Decimal
from helpers import apology, login_required, lookup, usd
# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of books"""

    # Query database for user's cash
    rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    if not rows:
        return apology("missing user")
    cash = rows[0]["cash"]

    # Query database for user's books
    books = db.execute("""SELECT Title, GBP_Price FROM transactions
        WHERE user_id = :user_id""", user_id=session["user_id"])

    # Query journals database to retreive info about books the user has!
    for book in books:
        book1 = lookup(book["Title"])
        book["GBP_Price"] = book1["GBP_Price"]
        book["transacted"] = book1["transacted"]


    # Render portfolio
    return render_template("index.html", cash=cash, books=books)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Enable user to buy a book."""

    # POST
    if request.method == "POST":

        # Validate form submission
        if not request.form.get("Title"):
            return apology("missing Title")

        # Get book's quote
        quote = lookup(request.form.get("Title"))
        if not quote:
            return apology("invalid Title")

        cost = quote["GBP_Price"]


        # Get user's cash balance
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        if not rows:
            return apology("missing user")
        cash = rows[0]["cash"]


        # Record purchase
        db.execute("""INSERT INTO transactions (user_id, Title, GBP_Price)
            VALUES(:user_id, :Title, :GBP_Price)""",
                   user_id=session["user_id"], Title=quote["Title"], GBP_Price=cost)

        # Deduct cash
        db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id",
                   cost=cost, id=session["user_id"])

        # Display portfolio
        flash(cash)
        return redirect("/")

    # GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Display user's history of transactions."""
    transactions = db.execute(
        "SELECT Title, GBP_Price, transacted FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        print(rows)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out."""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")


@app.route("/search", methods=["GET", "POST"])
@login_required
def search():
    """Search for book."""

    return render_template("search.html")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get a book quote."""

    # POST
    if request.method == "POST":

        # Validate form submission
        if not request.form.get("Title"):
            return apology("missing Title")

        # Get stock quote
        quote = lookup(request.form.get("Title"))
        if not quote:
            return apology("invalid Title")

        # Display quote
        return render_template("quoted.html", quote=quote)

    # GET
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user for an account."""

    # POST
    if request.method == "POST":

        # Validate form submission
        if not request.form.get("username"):
            return apology("missing username")
        elif not request.form.get("password"):
            return apology("missing password")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match")

        # Add user to database
        id = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                        username=request.form.get("username"),
                        hash=generate_password_hash(request.form.get("password")))
        if not id:
            return apology("username taken")

        # Log user in
        session["user_id"] = id

        # Let user know they're registered
        flash("Registered!")
        return redirect("/")

    # GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Enable user to sell a stock."""

    # POST
    if request.method == "POST":

        # Validate form submission
        if not request.form.get("Title"):
            return apology("missing title")
        Title = request.form.get("Title")

        # Check how many shares user owes
        rows = db.execute("""SELECT * FROM transactions
            WHERE user_id = :user_id AND Title = :Title GROUP BY Title""",
                          user_id=session["user_id"], Title = Title)
        if len(rows) != 1:
            return apology("book not owned")

        # Get price quote
        quote = lookup(request.form.get("Title"))

        # Record sale
        db.execute("""INSERT INTO transactions (user_id, Title, GBP_Price)
            VALUES(:user_id, :Title, :GBP_Price)""",
                   user_id=session["user_id"], Title=quote["Title"], price=quote["GBP_Price"])

        # Deposit cash
        db.execute("UPDATE users SET cash = cash + :value WHERE id = :id",
                   value=quote["GBP_Price"], id=session["user_id"])

        # Display portfolio
        flash("Sold!")
        return redirect("/")

    # GET
    else:

        # Get symbols owned
        rows = db.execute("""SELECT Title FROM transactions
                            WHERE user_id = :user_id GROUP BY Title""",
                          user_id=session["user_id"])
        Title = [row["Title"] for row in rows]

        # Display sales form
        return render_template("sell.html", Title = Title) #Titles=Titles?


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
