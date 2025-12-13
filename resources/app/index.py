import json
import os
from flask import Flask
from werkzeug.exceptions import HTTPException

app = Flask(__name__)

from mako.template import Template


@app.route("/whatsnew")
def start():
    return Template(filename=os.path.join('views', 'start.xml')).render(data={})

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

    template = Template(filename=os.path.join('views', 'error.xml'))

    response.data = template.render(data=data).encode('utf-8')

    return response