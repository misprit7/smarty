CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=

BUILD_DIR=build
SRCS=src/net.cpp \
src/matrix.cpp \
test/main.cpp

INC=-Isrc/net.h \
-Isrc/matrix.h

OBJS=$(subst .cpp,.o,$(SRCS))

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(BUILD_DIR) $(OBJS)
	$(CXX) $(LDFLAGS) -o $(BUILD_DIR)/main $(INC) $(OBJS) $(LDLIBS)

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
