.PHONEY: debug release clean

debug:
	mkdir -p build && cd build; \
	conan install --build missing -s build_type=Debug ..; \
	cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON ..; \
	make -j2

release:
	# NOTE: 手动指定 -DCMAKE_BUILD_TYPE=Release 后才看到 -O3 编译参数, 不指定的话没有, 原因未查
	mkdir -p build && cd build; \
	conan install --build missing -s build_type=Release ..; \
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE=ON -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON ..; \
	cmake ..; \
	make -j2

clean:
	rm -rf build
