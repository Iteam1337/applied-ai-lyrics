import multiprocessing as mp
from generate import Generate
from flask_cors import CORS, cross_origin
from flask import Flask, jsonify

app = Flask(__name__)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'

def generate_text(q, artist):
    gen = Generate(artist)
    q.put(gen.generated)


@app.route('/api/generate/<artist>')
@cross_origin()
def generate(artist):
    ctx = mp.get_context('spawn')
    q = ctx.Queue()
    p = ctx.Process(target=generate_text, args=(q, artist))
    p.start()

    result = q.get()

    p.join()

    return jsonify(data=result)
