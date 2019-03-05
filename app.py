import multiprocessing as mp
from generate import Generate
from flask_cors import CORS, cross_origin
from flask import Flask, jsonify, send_file

app = Flask(__name__, root_path="web/", static_url_path="/", static_folder="build/")

cors = CORS(app)
app.config["CORS_HEADERS"] = "Content-Type"


def generate_text(q, artist):
    gen = Generate(artist)
    q.put(gen.generated)


@app.route("/")
def web():
    return open("web/build/index.html").read()


@app.route("/Index.js")
def send_js():
    return open("web/build/Index.js").read()

@app.route("/img/<artist>")
def send_image(artist):
    return send_file("".join(("img/", artist)))


@app.route("/api/generate/<artist>")
@cross_origin()
def generate(artist):
    ctx = mp.get_context("spawn")
    q = ctx.Queue()
    p = ctx.Process(target=generate_text, args=(q, artist))
    p.start()

    result = q.get()

    p.join()

    return jsonify(data=result)
