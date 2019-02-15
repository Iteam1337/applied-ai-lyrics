from flask import Flask
from generate import Generate
import multiprocessing as mp

app = Flask(__name__)

def foo(q, artist):
    gen = Generate(artist)
    q.put(gen.generated)


@app.route("/api/generate/<artist>")
def generate(artist):
    ctx = mp.get_context('spawn')
    q = ctx.Queue()
    p = ctx.Process(target=foo, args=(q,artist))
    p.start()
    result = q.get()
    p.join()

    return result