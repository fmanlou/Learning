CFLAGS=-Werror -g -I.
LDFLAGS= 

SOURCES=$(wildcard log/*.c lib/*.c tcp/*.c http/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

LOG_SOURCES=$(wildcard log/*.c test/t_log.c)
LOG_OBJECTS=$(patsubst %.c,%.o,$(LOG_SOURCES))

TCP_SOURCES=$(wildcard tcp/*.c log/*.c lib/*.c test/t_tcp.c)
TCP_OBJECTS=$(patsubst %.c,%.o,$(TCP_SOURCES))

CONF_SOURCES=$(wildcard conf/*.c log/*.c test/t_conf.c lib/*.c)
CONF_OBJECTS=$(patsubst %.c,%.o,$(CONF_SOURCES))

HTTP_SOURCES=$(wildcard http/*.c log/*.c lib/*.c test/t_http.c tcp/*.c conf/*.c)
HTTP_OBJECTS=$(patsubst %.c,%.o,$(HTTP_SOURCES))

TARGET=bin/durl
LOG=test/bin/log
TCP=test/bin/tcp
CONF=test/bin/conf
HTTP=test/bin/http

all: $(TARGET)
log: $(LOG)
tcp: $(TCP)
conf: $(CONF)
http: $(HTTP)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

$(LOG): $(LOG_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(LOG_OBJECTS)

$(TCP): $(TCP_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(TCP_OBJECTS) 

$(CONF): $(CONF_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(CONF_OBJECTS) 

$(HTTP): $(HTTP_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(HTTP_OBJECTS) 
	

build:
	mkdir -p bin
	mkdir -p test/bin
clean:
	rm -rf bin/durl *.o
	rm -rf test/bin/*
