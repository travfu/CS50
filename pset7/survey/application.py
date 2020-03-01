import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    # form validation
    if not request.form.get("name"):
        return render_template("error.html", message="Please input your name")
    elif request.form.get("name").replace(" ", "").isalpha() == False:
        return render_template("error.html", message="Please enter valid name")
    elif not request.form.get("character"):
        return render_template("error.html", message="Please select a character")
    else:
        # write to .csv file
        name = request.form["name"]
        comicOrMovie = request.form["radioAnswer"]
        character = request.form["character"]
        text = [name, comicOrMovie, character]

        outfile = "survey.csv"

        with open(outfile, "a") as csv_file:
            writer = csv.writer(csv_file, delimiter=",")
            writer.writerow(text)

        csv_file.close()

        return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    # open .csv in readmode and store data in a list
    with open("survey.csv", "r") as csvFile:
        csvReader = csv.reader(csvFile, delimiter=",")
        dataset = list()
        for line in csvReader:
            dataset.append(line)
        csvFile.close()

        # pass .csv data values to jinja template engine to render table
        return render_template("sheet.html", dataset=dataset)
