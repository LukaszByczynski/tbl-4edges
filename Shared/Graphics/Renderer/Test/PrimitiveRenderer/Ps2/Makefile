#
# This makefile really needs to be cleaned up.
#

EE_BIN = RenderTest.elf
EE_OBJS = ../main.o \
		  ../../../../../../Shared/Graphics/Renderer/Ps2/Renderer.o \
		  ../../../../../../Shared/Graphics/Renderer/Ps2/DrawingEnviroment.o \
		  ../../../../../../Shared/Graphics/Renderer/Ps2/PrimitiveRenderer.o \
		  ../../../../../../Shared/Graphics/Renderer/Ps2/PrimitiveRenderer_Vcl.o \
		  ../../../../../../Shared/Hardware/Ps2/Dma.o \
		  ../../../../../../Shared/Base/Log/Log.o \
		  ../../../../../../Shared/Base/Io/Ps2/File.o \
		  ../../../../../../Shared/Base/Debug/Ps2/Assert.o \
		  ../../../../../../Shared/Hardware/Ps2/Vu1.o \
		  ../../../../../../Shared/Base/Math/Ps2/Matrix4.o
EE_LIBS =  -lc -lkernel -lgcc -lsyscall
EE_INCS = -I../../../../../../ -DCELL_PS2 -D_DEBUG

all: $(EE_BIN)

.SECONDARY: ../../../../../../Shared/Graphics/Renderer/Ps2/PrimitiveRenderer_Vcl.vsm

clean:
	rm -f *.elf *.o *.a $(EE_OBJS)
run:
	ps2client reset
	sleep 4
	ps2client -t 4 execee host:$(EE_BIN)

include $(PS2SDK)/samples/Makefile.pref

# Include directories
EE_INCS := -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I. $(EE_INCS)

VCL = openvcl #  vcl_14beta7

# C compiler flags
EE_CFLAGS := -D_EE -O2 -G0 -Wall $(EE_CFLAGS)

# C++ compiler flags
EE_CXXFLAGS := -D_EE -O2 -G0 -Wall $(EE_CXXFLAGS)

# Linker flags
EE_LDFLAGS := -L$(PS2SDK)/ee/lib $(EE_LDFLAGS)

# Assembler flags
EE_ASFLAGS := -G0 $(EE_ASFLAGS)

# Link with following libraries.  This is a special case, and instead of
# allowing the user to override the library order, we always make sure
# libkernel is the last library to be linked.
EE_LIBS += -lkernel -lc -lkernel -lsyscall

# Externally defined variables: EE_BIN, EE_OBJS, EE_LIB

# These macros can be used to simplify certain build rules.
EE_C_COMPILE = $(EE_CC) $(EE_CFLAGS) $(EE_INCS)
EE_CXX_COMPILE = $(EE_CXX) $(EE_CXXFLAGS) $(EE_INCS)

%.o : %.c
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

%.o : %.cpp
	$(EE_CXX)  -fshort-double -fno-exceptions -fno-rtti $(EE_CXXFLAGS) $(EE_INCS) -c $< -o $@ 2>&1 | Gcc2MS

%.o : %.S
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

%.o : %.s
	$(EE_AS) $(EE_ASFLAGS) $< -o $@

%.o : %.vsm
	dvp-as $< -o $@

%.vsm : %.vcl
	$(VCL) -o$@ $<

$(EE_BIN) : $(EE_OBJS) $(PS2SDK)/ee/startup/crt0.o
	$(EE_CC) -nostdlib -T$(PS2SDK)/ee/startup/linkfile $(EE_LDFLAGS) \
		-o $(EE_BIN) $(PS2SDK)/ee/startup/crt0.o $(EE_OBJS) $(EE_LIBS)
	ee-strip $(EE_BIN)

$(EE_LIB) : $(EE_OBJS)
	$(EE_AR) cru $(EE_LIB) $(EE_OBJS)
