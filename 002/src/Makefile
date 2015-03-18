ifeq ($(OS),Windows_NT)
TARGET = result.exe
else
TARGET = result
endif

$(TARGET) : main.o visitor.o
	g++ -g -std=c++11 -o $@ $^

main.o : main.cpp student.h visitor.h score.h config.h
	g++ -g -std=c++11 -o $@ -c $<

visitor.o : visitor.cpp student.h visitor.h score.h config.h
	g++ -g -std=c++11 -o $@ -c $<

.PHONY: clean

clean:
	rm *.o $(TARGET)
