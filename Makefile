CC=g++
CFLAGS=-c -Wall
LDFLAGS=
PTLDFLAGS=-lpthread

SEC_SOURCES=SMain.cpp Rutas.cpp
SEC_OBJECTS=$(SEC_SOURCES:.cpp=.o)
SEC_EXECUTABLE=secuencial

PAR_SOURCES=PMain.cpp Rutas.cpp
PAR_OBJECTS=$(PAR_SOURCES:.cpp=.o)
PAR_EXECUTABLE=paralelo

all: secuencial paralelo

secuencial: $(SEC_SOURCES) $(SEC_EXECUTABLE)

paralelo: $(PAR_SOURCES) $(PAR_EXECUTABLE)

$(SEC_EXECUTABLE): $(SEC_OBJECTS) 
	$(CC) $(LDFLAGS) $(SEC_OBJECTS) -o $@

$(PAR_EXECUTABLE): $(PAR_OBJECTS) 
	$(CC) $(PTLDFLAGS) $(PAR_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o

