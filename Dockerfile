FROM ubuntu

RUN apt update -q; \
    apt install -qy make git clang cmake qpdf clitest zlib1g-dev pkg-config

RUN git clone https://gitflic.ru/project/libberesta/libberesta.git -b issue-12 libBeresta

RUN (cd libBeresta && mkdir build)
RUN (cd libBeresta/build && cmake .. -DLIBBRST_EXAMPLES=OFF -DLIBBRST_SHARED_LIB=OFF -DLIBBRST_ISO_216_ONLY=ON -DLIBBRST_DEBUG_TRACE=OFF && make)
RUN (cd libBeresta/build/tests && ctest -R test_beresta --verbose)
