FROM node:11.9.0 as web

WORKDIR /web

COPY ./web .

RUN npm i
RUN node_modules/.bin/bsb -make-world && node_modules/.bin/webpack


FROM python:3.7

WORKDIR /usr/src/app

COPY --from=web /web/build ./web/build

COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY lyrics ./lyrics
COPY models ./models
COPY app.py ./
COPY generate.py ./
COPY train.py ./

ENV FLASK_APP app.py

EXPOSE 5000
CMD flask run --host=0.0.0.0
