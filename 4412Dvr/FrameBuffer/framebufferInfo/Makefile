LDFLAGS			:= 

TARGET			:= framebufferInfo

STRIP           := ls

OBJS = \
	framebufferInfo.o

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CXX) -O3 -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

%.o:%.c
	$(CXX) -c -O3 -o $@ $< $ $(LDFLAGS)

clean:
	@rm -rf *.o $(TARGET) svgfile.svg

