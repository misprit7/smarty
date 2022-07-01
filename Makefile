CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=

BUILD_DIR=build
SRCS=src/net.cpp test/main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(BUILD_DIR) $(OBJS)
	$(CXX) $(LDFLAGS) -o $(BUILD_DIR)/main $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

$(BUILD_DIR):
	mkdir build

include .depend
