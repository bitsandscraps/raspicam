CC=gcc
CCFLAGS=-Werror -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes\
        -Wdeclaration-after-statement -Wextra -O2
LDPATH=-L$(HOME)/git/raspberrypi/userland/build/lib
LDLIBS=-lpthread -lraspicamcv -lm -lmmal_core -lmmal -lmmal_util -lvcos\
       -lbcm_host -lopencv_core -lopencv_highgui -lopencv_imgproc
OBJDIR=objs
BINDIR=bin
#Pattern rule
all: raspicam
clobber: clean
	rm -fv *~ \#*\# core .*.sw*
clean:
	rm -rfv $(BINDIR) $(OBJDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -c -o $@ $<
raspicam: $(OBJDIR)/raspi_camera.o $(OBJDIR)/raspi_cmain.o | $(BINDIR)
	$(CC) $(CCFLAGS) $^ $(LDPATH) $(LDLIBS) -o $(BINDIR)/$@
all: raspicam

