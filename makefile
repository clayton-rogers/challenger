CXXFLAGS:=-Wall -Wextra -pedantic -std=c++17 -O0 -g -Iarduchallenger
LDFLAGS:=$(LDFLAGS)

#SRCS:=main.cpp
SRCS:=$(shell find . -name "*.cpp")
OBJS:=$(subst .cpp,.o,$(SRCS))

challenger: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) arduchallenger/*.o
	$(RM) *.o
	$(RM) challenger

