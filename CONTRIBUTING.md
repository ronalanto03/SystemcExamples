# Contributing to SystemcExamples

Thanks for your interest in improving the `scu` cell library. This document
collects the conventions used in the project so that contributions can land
quickly and consistently.

## Reporting issues

Please open an issue with:

- A short description of what you expected versus what happened.
- Your operating system, compiler version, and SystemC version.
- A minimal reproducer (ideally a self-contained `sc_main`).

## Development setup

1. Install SystemC and expose its install prefix through `SYSTEMC_HOME`.
2. Clone the repository and build every example to verify your environment:

   ```sh
   export SYSTEMC_HOME=/opt/systemc
   make all
   make run-all
   ```

3. Create a topic branch for your change:

   ```sh
   git checkout -b feat/my-change
   ```

## Coding conventions

- The library is **header-only**. Keep public interfaces in the existing
  headers under `scu/`.
- All public symbols live in the `scu::` namespace.
- Follow the existing port-naming conventions:
  - `x_in`, `y_in`, `c_in`, `en_in`, `reset_in`, `clk_in` for inputs;
  - `z_out`, `c_out` for outputs.
- Every `sc_module` subclass should:
  - Initialise every port with `SCU_INIT_PORT_NAME(port)` in the constructor
    initialiser list, so that SystemC kernel errors point at the user-facing
    name.
  - Override `kind()` to return the class name.
  - Validate template parameters in the constructor with `SCU_REPORT_FATAL`.
- Use Doxygen comments (`/**` … `*/` and `///`) on classes, ports and methods.
- Indent with tabs to match the surrounding code.
- Prefer `not`, `and`, `or` over `!`, `&&`, `||` — this matches the existing
  style and reads better for hardware descriptions.

## Adding a new module

1. Create a new header in `scu/` (e.g. `scuMyCell.h`).
2. Wrap it with `SCU_BEGIN_NAMESPACE` / `SCU_END_NAMESPACE`.
3. Add `#include "scuMyCell.h"` to `scu/scu.h`.
4. Create a matching test bench under `scu/moduleTest/myCell/`:
   - `sc_main.cpp` — wires up the DUT, signals and test bench.
   - `test_bench.h` — drives the DUT and prints a truth table / trace.
   - `Makefile` — three lines:
     ```makefile
     MODULE = myCell
     SRCS   = sc_main.cpp
     include ../../common.mk
     ```
5. Document the new module in `README.md` and `docs/USAGE.md`.
6. Add an entry under `## [Unreleased]` in `CHANGELOG.md`.

## Commit messages

Write commit messages in the imperative mood, wrapped at ~72 columns:

```
Short summary (max 72 chars)

Optional body explaining the "why" in more detail. Reference issues
with `#123` when applicable.
```

## Pull requests

- Keep pull requests focused on a single concern.
- Run `make all` and `make run-all` before opening the PR.
- Update `CHANGELOG.md` and, where relevant, `docs/`.

## License

By contributing you agree that your contributions will be licensed under the
MIT License that covers this project.
