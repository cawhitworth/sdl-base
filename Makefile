TARGET=yarlpp
CXX=clang++
SRC_PATH=yarl
BIN_PATH=build

INC=-I/usr/include/SDL2 -I$(SRC_PATH)

LIBS=-lSDL2 -lSDL2_image
LIBPATH=-L/usr/lib/x86_64-linux-gnu

CXXOPTS=-std=c++1y -stdlib=libc++ -O2

SOURCES=yarl/FPS.cpp yarl/Imp.cpp yarl/ImpRenderer.cpp yarl/Map.cpp \
	   	yarl/MapRenderer.cpp yarl/PngLoader.cpp yarl/SDLRenderer.cpp \
		yarl/SDLSurface.cpp yarl/SDLTexture.cpp yarl/SDLWrapper.cpp \
		yarl/TextRenderer.cpp \
		yarl/main.cpp

OBJS=$(SOURCES:$(SRC_PATH)/%.cpp=$(BIN_PATH)/%.o)
DEPS=$(OBJS:.o=.d)

print-%: ; @echo $*=$($*)

all: dirs $(TARGET)

clean:
	@rm -rf $(TARGET) $(BIN_PATH)

dirs:
	@mkdir -p $(BIN_PATH)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXOPTS) $(OBJS) -o $(TARGET) $(LIBPATH) $(LIBS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXOPTS) $(INC) -c $< -o $@ -MMD

