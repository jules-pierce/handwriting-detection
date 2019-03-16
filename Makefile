# Note that this makefile must end in
# a carriage return, and "command" lines must begin with a
# tab character

#ADDING A NEW APP:
# uncomment 3 lines: APPNAMEn, SRCn, and the appropriate rm line
# fill in the APPNAMEn and SRCn lines as required by replacing the "xxx"

#############################
# Edit the APPNAME and SRC lines below
############################

# The name of the app being built
APPNAME01 = handwrite
APPNAME02 = bmp2ts
#APPNAME03 = xxx
#APPNAME04 = xxx
#APPNAME05 = xxx
#APPNAME06 = xxx
#APPNAME07 = xxx
#APPNAME08 = xxx
#APPNAME09 = xxx
#APPNAME10 = xxx
#APPNAME11 = xxx
#APPNAME12 = xxx
#APPNAME13 = xxx
#APPNAME14 = xxx
#APPNAME15 = xxx
#APPNAME16 = xxx
#APPNAME17 = xxx
#APPNAME18 = xxx
#APPNAME19 = xxx
#APPNAME20 = xxx
#APPNAME21 = xxx
#APPNAME22 = xxx
#APPNAME23 = xxx
#APPNAME24 = xxx
#APPNAME25 = xxx
#APPNAME26 = xxx
#APPNAME27 = xxx
#APPNAME28 = xxx
#APPNAME29 = xxx
#APPNAME30 = xxx
#APPNAME31 = xxx

#  The source files needed to build this app
SRC01 = handwrite.c input_bmp.c imgstuff.c output_bmp.c
SRC02 = bmp2ts.c input_bmp.c imgstuff.c 
#SRC03 = xxx
#SRC04 = xxx
#SRC05 = xxx
#SRC06 = xxx
#SRC07 = xxx
#SRC08 = xxx
#SRC09 = xxx
#SRC10 = xxx
#SRC11 = xxx
#SRC12 = xxx
#SRC13 = xxx
#SRC14 = xxx
#SRC15 = xxx
#SRC16 = xxx
#SRC17 = xxx
#SRC18 = xxx
#SRC19 = xxx
#SRC20 = xxx
#SRC21 = xxx
#SRC22 = xxx
#SRC22 = xxx
#SRC23 = xxx
#SRC24 = xxx
#SRC25 = xxx
#SRC26 = xxx
#SRC27 = xxx
#SRC28 = xxx
#SRC29 = xxx
#SRC30 = xxx
#SRC31 = xxx

#############################
# Edit the lines below if any special libraries need to be linked
# or include directories need to be searched
############################

INCLUDES = -I.

LIBS = -lm

#############################
# Should not need to edit anything below here under normal circumstances
############################

# the C++ compiler we are using, and our preferred flags
CPP = g++
CPPFLAGS = -mms-bitfields -O3 $(INCLUDES)

#How to build a .o file from a .cpp file
.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

#How to build a .o file from a .cc file
.cc.o:
	$(CPP) $(CPPFLAGS) -c $<

#How to build a .o file from a .c file
.c.o:
	$(CPP) $(CPPFLAGS) -c $<

# Strip off the .cc, .c, and .cpp suffixes for all files in SRC and replace 
# them with .o.  These object files are our dependencies for building the
# target
OBJ01 = $(addsuffix .o, $(basename $(SRC01)))
OBJ02 = $(addsuffix .o, $(basename $(SRC02)))
OBJ03 = $(addsuffix .o, $(basename $(SRC03)))
OBJ04 = $(addsuffix .o, $(basename $(SRC04)))
OBJ05 = $(addsuffix .o, $(basename $(SRC05)))
OBJ06 = $(addsuffix .o, $(basename $(SRC06)))
OBJ07 = $(addsuffix .o, $(basename $(SRC07)))
OBJ08 = $(addsuffix .o, $(basename $(SRC08)))
OBJ09 = $(addsuffix .o, $(basename $(SRC09)))
OBJ10 = $(addsuffix .o, $(basename $(SRC10)))
OBJ11 = $(addsuffix .o, $(basename $(SRC11)))
OBJ12 = $(addsuffix .o, $(basename $(SRC12)))
OBJ13 = $(addsuffix .o, $(basename $(SRC13)))
OBJ14 = $(addsuffix .o, $(basename $(SRC14)))
OBJ15 = $(addsuffix .o, $(basename $(SRC15)))
OBJ16 = $(addsuffix .o, $(basename $(SRC16)))
OBJ17 = $(addsuffix .o, $(basename $(SRC17)))
OBJ18 = $(addsuffix .o, $(basename $(SRC18)))
OBJ19 = $(addsuffix .o, $(basename $(SRC19)))
OBJ20 = $(addsuffix .o, $(basename $(SRC20)))
OBJ21 = $(addsuffix .o, $(basename $(SRC21)))
OBJ22 = $(addsuffix .o, $(basename $(SRC22)))
OBJ23 = $(addsuffix .o, $(basename $(SRC23)))
OBJ24 = $(addsuffix .o, $(basename $(SRC24)))
OBJ25 = $(addsuffix .o, $(basename $(SRC25)))
OBJ26 = $(addsuffix .o, $(basename $(SRC26)))
OBJ27 = $(addsuffix .o, $(basename $(SRC27)))
OBJ28 = $(addsuffix .o, $(basename $(SRC28)))
OBJ29 = $(addsuffix .o, $(basename $(SRC29)))
OBJ30 = $(addsuffix .o, $(basename $(SRC30)))
OBJ31 = $(addsuffix .o, $(basename $(SRC31)))

# The target APPNAME depends on the OBJ files
$(APPNAME01): $(OBJ01)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ01) $(LIBS)

$(APPNAME02): $(OBJ02)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ02) $(LIBS)

$(APPNAME03): $(OBJ03)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ03) $(LIBS)

$(APPNAME04): $(OBJ04)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ04) $(LIBS)

$(APPNAME05): $(OBJ05)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ05) $(LIBS)

$(APPNAME06): $(OBJ06)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ06) $(LIBS)

$(APPNAME07): $(OBJ07)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ07) $(LIBS)

$(APPNAME08): $(OBJ08)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ08) $(LIBS)

$(APPNAME09): $(OBJ09)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ09) $(LIBS)

$(APPNAME10): $(OBJ10)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ10) $(LIBS)

$(APPNAME11): $(OBJ11)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ11) $(LIBS)

$(APPNAME12): $(OBJ12)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ12) $(LIBS)

$(APPNAME13): $(OBJ13)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ13) $(LIBS)

$(APPNAME14): $(OBJ14)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ14) $(LIBS)

$(APPNAME15): $(OBJ15)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ15) $(LIBS)

$(APPNAME16): $(OBJ16)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ16) $(LIBS)

$(APPNAME17): $(OBJ17)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ17) $(LIBS)

$(APPNAME18): $(OBJ18)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ18) $(LIBS)

$(APPNAME19): $(OBJ19)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ19) $(LIBS)

$(APPNAME20): $(OBJ20)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ20) $(LIBS)

$(APPNAME21): $(OBJ21)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ21) $(LIBS)

$(APPNAME22): $(OBJ22)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ22) $(LIBS)

$(APPNAME23): $(OBJ23)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ23) $(LIBS)

$(APPNAME24): $(OBJ24)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ24) $(LIBS)

$(APPNAME25): $(OBJ25)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ25) $(LIBS)

$(APPNAME26): $(OBJ26)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ26) $(LIBS)

$(APPNAME27): $(OBJ27)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ27) $(LIBS)

$(APPNAME28): $(OBJ28)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ28) $(LIBS)

$(APPNAME29): $(OBJ29)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ29) $(LIBS)

$(APPNAME30): $(OBJ30)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ30) $(LIBS)

$(APPNAME31): $(OBJ31)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ31) $(LIBS)

# clean up by removing .o files and thecutable
# ***the "rm" lines below must be preceded by a TAB****
clean:
	rm -f $(OBJ01) $(APPNAME01) Makefile.am
	rm -f $(OBJ02) $(APPNAME02) Makefile.am
	rm -f $(OBJ03) $(APPNAME03) Makefile.am
	rm -f $(OBJ04) $(APPNAME04) Makefile.am
#rm -f $(OBJ05) $(APPNAME05) Makefile.am
#rm -f $(OBJ06) $(APPNAME06) Makefile.am
#rm -f $(OBJ07) $(APPNAME07) Makefile.am
#rm -f $(OBJ08) $(APPNAME08) Makefile.am
#rm -f $(OBJ09) $(APPNAME09) Makefile.am
#rm -f $(OBJ10) $(APPNAME10) Makefile.am
#rm -f $(OBJ11) $(APPNAME11) Makefile.am
#rm -f $(OBJ12) $(APPNAME12) Makefile.am
#rm -f $(OBJ13) $(APPNAME13) Makefile.am
#rm -f $(OBJ14) $(APPNAME14) Makefile.am
#rm -f $(OBJ15) $(APPNAME15) Makefile.am
#rm -f $(OBJ16) $(APPNAME16) Makefile.am
#rm -f $(OBJ17) $(APPNAME17) Makefile.am
#rm -f $(OBJ18) $(APPNAME18) Makefile.am
#rm -f $(OBJ19) $(APPNAME19) Makefile.am
#rm -f $(OBJ20) $(APPNAME20) Makefile.am
#rm -f $(OBJ21) $(APPNAME21) Makefile.am
#rm -f $(OBJ22) $(APPNAME22) Makefile.am
#rm -f $(OBJ23) $(APPNAME23) Makefile.am
#rm -f $(OBJ24) $(APPNAME24) Makefile.am
#rm -f $(OBJ25) $(APPNAME25) Makefile.am
#rm -f $(OBJ26) $(APPNAME26) Makefile.am
#rm -f $(OBJ27) $(APPNAME27) Makefile.am
#rm -f $(OBJ28) $(APPNAME28) Makefile.am
#rm -f $(OBJ30) $(APPNAME30) Makefile.am
#rm -f $(OBJ31) $(APPNAME31) Makefile.am

#cuting this target will add .h dependencies on the end of this
# file.  NOTE: this doesn't work on windows under mingw, msys
depend:
	makedepend $(CPPFLAGS) -Y $(SRC)

# can list .o dependencies on .h files here manually if desired.  This
# can be useful on a platform where makedepend does not work.
# NOTE: the file must end in a carriage return

