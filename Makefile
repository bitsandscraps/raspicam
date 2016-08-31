CC=gcc
CCFLAGS=-Werror -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes\
        -Wdeclaration-after-statement -Wextra -O2
INCLUDE=-I$(HOME)/git/robidouille/raspicam_cv
LDPATH=-L$(HOME)/git/robidouille/raspicam_cv -L$(HOME)/git/raspberrypi/userland/build/lib
LDLIBS=-lraspicamcv -lm -lmmal_core -lmmal -lmmal_util -lvcos -lbcm_host -lopencv_core -lopencv_highgui\
       -lopencv_imgproc
#Pattern rule
all: raspicam
clobber: clean
	rm -fv *~ \#*\# core .*.sw*
clean:
	rm -fv raspicam *.o
%.o: %.c %.h
	$(CC) $(CCFLAGS) $(INCLUDE) -c $<
raspicam: raspi_camera.o
	$(CC) $(CCFLAGS) $^ $(LDPATH) $(LDLIBS) -o $@

