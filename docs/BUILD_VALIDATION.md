# Build validation and cleanup

Date: 2026-09-12. Default branch baseline: `8bbe9fa`. Environment: arm64 macOS, Apple Clang 16.0.0, system Make; CMake 3.31.10 installed in an isolated temporary Python environment for this check.

## Baseline and actual checks

| Check | Result |
|---|---|
| `make` | `libft.a` compiled successfully; SDL bootstrap failed: `Couldn't find autoconf, aborting`. No renderer executable produced. |
| `cmake -S . -B /private/tmp/raytracer-cmake-build` | Configuration identified compilers but generation failed because `UI_LIB` was `NOTFOUND`. |
| `cmake --build /private/tmp/raytracer-cmake-build` | Attempted available generated rules; failed compiling the first renderer source because bundled SDL headers include x86-only intrinsics on arm64. |
| `python3 -m json.tool scene.json` | Passed JSON syntax validation; does not validate custom-parser semantics. |
| Final `make` after stamp fix and cleanup | Same missing-autoconf failure; verified that no success stamp remains after failure. |
| Renderer GUI / OpenCL / screenshot | Not run: no successful renderer build. |

Additional source-inspection issues: CMake points at `libs/SDL2` although bundled source is under `libs/libui/SDL/SDL2`, omits the `libui` header directory, and expects prebuilt libraries. It lists OpenCL helpers that the Makefile does not build. Existing `incs/SDL2` configuration is platform-specific. No dependency upgrades or broad build-system rewrite were attempted.

## Small build-rule correction

In `libs/libui/Makefile`, move `touch sdl_config` after successful bootstrap/configure. Previously a failing first attempt left a success stamp that could skip necessary configuration on later attempts. The failure-path behavior was verified by running Make and checking stamp absence.

## Removed generated files

Removed stale outputs directly under `libs/libui`: `config.log`, `config.status`, `Makefile.rules`, `sdl2-config`, `sdl2-config.cmake`, `sdl2.pc`, and `SDL2.spec`. They embed an old machine's paths and are configuration outputs, not source dependencies of the active custom Makefile. Bundled SDL `configure.in` generates these names (including `Makefile.rules` and `AC_CONFIG_FILES` near its end); the active Make workflow configures inside `libs/libui/SDL/SDL2` instead.

No tracked renderer executable, object file, or generated static library was found at baseline. Build attempts generated local object files and `libft.a`, now ignored. Vendored SDL, headers, source dependencies, third-party notices, author files, and the existing BMP scene asset were retained. Some legacy generated dependency material remains where removal might affect restoration or attribution; cleanup does not claim a fully portable dependency tree.

## Restoration follow-ups

1. Provision Autoconf and the historical macOS development dependencies in an isolated compatible environment, then retry Make from a clean SDL configure state.
2. Resolve bundled SDL architecture configuration and compiler diagnostics before claiming Apple Silicon support.
3. Choose whether CMake should build dependencies or consume an explicitly installed set; align include/library paths before describing it as supported.
4. Validate `./rtv1 scene.json` and collect a real screenshot only after compilation succeeds.
5. Separately test scene validation, rectangular-buffer allocation, resource cleanup, and OpenCL integration. No benchmarks or runtime acceptance results are inferred from static code.
