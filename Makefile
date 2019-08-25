APP=LetterBox
CXX=g++
RM=rm -f
CXXFLAGS=-O3
CPPFLAGS=
LDFLAGS=
LDLIBS=

SRCS=$(shell ls *.cxx)
OBJS=$(subst .cxx,.o,$(SRCS))

all: $(APP)

$(APP): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(APP) $(OBJS) $(LDLIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CXXFLAGS) -M $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend
