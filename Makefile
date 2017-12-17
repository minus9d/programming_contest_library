# 参考：https://stackoverflow.com/questions/5178125/how-to-place-object-files-in-separate-subdirectory

#Compiler and Linker
CXX          := g++

#The Target Binary Program
TARGET      := testmain

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := test
BUILDDIR    := obj
TARGETDIR   := bin
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CXXFLAGS    := -Wall -g -std=c++14
LDFLAGS     :=
INC         := -Itest -Iinclude

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------

sources     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
objects     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(subst $(SRCEXT),$(OBJEXT),$(sources)))
dependencies := $(subst .$(OBJEXT),.$(DEPEXT),$(objects))

# # for debug
# $(info $(sources))
# $(info $(objects))
# $(info $(dependencies))

#Defauilt Make
all: directories $(TARGETDIR)/$(TARGET)

#Remake
remake: cleaner all

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(dependencies)

#Link
$(TARGETDIR)/$(TARGET): $(objects)
	$(CXX) -o $(TARGETDIR)/$(TARGET) $^ $(LDFLAGS)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
	@$(CXX) $(CXXFLAGS) $(INC) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean cleaner
