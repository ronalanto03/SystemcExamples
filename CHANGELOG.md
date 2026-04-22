# Changelog

All notable changes to this project are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [Unreleased]

### Added
- `scu/scu.h` umbrella header that includes the whole public API.
- Top-level `Makefile` with `all`, `run-all` and `clean` targets that recurse
  into every example.
- Shared `scu/moduleTest/common.mk` build fragment. Per-example Makefiles are
  now a few lines each.
- `docs/USAGE.md` with worked examples for every module.
- `docs/ARCHITECTURE.md` describing the layout of the library.
- `CONTRIBUTING.md`, `CHANGELOG.md`, `LICENSE` (MIT) and a proper `.gitignore`.

### Changed
- The build system is now portable: it honours `SYSTEMC_HOME`, `CXX` and
  `CXXFLAGS`, and auto-detects the correct SystemC library directory
  (`lib`, `lib-linux`, `lib-linux64`, `lib-macos`). The previous hard-coded
  `/home/ronalanto03/Desktop/scu` and `g++-4.4` references are gone.
- README rewritten with requirements, build instructions, a minimal usage
  example and a map of the repository.

### Fixed
- `scu/moduleTest/register/registerEnable/sc_main.cpp` no longer includes a
  non-existent header (`RegisterEnable.h`) and uses the correct port names
  (`x_in` / `z_out`) and `scu::` namespace.
- Corrected `@file` tags in `scuDefines.h`, `scuDecoder.h`, `scuRegister.h`
  that previously said "dLatch.h".
- Fixed the `@class Or` Doxygen tag on the `Nor` class in `scuGates.h`.
- Minor spelling fixes across the header documentation
  ("Usefull", "sincronization", "informaion", "de DataType", "construtor",
  "diferent", "doesnt").

## [0.1.0] — 2012-12

Initial public release of the `scu` cell library: gates, full adder,
multiplexer, decoder, latches and registers, with SystemC test benches.
