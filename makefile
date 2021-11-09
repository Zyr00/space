CC = gcc

SDL_CFLAGS := $(shell pkg-config --cflags SDL2_image)
SDL_LDFALGS := $(shell pkg-config --libs SDL2_image) $(shell pkg-config --libs SDL2_mixer)

CFLAGS := -Wall -g $(SDL_CFLAGS)
LDFLAGS := $(SDL_LDFALGS)

SDIR = src
ODIR = obj
HDIR = includes

SDIRS = $(wildcard $(SDIR)/*.c)
ODIRS = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SDIRS))
HDRS = $(wildcard $(HDIR)/*.h)

BIN = main

all: $(BIN)

$(BIN): $(ODIRS) $(ODIR) $(HDRS)
	$(CC) $(CFLAGS) $(ODIRS) -o $@ $(LDFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

docs:
ifneq ("$(wildcard ./docs)", "")
	rm -rf docs
endif
	doxygen .doxygen

clean:
	rm -fr $(ODIR)
ifneq ("$(wildcard ./$(BIN))","")
	rm $(BIN)
endif


