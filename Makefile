CC          := g++

CFLAGS      := -std=c++11 -Wall -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lBox2D

HB          := Hummingbird-
BASE        := $(HB)Base
SFML        := $(HB)SFML
BOX2D       := $(HB)Box2D

MODULES     := $(BASE) $(SFML) $(BOX2D)

SOURCES     := $(shell find ./ -maxdepth 1 -name '*.cpp')
INCLUDES    := $(shell find ./ -maxdepth 1 -name '*.h')
STATIC_LIBS = $(shell find ./ -name '*.a')

OBJ         := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

EXE         := exe

.PHONY: $(BASE) $(SFML) $(BOX2D) clean

all: $(MODULES) $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(STATIC_LIBS) $(CFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(STATIC_LIBS) $(CFLAGS)

$(BASE):
	@$(MAKE) -C $@;

$(SFML): $(BASE)
	@$(MAKE) -C $@;

$(BOX2D): $(BASE)
	@$(MAKE) -C $@;

clean:
	rm *.o *~ $(EXE) -f
	@$(MAKE) -C $(BASE) clean;
	@$(MAKE) -C $(SFML) clean;
	@$(MAKE) -C $(BOX2D) clean;
