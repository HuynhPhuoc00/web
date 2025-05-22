PYTHON_VERSION = $(shell python3 -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
PYBIND11_INCLUDE = $(shell python3 -m pybind11 --includes)
EXT_SUFFIX = $(shell python3-config --extension-suffix)

all:
	python3 -m http.server 8080
	c++ -O3 -Wall -shared -std=c++11 -fPIC $(PYBIND11_INCLUDE) \
	my_module.cpp -o my_module$(EXT_SUFFIX)

clean:
	rm -f my_module*.so
	# Remove any versioned shared object files
	rm -f my_module*.so.*