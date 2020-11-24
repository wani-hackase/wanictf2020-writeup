# docker build -t basic_rsa .
# docker run -itd --rm --name basic_rsa -p50000:50000 basic_rsa

FROM python:3.8-alpine

RUN apk --no-cache add socat

RUN apk add gcc
RUN apk add musl-dev
RUN apk add gmp-dev

RUN pip install pycrypto

ADD server.py server.py
ADD const.py const.py

CMD socat -dd -v >/dev/stdout TCP-L:50000,fork,reuseaddr EXEC:"python -u server.py"
