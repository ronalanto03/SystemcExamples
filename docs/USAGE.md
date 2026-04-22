# Using the `scu` cell library

This guide walks through every public module with a runnable snippet. All
examples assume:

```cpp
#include <systemc.h>
#include <scu.h>          // pulls in the whole library
using namespace scu;
```

and a build line of the form:

```sh
g++ -std=c++11 -I$SYSTEMC_HOME/include -Iscu \
    -L$SYSTEMC_HOME/lib-linux64 \
    my_design.cpp -lsystemc -lm -o my_design
```

## Conventions

Every module follows the same port-naming convention:

| Suffix     | Meaning                              |
|------------|--------------------------------------|
| `x_in`     | Primary data input (or input array)  |
| `y_in`     | Second data input (where applicable) |
| `c_in`     | Carry input                          |
| `en_in`    | Enable input                         |
| `reset_in` | Synchronous reset, active-high       |
| `clk_in`   | Clock                                |
| `ctrl_in`  | Control / select input               |
| `z_out`    | Primary data output                  |
| `c_out`    | Carry output                         |

Every module overrides `kind()` to return its class name, and registers each
port with `SCU_INIT_PORT_NAME` so SystemC kernel diagnostics point at the
correct symbolic name.

---

## Logic gates — `scuGates.h`

All multi-input gates are templated on the number of inputs `N` (must be
`>= 2`); `Not` is a unary gate.

```cpp
sc_signal<bool> a, b, c, y;

And<3> g("and3");      // 3-input AND
g.x_in[0](a);
g.x_in[1](b);
g.x_in[2](c);
g.z_out(y);
```

| Class     | Operation                  | Default `N` |
|-----------|----------------------------|-------------|
| `Or<N>`   | `y = OR(x[0..N-1])`        | none        |
| `And<N>`  | `y = AND(x[0..N-1])`       | 2           |
| `Xor<N>`  | `y = XOR(x[0..N-1])`       | 2           |
| `Nand<N>` | `y = NOT(AND(x[0..N-1]))`  | 2           |
| `Nor<N>`  | `y = NOT(OR(x[0..N-1]))`   | 2           |
| `NotXor<N>` | `y = NOT(XOR(x[0..N-1]))`| 2           |
| `Not`     | `y = NOT(x)`               | —           |

A fatal SystemC report is raised at elaboration if `N < 2`.

---

## Full adder — `scuFullAdder.h`

`FullAdder` is a 1-bit full adder built out of the gate primitives above.

```cpp
sc_signal<bool> a, b, cin, sum, cout;

FullAdder fa("fa");
fa.x_in(a);
fa.y_in(b);
fa.c_in(cin);
fa.z_out(sum);
fa.c_out(cout);
```

`sum  = a XOR b XOR cin`
`cout = (a AND (b OR cin)) OR (b AND cin)`

Wider adders can be built by chaining instances on `c_in`/`c_out`.

---

## Multiplexer — `scuMux.h`

```cpp
template < int N=2, int NB=1, typename DataType = sc_int<32> >
class Mux;
```

- `N`  — number of data inputs.
- `NB` — number of bits of the control port.
- `DataType` — the data type carried.

The constructor verifies `N` lies in the valid range
`(2^(NB-1), 2^NB]`, raising a fatal report otherwise.

```cpp
const int N  = 4;
const int NB = 2;
sc_signal< sc_int<32> > in[N];
sc_signal< sc_uint<NB> > sel;
sc_signal< sc_int<32> >  out;

Mux<N, NB, sc_int<32> > mux("mux");
for (int i = 0; i < N; ++i) mux.x_in[i](in[i]);
mux.ctrl_in(sel);
mux.z_out(out);
```

---

## Decoders — `scuDecoder.h`

```cpp
template < int N_IN=1, int N_OUT=2 > class Decoder;
template < int N_IN=1, int N_OUT=2 > class DecoderEnable; // adds en_in
```

`N_OUT` must satisfy `(2^(N_IN-1), 2^N_IN]` (one-hot on the binary input).

```cpp
const int N_IN = 3, N_OUT = 8;
sc_signal< sc_uint<N_IN> > sel;
sc_signal<bool>            out[N_OUT];

Decoder<N_IN, N_OUT> dec("dec");
dec.x_in(sel);
for (int i = 0; i < N_OUT; ++i) dec.z_out[i](out[i]);
```

`DecoderEnable` adds an `en_in`: when `en_in == 0` every output is forced
to `0`.

---

## Latches — `scuDLatch.h`

Eight level-sensitive flavours, all templated on `<DataType, bool zero=false>`.
When `zero=true` the cell behaves as a "zero latch" that constantly drives
zero on `z_out` (handy as a stand-in during early integration).

| Class                      | Inputs                                           | Behaviour                                                |
|----------------------------|--------------------------------------------------|----------------------------------------------------------|
| `DLatch`                   | `x_in`                                           | Transparent: `z_out` follows `x_in`.                     |
| `DLatchReset`              | `x_in`, `reset_in`                               | Transparent; `reset_in=1` clears the state.              |
| `DLatchEnable`             | `x_in`, `en_in`                                  | Transparent only when `en_in=1`.                         |
| `DLatchEnableReset`        | `x_in`, `en_in`, `reset_in`                      | Combination of the above.                                |
| `DLatchClocked`            | `x_in`, `clk_in`                                 | Transparent while `clk_in=1`.                            |
| `DLatchClockedReset`       | `x_in`, `clk_in`, `reset_in`                     | Clocked, with synchronous reset.                         |
| `DLatchClockedEnable`      | `x_in`, `clk_in`, `en_in`                        | Clocked, transparent when `clk_in & en_in`.              |
| `DLatchClockedEnableReset` | `x_in`, `clk_in`, `en_in`, `reset_in`            | All of the above combined.                               |

```cpp
sc_signal< sc_int<8> > d, q;
sc_signal<bool>        en;

DLatchEnable< sc_int<8> > latch("latch");
latch.x_in(d);
latch.en_in(en);
latch.z_out(q);
```

---

## Registers — `scuRegister.h`

Edge-sensitive flavours. They sample on the **rising edge** of `clk_in`
and drive `z_out` on the falling edge, modelling a master-slave flip-flop.
Same `<DataType, bool zero=false>` template parameters as the latches.

| Class                  | Inputs                                       |
|------------------------|----------------------------------------------|
| `Register`             | `clk_in`, `x_in`                             |
| `RegisterReset`        | `clk_in`, `x_in`, `reset_in`                 |
| `RegisterEnable`       | `clk_in`, `x_in`, `en_in`                    |
| `RegisterEnableReset`  | `clk_in`, `x_in`, `en_in`, `reset_in`        |

```cpp
sc_clock              clk("clk", 10, SC_NS);
sc_signal<sc_int<16>> d, q;
sc_signal<bool>       en, rst;

RegisterEnableReset< sc_int<16> > reg("reg");
reg.clk_in(clk);
reg.x_in(d);
reg.z_out(q);
reg.en_in(en);
reg.reset_in(rst);
```

---

## Composing modules

The `FullAdder` itself is a worked example of composition: it instantiates
six gates from `scuGates.h` and wires them with internal `sc_signal<bool>`
nets. See `scu/scuFullAdder.h` for a complete pattern you can copy when
building larger blocks.

---

## Tracing simulations

The bundled register and latch test benches dump `tf.vcd`. To produce one
in your own design, use the standard SystemC tracing API:

```cpp
sc_trace_file *tf = sc_create_vcd_trace_file("tf");
sc_trace(tf, my_signal, "my_signal");
// ...
sc_start();
sc_close_vcd_trace_file(tf);
```

Open it with GTKWave:

```sh
gtkwave tf.vcd
```

The `Makefile`s included with each example also expose a `make view` target
that does this for you.
