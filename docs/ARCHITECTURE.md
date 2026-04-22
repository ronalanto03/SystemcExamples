# Architecture overview

The repository is split into two clearly separated concerns:

```
scu/                   library (header-only)
scu/moduleTest/        simulation test benches (binaries)
```

## Library layout

The library is a flat collection of C++ headers in `scu/`. Every public
symbol lives in the `scu::` namespace, opened and closed via the
`SCU_BEGIN_NAMESPACE` / `SCU_END_NAMESPACE` macros from `scuDefines.h`.

```
scu/scu.h           umbrella header (transitively includes everything)
scu/scuDefines.h    macros + minimal helpers
scu/scuGates.h      And, Or, Xor, Nand, Nor, NotXor, Not
scu/scuFullAdder.h  FullAdder, built on scuGates.h
scu/scuMux.h        Mux<N, NB, DataType>
scu/scuDecoder.h    Decoder, DecoderEnable
scu/scuDLatch.h     8 level-sensitive latch variants
scu/scuRegister.h   4 edge-sensitive register variants
```

Header dependencies form a directed acyclic graph:

```
scu.h ─┬─> scuDefines.h  <─┬─ scuGates.h ──> scuFullAdder.h
       │                   ├─ scuMux.h
       │                   ├─ scuDecoder.h
       │                   ├─ scuDLatch.h
       │                   └─ scuRegister.h
       └─> systemc.h
```

`scuDefines.h` requires `systemc.h` to have been included first; every
other header pulls `systemc.h` in directly.

## Module skeleton

All cells follow the same pattern:

```cpp
template <typename DataType /*, ... */>
class CellName : public sc_module {
public:
    sc_in<DataType>   x_in;
    sc_out<DataType>  z_out;

    SC_CTOR(CellName)
        : SCU_INIT_PORT_NAME(x_in),
          SCU_INIT_PORT_NAME(z_out)
    {
        // optional: validate template parameters
        if (/* invalid */) SCU_REPORT_FATAL("...");

        SC_METHOD(behaviour);
        sensitive << x_in /* << ... */;
    }

    virtual const char *kind() const { return "CellName"; }

private:
    void behaviour() {
        z_out.write(/* ... */);
    }
};
```

Three things make the resulting messages user-friendly:

1. **`SCU_INIT_PORT_NAME(p)`** initialises every port with its symbolic
   name (`p(#p)`), so SystemC kernel diagnostics print human-readable
   identifiers instead of `port_0`, `port_1`, ...
2. **`kind()`** is overridden so SystemC's introspection prints the cell
   type, not the generic `sc_module`.
3. **`SCU_REPORT_FATAL`** wraps `SC_REPORT_FATAL` and tags the offending
   `kind()` and `name()` automatically.

## Test bench layout

Every `scu/moduleTest/<group>/<example>/` directory contains:

```
sc_main.cpp (or *_main.cpp / sc_main.C)   wires DUT to a Test_Bench
test_bench.h                              random-vector driver + printer
Makefile                                  three-line; includes common.mk
```

The `Test_Bench` modules are **per-example** (different DUTs need different
ports), but they all share the same shape: a `SC_THREAD` triggered on
`clk_in.pos()` writes random vectors, waits a clock, then prints the
captured outputs.

## Build system

A single `scu/moduleTest/common.mk` carries every shared rule. Each
per-example `Makefile` only declares what is unique to that example:

```makefile
MODULE = and_test
SRCS   = sc_main.cpp
include ../../common.mk
```

The toplevel `Makefile` simply iterates over every directory containing a
`Makefile` and forwards `all` / `run-all` / `clean`.

`common.mk` honours environment variables for portability:

| Variable        | Default               | Purpose                                     |
|-----------------|-----------------------|---------------------------------------------|
| `SYSTEMC_HOME`  | `/usr/local/systemc`  | Root of the SystemC install.                |
| `SCU_HOME`      | auto-detected         | Repository root.                            |
| `CXX`           | `g++`                 | C++ compiler.                               |
| `CXXFLAGS`      | (empty)               | Extra compiler flags.                       |
| `LDFLAGS`       | (empty)               | Extra linker flags.                         |

The SystemC library directory is auto-detected from the layout of
`$SYSTEMC_HOME` (any of `lib`, `lib-linux`, `lib-linux64`, `lib-macos`).
