from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
import datetime
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


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
 # select stock and the share of each stock
    stock_symbol = db.execute("SELECT shares, symbol \
                                    FROM stocks WHERE id = :id",
                              id=session["user_id"])

    # stores the total assets including cash
    t_cash = 0

    # update the stock table by finding changes in number of shares held for each stock
    # change amount of cash accordingly
    for i in stock_symbol:
        symbol = i["symbol"]
        shares = i["shares"]
        stock = lookup(symbol)
        total = shares * stock["price"]
        db.execute("UPDATE stocks SET price=:price, \
                    total=:total WHERE id=:id AND symbol=:symbol",
                   price=stock["price"],
                   total=total, id=session["user_id"], symbol=symbol)

    # add this amount which user already has to the product of shares and stock
    new_cash = db.execute("SELECT cash FROM users \
                               WHERE id=:id", id=session["user_id"])

    new_stocks = db.execute("SELECT * from stocks \
                                    WHERE id=:id", id=session["user_id"])

    return render_template("index.html", stocks=new_stocks,
                            cash=usd(new_cash[0]["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    if request.method == "GET":
        return render_template("buy.html")
    else:
        # ensure proper symbol
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol doesn't exist")

        shares = int(request.form.get("shares"))

        # check if shares numberical or are greater than 0
        # https://stackoverflow.com/questions/5424716/how-to-check-if-string-input-is-a-number
        try:
            val = int(shares)
        except ValueError:
            return apology("not an integer")

        if shares < 1:
            return apology("shares requested must be greater than 1")

        # select user's cash
        money = db.execute("SELECT cash FROM users WHERE id = :id",
                           id=session["user_id"])

        # check if enough money to buy
        # use float for comparison since stock price might be not be a whole number
        if not money or float(money[0]["cash"]) < stock["price"] * shares:
            return apology("Not enough money")

        # record time of transaction
        time = datetime.datetime.now()

        # update history/transaction table
        db.execute("INSERT INTO transactions (id, stock, shares, price, time, total) \
                    VALUES(:id, :symbol, :shares, :price, :time, :total)",
                   id=session["user_id"], symbol=stock["symbol"], shares=shares, price=usd(stock["price"]), time=time, total=usd(shares * stock["price"]))

        # update user cash
        db.execute("UPDATE users SET cash = cash - :bought WHERE id = :id",
                   id=session["user_id"], bought=stock["price"] * float(shares))

        # Update user's shares in the stock table
        # Select shares that user already has from stocks table
        shares_1 = db.execute("SELECT shares FROM stocks\
                           WHERE id = :id AND symbol= :symbol",
                              id=session["user_id"], symbol=stock["symbol"])

        # if user doesn't have shares of that stock make new one
        if not shares_1:
            db.execute("INSERT INTO stocks (id, symbol, shares, price, total) \
                        VALUES(:id, :symbol, :sharesbought, :price, :total)",
                       id=session["user_id"], symbol=stock["symbol"],
                       price=usd(stock["price"]), sharesbought=shares,
                       total=usd(shares * stock["price"]))

        # Else add the shares to already existing ones
        else:
            t_shares = shares_1[0]["shares"] + shares
            db.execute("UPDATE stocks SET shares =:shares \
                        WHERE id=:id AND symbol =:symbol",
                       shares=t_shares, id=session["user_id"],
                       symbol=stock["symbol"])

        # return to index
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT stock, shares, price, time FROM transactions WHERE id=:id", id=session["user_id"])

    for t in transactions:
        stock = t["stock"]
        shares = t["shares"]
        price = t["price"]
        time = t["time"]

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

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
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        #   use lookup in helpers on the symbol submitted by user
        symbol_2 = lookup(request.form.get("symbol"))

        #   if symbol doesn't exist then return error
        if not symbol_2:
            return apology("Symbol doesn't exist")

        else:

            return render_template("quoted.html", symbol=symbol_2)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match")

        # insert new user and its unique hash value
        store = db.execute("INSERT INTO users (username, hash) \
                           VALUES(:username, :hash)",
                           username=request.form.get("username"),
                           hash=generate_password_hash(request.form.get("password")))

        # check if store can't be executed because row already exists
        # display error
        if not store:
            return apology("Username exists/try a new one")

        # remember which user has logged in
        session["user_id"] = store

        # redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    else:
        sym = request.form.get("symbol")
        stock_sell = lookup(sym)
        if not stock_sell:
            return apology("Invalid Symbol")

        # ensure proper number of shares
        shares = 0

        while shares <= 0:
            shares = int(request.form.get("shares"))
            if shares > 0:
                break
            else:
                return apology("Shares must be greater than 0")

        # select the symbol and shares of that user
        user_s = db.execute("SELECT shares FROM stocks \
                                 WHERE id =:id AND symbol =:symbol",
                            id=session["user_id"], symbol=stock_sell["symbol"])

        # check if user has any shares to sell
        if not user_s or int(user_s[0]["shares"]) < shares:
            return apology("Not enough shares to sell")

        time = datetime.datetime.now()

        # update history
        db.execute("INSERT INTO transactions (id, stock, shares, price, time, total ) \
                    VALUES(:id, :symbol, :shares,  :price, :time, :total)",
                   id=session["user_id"], symbol=stock_sell["symbol"], shares=shares, price=usd(stock_sell["price"]), time=time, total=usd(shares * stock_sell["price"]))

        # update cash in users table
        # use float to avoid issues with multiplying decimal values
        db.execute("UPDATE users SET cash = (cash + :sold) WHERE id =:id",
                   id=session["user_id"],
                   sold=stock_sell["price"] * float(shares))

        # update trasactions with shares left
        share_total = user_s[0]["shares"] - shares

        # delete shares if shares = 0 after
        # if not then update transactions with new shares left
        if share_total == 0:
            db.execute("DELETE FROM stocks \
                        WHERE id =:id AND symbol =:symbol",
                       id=session["user_id"],
                       symbol=stock_sell["symbol"])

        else:
            db.execute("UPDATE stocks SET shares=:shares \
                    WHERE id =:id AND symbol =:symbol",
                       shares=share_total, id=session["user_id"],
                       symbol=stock_sell["symbol"])

        # return to index
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
