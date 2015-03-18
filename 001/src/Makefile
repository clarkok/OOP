ifeq ($(OS),Windows_NT)
TARGET = result.exe
else
TARGET = result
endif

$(TARGET) : main.o visitor.o
	g++ -std=c++11 -o $@ -O2 $^

main.o : main.cpp student.h visitor.h score.h
	g++ -std=c++11 -o $@ -c -O2 $<

visitor.o : visitor.cpp student.h visitor.h score.h
	g++ -std=c++11 -o $@ -c -O2 $<

.PHONY: clean

clean:
	rm *.o $(TARGET)
