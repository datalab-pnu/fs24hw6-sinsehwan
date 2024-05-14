CC=g++
CFLAGS= -Wall 
OBJS = testIdxFile.o
INCDIR=./include
LIBDIR=./lib
DIRS = buf fixed index student_reg var
MKDIR_P = mkdir -p

.PHONY: all clean mklibdir

all: mklibdir testIdxFile
%.o: %.cpp
	$(CC) -c -I$(INCDIR) $(CFLAGS) -o $@ $<

mklibdir: $(LIBDIR)

$(LIBDIR):
	$(MKDIR_P) $(LIBDIR)

testIdxFile: $(OBJS)
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d; \
	done
	$(CC) -o testIdxFile $(OBJS) -L$(LIBDIR) -lmybuffer -lmyfixed -lmyindex -lmyrecording -lmyvar -Wl,-rpath=$(LIBDIR)
	#export LD_LIBRARY_PATH=$(LIBDIR)

clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done
	-rm -rf testIdxFile recording.dat recording.ind $(OBJS) $(LIBDIR)
