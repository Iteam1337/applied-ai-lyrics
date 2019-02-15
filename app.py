import multiprocessing as mp
from generate import Generate
from flask import Flask

app = Flask(__name__)


def generate_text(q, artist):
    gen = Generate(artist)
    q.put(gen.generated)


@app.route('/api/generate/<artist>')
def generate(artist):
    ctx = mp.get_context('spawn')
    q = ctx.Queue()
    p = ctx.Process(target=generate_text, args=(q, artist))
    p.start()

    result = q.get()

    p.join()

    return result
