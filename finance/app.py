import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    id = session["user_id"]
    total = float(0)
    transactions = db.execute("SELECT symbol, shares, price FROM transactions WHERE user_id = ?", id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", id)

    for data in transactions:
        total += (data["price"] * data["shares"])
    total += cash[0]["cash"]

    return render_template("index.html", database=transactions, cash=usd(cash[0]["cash"]), total=usd(total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid value")
        valid = lookup(symbol.upper())
        if not symbol:
            return apology("must provide symbol")
        elif valid == None:
            return apology("symbol does not exist")
        elif shares <= 0:
            return apology("invalid share")
        elif float(shares) < float(request.form.get("shares")):
            return apology("invalid value")

        value = shares * valid["price"]
        id = session["user_id"]
        temp_cash = db.execute("SELECT cash FROM users WHERE id = ?", id)
        cash = (temp_cash[0]["cash"]) - value

        if cash < 0:
            return apology("insufficient funds")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, id)
        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", id, symbol, shares, valid["price"], date)

        flash(f"Bought! {usd(value)}")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    id = session["user_id"]
    if request.method == "POST":
        new_cash = request.form.get("new_cash")
        if not new_cash:
            return apology("must provide a cash")
        temp_cash = db.execute("SELECT cash FROM users WHERE id = ?", id)
        cash = temp_cash[0]["cash"] + float(new_cash)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, id)
        flash(f"Successful recharge of ${new_cash}!")
        return redirect("/")
    else:
        return render_template("add.html")


@app.route("/history")
@login_required
def history():
    id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", id)
    return render_template("history.html", transactions = transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol")

        valid = lookup(symbol.upper())

        if valid == None:
            return apology("symbol does not exist")

        return render_template("quoted.html", name=valid["name"], price=usd(valid["price"]), symbol=valid["symbol"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")
        elif not request.form.get("password"):
            return apology("must provide password")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("wrong password")

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("username already used", 400)

        passwordhash = generate_password_hash(request.form.get("password"))

        user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), passwordhash)

        # user = db.execute("SELECT id FROM users where username = ?", request.form.get("username"))

        session["user_id"] = user
        flash("Registered")

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        valid = lookup(symbol.upper())
        if not symbol:
            return apology("must provide symbol")
        elif valid == None:
            return apology("symbol does not exist")
        elif shares < 0:
            return apology("invalid share")

        value = shares * valid["price"]
        id = session["user_id"]
        temp_cash = db.execute("SELECT cash FROM users WHERE id = ?", id)

        temp_shares = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP by symbol", id, symbol)
        user_shares = temp_shares[0]["shares"]
        if shares > user_shares:
            return apology("insufficient shares")

        cash = (temp_cash[0]["cash"]) + value

        if cash < 0:
            return apology("insufficient funds")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, id)
        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", id, symbol, (-1)*shares, valid["price"], date)
        flash(f"Sold! {usd(value)}")

        return redirect("/")
    else:
        id = session["user_id"]
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols])
