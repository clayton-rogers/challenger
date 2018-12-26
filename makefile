CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O0

#SRCS:=main.cpp
SRCS:=$(shell find . -name "*.cpp")
OBJS:=$(subst .cpp,.o,$(SRCS))

challenger: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) challenger

