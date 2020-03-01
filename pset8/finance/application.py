import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

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
    """Show portfolio of stocks"""
    # query for user's portfolio
    portfolio = db.execute("SELECT * FROM portfolio WHERE id=:id", id=session.get('user_id'))

    # variable to tally portfolio's total value
    portfolioValue = 0

    # add latest stock price and total stock value to portfolio dict
    for row in portfolio:
        row["price"] = lookup(row["symbol"])["price"]
        row["total"] = row["shares"] * row["price"]
        portfolioValue += row["total"]

    # query for user's cash
    cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session.get('user_id'))[0]["cash"]
    portfolioValue += cash

    return render_template("portfolio.html", portfolio=portfolio, cash=usd(cash), portfolioValue=usd(portfolioValue))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        # validation - invalid symbol or blank
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("Invalid symbol", 400)

        # validation - shares is blank
        if not request.form.get("shares"):
            return apology("Invalid number of shares", 400)

        # validation - shares is non-numeric or a float
        if not request.form.get("shares").isdigit():
            return apology("Invalid number of shares", 400)

        # validation - shares is 0, negative
        if int(request.form.get("shares")) < 1:
            return apology("Invalid number of shares", 400)

        # store data
        id = session.get('user_id')
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        price = lookup(symbol)["price"]
        cash = int(db.execute("SELECT cash FROM users WHERE id=:id", id=id)[0]["cash"])
        remainingCash = cash - (price * shares)

        # validation - check if insufficient funds
        if remainingCash < 0:
            return apology("Insufficient Funds", 400)

        # insert transaction into SQL table: ledger
        # orderType Buy: 1; Sell: 0.
        db.execute("INSERT INTO ledger (userId, orderType, symbol, shares, stockPrice) VALUES (:id, '1', :symbol, :shares, :price)",
                   id=id,
                   symbol=symbol,
                   shares=shares,
                   price=price)

        # update cash in SQL table: users
        db.execute("UPDATE users SET cash=:cash WHERE id=:id",
                   cash=remainingCash,
                   id=id)

        # update SQL table: portfolio
        portfolioCheck = db.execute("SELECT * FROM portfolio WHERE id=:id AND symbol=:symbol",
                                    id=id,
                                    symbol=symbol)

        if len(portfolioCheck) != 0:
            # UPDATE portfolio if stock already exists
            db.execute("UPDATE portfolio SET shares = shares + :shares WHERE id=:id AND symbol=:symbol",
                       shares=shares,
                       id=id,
                       symbol=symbol)
        else:
            # INSERT new stock if absent in portfolio
            db.execute("INSERT INTO portfolio (id, symbol, shares) VALUES (:id, :symbol, :shares)",
                       id=id,
                       symbol=symbol,
                       shares=shares)

    return redirect("/")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get('username')
    usernameCheck = db.execute("SELECT username FROM users WHERE username=:username", username=username)

    if len(username) != 0 and len(usernameCheck) != 0:
        return jsonify(False)
    else:
        return jsonify(True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT * FROM ledger WHERE userId=:id ORDER BY 1 DESC", id=session.get('user_id'))

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
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    else:
        # validation
        # check if input is blank
        if not request.form.get("symbol"):
            return apology("Please enter symbol", 400)

        # check if symbol is valid
        elif lookup(request.form.get("symbol")) == None:
            return apology("Invalid symbol", 400)

        # display stock quote
        else:
            JSON = lookup(request.form["symbol"])
            return render_template("quoted.html", name=JSON["name"], symbol=JSON["symbol"], price=JSON["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # do this when form is POSTed
    if request.method == "POST":
        # form validation
        # username input is blank
        if not request.form.get("username"):
            return apology("Please enter a username", 400)

        # username is taken
        if db.execute("SELECT username FROM users WHERE username = :username",
                      username=request.form.get("username")):
            return apology("Sorry, username is already taken", 400)

        # password or confirm password input is blank
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Please enter a password", 400)

        # check if passwords match
        elif request.form["password"] != request.form["confirmation"]:
            return apology("Passwords do not match", 400)

        # insert username and hashed password into SQL
        username = request.form['username']
        passwordHash = generate_password_hash(request.form['password'])
        db.execute(f"INSERT INTO users (username, hash) VALUES ('{username}', '{passwordHash}')")

        return redirect("/login")

    # return register.html when route is accessed via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        # check if symbol input entered OR if stock does not exist in user's portfolio
        portfolioCheck = db.execute("SELECT symbol, shares FROM portfolio WHERE id=:id AND symbol=:symbol",
                                    id=session.get('user_id'),
                                    symbol=request.form.get("symbol"))
        if not request.form.get("symbol") or not portfolioCheck:
            return apology("Select a valid stock", 400)

        # check if shares input entered OR if shares is 0 or a negative value OR if user's portfolio holds insufficient shares
        if not request.form.get("shares") or int(request.form.get("shares")) < 1 or portfolioCheck[0]['shares'] < int(request.form.get("shares")):
            return apology("Invalid number of shares", 400)

        # book keeping
        id = session.get('user_id')
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        price = int(lookup(symbol)['price'])
        newCashAmount = int(db.execute("SELECT cash FROM users WHERE id=:id", id=id)[0]['cash']) + (price * shares)

        # insert transactions into ledger table
        db.execute("INSERT INTO ledger (userId, orderType, symbol, shares, stockPrice) VALUES (:id, '0', :symbol, :shares, :price)",
                   id=id,
                   symbol=symbol,
                   shares=shares,
                   price=price)

        # update number of shares in portfolio
        db.execute("UPDATE portfolio SET shares = shares - :shares WHERE id=:id AND symbol=:symbol", shares=shares, id=id, symbol=symbol)
        if db.execute("SELECT shares FROM portfolio WHERE id=:id AND symbol=:symbol", id=id, symbol=symbol)[0]['shares'] < 1:
            db.execute("DELETE FROM portfolio WHERE id=:id AND symbol=:symbol", id=id, symbol=symbol)

        # update cash amount in users
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=newCashAmount, id=id)

        return redirect("/")

    else:
        portfolio = db.execute("SELECT symbol, shares FROM portfolio WHERE id = :id", id=session.get('user_id'))
        return render_template("sell.html", portfolio=portfolio)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """deposit cash"""

    if request.method == "POST":
        depositValue = int(request.form.get("deposit"))
        id = session.get("user_id")

        # Form Validation
        if depositValue <= 0:
            return apology("Invalid amount", 400)

        # INSERT deposit (orderType = 2) transaction into ledger
        db.execute("INSERT INTO ledger (userId, orderType, symbol, shares, stockPrice) VALUES (:id, '2', '', '', :depositValue)",
                   id=id,
                   depositValue=depositValue)

        # UPDATE cash in users
        db.execute("UPDATE users SET cash = cash + :depositValue WHERE id=:id",
                   depositValue=depositValue,
                   id=id)

        return redirect("/")

    else:
        return render_template("deposit.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
