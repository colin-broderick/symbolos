FROM debian:latest AS builder

RUN apt update
RUN apt install -y binutils git gcc g++ make python3 libmpc-dev texinfo libmpfr-dev libgmp3-dev flex bison diffutils sed grep cmake grub-common xorriso grub-pc-bin

ENV PREFIX="/opt/cross"
ENV TARGET=i686-elf
ENV PATH="$PREFIX/bin:$PATH"

WORKDIR /deps

RUN git clone git://sourceware.org/git/binutils-gdb.git --branch binutils-2_45 --depth 1
RUN mkdir build-binutils 
RUN mkdir -p $PREFIX/bin
RUN cd build-binutils  && sh ../binutils-gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
RUN cd build-binutils && make -j8 && make install

RUN git clone git://sourceware.org/git/gcc.git --branch releases/gcc-14.2.0 --depth 1
RUN mkdir build-gcc
RUN cd build-gcc && ../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
RUN cd build-gcc && make all-target-libgcc -j8
RUN cd build-gcc && make all-target-libstdc++-v3 -j8
RUN cd build-gcc && make install-gcc
RUN cd build-gcc && make install-target-libgcc
RUN cd build-gcc && make install-target-libstdc++-v3

WORKDIR /symbol
COPY . .

WORKDIR /symbol-build
RUN cmake /symbol
RUN make iso -j8

FROM scratch AS output
COPY --from=builder /symbol-build/symbol.bin /symbol.bin
COPY --from=builder /symbol-build/symbol.iso /symbol.iso
