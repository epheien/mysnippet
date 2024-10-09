ifeq ($(shell uname -s),Linux)
	CONAN_UPDATE_COMMAND := conan profile update settings.compiler.libcxx=libstdc++11 default
endif

.PHONEY: debug release clean

debug:
	$(CONAN_UPDATE_COMMAND)
	mkdir -p build && cd build; \
	conan install --build missing -s build_type=Debug ..; \
	cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON ..; \
	make -j2

release:
	$(CONAN_UPDATE_COMMAND)
	mkdir -p build && cd build; \
	conan install --build missing ..; \
	cmake ..; \
	make -j2

clean:
	rm -rf build
