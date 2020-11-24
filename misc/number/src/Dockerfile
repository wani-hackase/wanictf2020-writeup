# port is tekitou
# docker build -t bins .
# docker run -itd --rm --name bins -p60000:60000 bins

FROM python:3.8-alpine

RUN apk --no-cache add socat

ADD server.py server.py

CMD socat -dd -v >/dev/stdout TCP-L:60000,fork,reuseaddr EXEC:"python -u server.py"
