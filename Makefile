CXX = g++
CXXFLAGS = -lcurl -Wall -std=c++17
TARGET = main

all: firmware-build run

firmware-build:
	make -C /home/phuoc/Documents/web/IoT_Prj/PRJ_001/Debug all

run:
	@echo "==> Start Flask server"
	@python3 server.py & \
	sleep 2 && \
	echo "==> Compile C++" && \
	$(CXX) cpp_control.cpp -o $(TARGET) $(CXXFLAGS) && \
	./$(TARGET)

clean:
	rm -f $(TARGET)
	make -C /home/phuoc/Documents/web/IoT_Prj/PRJ_001/Debug clean
