# docker build -t l0g0n .
# docker run -itd --rm --name l0g0n -p50002:50002 l0g0n

FROM python:3.8-alpine

RUN apk --no-cache add socat

RUN apk add gcc
RUN apk add musl-dev
RUN apk add gmp-dev

RUN pip install pycrypto

ADD server.py server.py
ADD secret.py secret.py

CMD socat -dd -v >/dev/stdout TCP-L:50002,fork,reuseaddr EXEC:"python -u server.py"
