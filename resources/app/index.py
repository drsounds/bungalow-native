import json
from datetime import datetime
from flask import Flask
from werkzeug.exceptions import HTTPException

from template_engine import render_template

app = Flask(__name__)


@app.route("/start", methods=['GET', 'POST', 'PUT'])
def start():
    return render_template('start.xml', now=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

@app.route("/artist", methods=['GET', 'POST', 'PUT'])
def artist():
    return render_template('artist.xml', now=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))


@app.route("/library", methods=['GET', 'POST', 'PUT'])
def library():
    return render_template('library.xml', now=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))


@app.errorhandler(HTTPException)
def handle_exception(e):
    """Return JSON instead of HTML for HTTP errors."""
    # start with the correct headers and status code from the error
    response = e.get_response()
    # replace the body with JSON
    data = json.dumps({
        "code": e.code,
        "name": e.name,
        "description": e.description,
    })
    response.content_type = "text/html"

    response.data = render_template('error.xml', data=data).encode('utf-8')

    return response