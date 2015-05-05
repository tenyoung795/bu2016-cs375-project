CC = g++
CFLAGS = -g -std=c++0x 
INPUT = testGen
OUTPUT = program4

all: $(INPUT)

$(INPUT): $(INPUT).o 
	$(CC) $(CFLAGS)  $< -o $(OUTPUT)

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $<   

clean:
	rm -f $(OUTPUT) $(INPUT).o 
