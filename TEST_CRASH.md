# Debug crash in ppc64le

This branch is created from the commit id: 9f3a8eeb1952c75d6d5f74aa4c5e6ed21e1318a8, which is being used in ceph as of now

Following are the exported flags used in ceph for compiling open-telemetry library
``` bash
export 'CFLAGS= -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong  -m64 -mcpu=power9 -mtune=power9 -fasynchronous-unwind-tables -fstack-clash-protection'
export 'CXXFLAGS= -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong  -m64 -mcpu=power9 -mtune=power9 -fasynchronous-unwind-tables -fstack-clash-protection '
export 'LDFLAGS= -Wl,-z,relro -Wl,--as-needed -Wl,-z,now -specs=/usr/lib/rpm/redhat/redhat-hardened-ld '
```

for compiling common/tracer.cc -> Where the resource is created

https://github.com/ceph/ceph/blob/v19.2.0/src/common/tracer.cc#L32
```bash
export 'CXXFLAGS= -DBOOST_ASIO_DISABLE_THREAD_KEYWORD_EXTENSION -DBOOST_ASIO_HAS_IO_URING -DBOOST_ASIO_NO_TS_EXECUTORS -DFMT_HEADER_ONLY=1 -DHAVE_ABSEIL -DHAVE_CONFIG_H -D_FILE_OFFSET_BITS=64 -D_FORTIFY_SOURCE=2 -D_GNU_SOURCE -D_REENTRANT -D_THREAD_SAFE -D__CEPH__ -D__STDC_FORMAT_MACROS -D__linux__ -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong   -m64 -mcpu=power9 -mtune=power9 -fasynchronous-unwind-tables -fstack-clash-protection -std=c++20 -fPIC   -U_FORTIFY_SOURCE -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DBOOST_PHOENIX_STL_TUPLE_H_ -Wall -fno-strict-aliasing -fsigned-char -Wtype-limits -Wignored-qualifiers -Wpointer-arith -Werror=format-security -Winit-self -Wno-unknown-pragmas -Wnon-virtual-dtor -Wno-ignored-qualifiers -ftemplate-depth-1024 -Wpessimizing-move -Wredundant-move -Wstrict-null-sentinel -Woverloaded-virtual -fstack-protector-strong -maltivec -fdiagnostics-color=auto'
export 'CFLAGS= -DBOOST_ASIO_DISABLE_THREAD_KEYWORD_EXTENSION -DBOOST_ASIO_HAS_IO_URING -DBOOST_ASIO_NO_TS_EXECUTORS -DFMT_HEADER_ONLY=1 -DHAVE_ABSEIL -DHAVE_CONFIG_H -D_FILE_OFFSET_BITS=64 -D_FORTIFY_SOURCE=2 -D_GNU_SOURCE -D_REENTRANT -D_THREAD_SAFE -D__CEPH__ -D__STDC_FORMAT_MACROS -D__linux__ -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong   -m64 -mcpu=power9 -mtune=power9 -fasynchronous-unwind-tables -fstack-clash-protection -std=c++20 -fPIC   -U_FORTIFY_SOURCE -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DBOOST_PHOENIX_STL_TUPLE_H_ -Wall -fno-strict-aliasing -fsigned-char -Wtype-limits -Wignored-qualifiers -Wpointer-arith -Werror=format-security -Winit-self -Wno-unknown-pragmas -Wnon-virtual-dtor -Wno-ignored-qualifiers -ftemplate-depth-1024 -Wpessimizing-move -Wredundant-move -Wstrict-null-sentinel -Woverloaded-virtual -fstack-protector-strong -maltivec -fdiagnostics-color=auto'
export 'LDFLAGS= -Wl,-z,relro -Wl,--as-needed -Wl,-z,now -specs=/usr/lib/rpm/redhat/redhat-hardened-ld '
```

for osd/OSD.cc -> Where it calls tracer.cc to create the resource

https://github.com/ceph/ceph/blob/v19.2.0/src/osd/OSD.cc#L3693
```bash
export 'CFLAGS= -DBOOST_ASIO_DISABLE_THREAD_KEYWORD_EXTENSION -DBOOST_ASIO_HAS_IO_URING -DBOOST_ASIO_NO_TS_EXECUTORS -DBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS -DBOOST_MPL_LIMIT_LIST_SIZE=30 -DFMT_HEADER_ONLY=1 -DHAVE_ABSEIL -DHAVE_CONFIG_H -D_FILE_OFFSET_BITS=64 -D_FORTIFY_SOURCE=2 -D_GNU_SOURCE -D_REENTRANT -D_THREAD_SAFE -D__CEPH__ -D__STDC_FORMAT_MACROS -D__linux__ -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong   -m64 -mcpu=power9 -mtune=power9 -fasynchronous-unwind-tables -fstack-clash-protection -std=c++20 -fPIC   -U_FORTIFY_SOURCE -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DBOOST_PHOENIX_STL_TUPLE_H_ -Wall -fno-strict-aliasing -fsigned-char -Wtype-limits -Wignored-qualifiers -Wpointer-arith -Werror=format-security -Winit-self -Wno-unknown-pragmas -Wnon-virtual-dtor -Wno-ignored-qualifiers -ftemplate-depth-1024 -Wpessimizing-move -Wredundant-move -Wstrict-null-sentinel -Woverloaded-virtual -fstack-protector-strong -maltivec -fdiagnostics-color=auto'
export 'CXXFLAGS= -DBOOST_ASIO_DISABLE_THREAD_KEYWORD_EXTENSION -DBOOST_ASIO_HAS_IO_URING -DBOOST_ASIO_NO_TS_EXECUTORS -DBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS -DBOOST_MPL_LIMIT_LIST_SIZE=30 -DFMT_HEADER_ONLY=1 -DHAVE_ABSEIL -DHAVE_CONFIG_H -D_FILE_OFFSET_BITS=64 -D_FORTIFY_SOURCE=2 -D_GNU_SOURCE -D_REENTRANT -D_THREAD_SAFE -D__CEPH__ -D__STDC_FORMAT_MACROS -D__linux__ -O2 -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong   -m64 -mcpu=power9 -mtune=power9 -fasynchronous-unwind-tables -fstack-clash-protection -std=c++20 -fPIC   -U_FORTIFY_SOURCE -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DBOOST_PHOENIX_STL_TUPLE_H_ -Wall -fno-strict-aliasing -fsigned-char -Wtype-limits -Wignored-qualifiers -Wpointer-arith -Werror=format-security -Winit-self -Wno-unknown-pragmas -Wnon-virtual-dtor -Wno-ignored-qualifiers -ftemplate-depth-1024 -Wpessimizing-move -Wredundant-move -Wstrict-null-sentinel -Woverloaded-virtual -fstack-protector-strong -maltivec -fdiagnostics-color=auto'
export 'LDFLAGS= -Wl,-z,relro -Wl,--as-needed -Wl,-z,now -specs=/usr/lib/rpm/redhat/redhat-hardened-ld '
```
## Run Locally

To get the similar crash behavior without the ceph changes, the above flags can be used or the following minimum one. Here in this branch, these flags are already included in the CMakeLists.txt file. Also inorder to setup the env with all required dependencies, refer the Containerfile in the project's root.

### To compile open-telemetry library
```bash
export 'CFLAGS= -O2 -flto=auto -ffat-lto-objects  -m64 -mcpu=power9 -mtune=power9'
export 'CXXFLAGS= -O2 -flto=auto -ffat-lto-objects  -m64 -mcpu=power9 -mtune=power9'
export 'LDFLAGS= -Wl,-z,relro -Wl,--as-needed -Wl,-z,now '

cd opentelemetry-cpp && mkdir build && cd build
cmake3 -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_BUILD_TYPE=Release -DWITH_JAEGER=ON -DBUILD_TESTING=OFF -DWITH_EXAMPLES=OFF ..
cmake3 --build . --target all -v && cmake3 --install . --config Debug
```

### To compile & run the test example
```bash
export 'CFLAGS= -DHAVE_ABSEIL -O2 -flto=auto -ffat-lto-objects -m64 -mcpu=power9 -mtune=power9 -fno-strict-aliasing -fPIC'
export 'CXXFLAGS= -DHAVE_ABSEIL -O2 -flto=auto -ffat-lto-objects -m64 -mcpu=power9 -mtune=power9 -fno-strict-aliasing -fPIC'
export 'LDFLAGS= -Wl,-z,relro -Wl,--as-needed -Wl,-z,now '

cd opentelemetry-cpp/example && mkdir build && cd build
cmake3 ..
cmake3 --build . --target test -v
./test_crash/test
```

## Observations

Though currently, SIGABRT is being observed instead of SIGILL which is being seen on Ceph v19, the backtrace looks similar to the one we have got so far. Also by removing the following CXX/LD flags from the test binary compilation, the core dump isn't observed

1. -DHAVE_ABSEIL -> Newely introduced in ceph v19.2.0
2. -flto=auto
3. -fno-strict-aliasing
4. -fPIC
5. -Wl,-z,now -> From LDFLAGS
