# SystemcExamples — the `scu` cell library

A small, header-only **SystemC** cell library of reusable hardware building
blocks, together with ready-to-run simulation test benches. It is intended as a
teaching aid and as a drop-in collection of parameterised modules you can
combine to describe larger digital systems in SystemC.

Everything lives in the `scu::` namespace.

## Modules at a glance

| Header             | Provides                                                      |
|--------------------|---------------------------------------------------------------|
| `scu/scuGates.h`   | `Or<N>`, `And<N>`, `Xor<N>`, `Nand<N>`, `Nor<N>`, `NotXor<N>`, `Not` |
| `scu/scuFullAdder.h` | `FullAdder` (1-bit), built from the gate primitives          |
| `scu/scuMux.h`     | `Mux<N, NB, DataType>` — N-to-1 multiplexer                    |
| `scu/scuDecoder.h` | `Decoder<N_IN, N_OUT>`, `DecoderEnable<N_IN, N_OUT>`           |
| `scu/scuDLatch.h`  | Level-sensitive latches (`DLatch`, `DLatchEnable`, `DLatchReset`, `DLatchEnableReset`, and their clocked variants) |
| `scu/scuRegister.h` | Edge-sensitive registers (`Register`, `RegisterEnable`, `RegisterReset`, `RegisterEnableReset`) |
| `scu/scuDefines.h` | Internal helpers (`SCU_REPORT_FATAL`, `SCU_INIT_PORT_NAME`, `scu::intToString`) |
| `scu/scu.h`        | Umbrella header that pulls everything in                       |

Every user-facing class is a template where it makes sense (bit-width, number
of inputs, data type…) so the same cell can be instantiated for any `sc_int`,
`sc_uint`, `bool` or other SystemC-compatible type.

## Requirements

- A C++ compiler with C++11 support (`g++ 4.8+`, `clang 3.3+`).
- [Accellera SystemC](https://systemc.org) 2.2 or later installed locally.
  The 2.3.x series is recommended.
- GNU Make.

## Getting SystemC

Download and build SystemC from <https://systemc.org>, then set the
`SYSTEMC_HOME` environment variable to its install prefix, for example:

```sh
export SYSTEMC_HOME=/opt/systemc
```

The build system auto-detects the correct library directory
(`lib`, `lib-linux`, `lib-linux64`, `lib-macos`).

## Quick start

Clone the repository and build any of the bundled examples:

```sh
git clone https://github.com/ronalanto03/SystemcExamples.git
cd SystemcExamples
export SYSTEMC_HOME=/path/to/systemc

# Build and run a single example:
make -C scu/moduleTest/gates/and run

# Build every example at once:
make all

# Run every example:
make run-all

# Remove generated files:
make clean
```

## Using the library in your own project

The library is header-only. Point your compiler at the `scu/` directory and
include either the umbrella header or the specific module you need:

```cpp
#include <systemc.h>
#include <scu.h>          // everything, or cherry-pick:
// #include <scuGates.h>
// #include <scuRegister.h>

int sc_main(int, char*[]) {
    sc_clock         clk("clk", 10, SC_NS);
    sc_signal<bool>  a, b, y;

    scu::And<2> gate("and_gate");
    gate.x_in[0](a);
    gate.x_in[1](b);
    gate.z_out(y);

    sc_start(100, SC_NS);
    return 0;
}
```

Compile against SystemC:

```sh
g++ -std=c++11 -I$SYSTEMC_HOME/include -Iscu \
    -L$SYSTEMC_HOME/lib-linux64 \
    my_design.cpp -lsystemc -lm -o my_design
```

More examples live in [`docs/USAGE.md`](docs/USAGE.md).

## Repository layout

```
scu/                       — header-only library
  scu.h                    — umbrella header
  scuDefines.h             — shared macros / helpers
  scuGates.h               — logic gates
  scuFullAdder.h           — 1-bit full adder
  scuMux.h                 — generic multiplexer
  scuDecoder.h             — generic decoder (+ enable variant)
  scuDLatch.h              — latches
  scuRegister.h            — registers
  moduleTest/              — simulation test benches
    common.mk              — shared Makefile rules
    gates/{and,or,xor,nand,nor,not,notXor}/
    fullAdder/
    muxn/
    decoder/{decoder,decoderEnable}/
    dLatch/{DLatch,DLatchEnable,DLatchReset,DLatchEnableReset,
            DLatchClocked,DLatchClockedEnable,DLatchClockedReset,
            DLatchClockedEnableReset}/
    register/{register,registerEnable,registerReset,registerEnableReset}/
docs/                      — user guides
CONTRIBUTING.md
CHANGELOG.md
LICENSE
```

## Running the test benches

Every directory under `scu/moduleTest/` holds a self-contained simulation. The
standard targets are:

```sh
make           # build the simulator executable
make run       # build (if needed) and execute
make clean     # remove the executable and generated .vcd traces
```

The register and latch examples produce `tf.vcd` trace files that can be
viewed with [GTKWave](https://gtkwave.sourceforge.net).

## Contributing

Pull requests, issues and suggestions are welcome. Please read
[`CONTRIBUTING.md`](CONTRIBUTING.md) first.

## License

Released under the MIT License — see [`LICENSE`](LICENSE).

## Author

Ronald Sulbarán &lt;ronalanto03@gmail.com&gt;
