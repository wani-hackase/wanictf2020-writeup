# docker build -t lcg .
# docker run -itd --rm --name lcg -p50001:50001 lcg

FROM python:3.8-alpine

RUN apk --no-cache add socat

RUN apk add gcc
RUN apk add musl-dev
RUN apk add gmp-dev

RUN pip install pycrypto

ADD server.py server.py
ADD const.py const.py

CMD socat -dd -v >/dev/stdout TCP-L:50001,fork,reuseaddr EXEC:"python -u server.py"
