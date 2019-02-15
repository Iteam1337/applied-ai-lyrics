FROM python:3.7

WORKDIR /usr/src/app

COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

ENV FLASK_APP app.py

EXPOSE 5000
CMD flask run --host=0.0.0.0