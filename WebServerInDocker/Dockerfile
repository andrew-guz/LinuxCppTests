FROM debian

LABEL author="Andrew Guz"

WORKDIR /opt/CppWebServer

COPY ./bin .

ENV PORT=15800

EXPOSE 15800

ENTRYPOINT [ "./WebServerInDocker" ]
