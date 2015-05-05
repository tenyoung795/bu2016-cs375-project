CC = g++
CFLAGS = -g -std=c++0x 
INPUT = testGen
OUTPUT =  userInterface

all: $(INPUT)

$(INPUT): $(INPUT).o 
	$(CC) $(CFLAGS)  $< -o $(OUTPUT)

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $<   

clean:
	rm -f $(OUTPUT) $(INPUT).o 
