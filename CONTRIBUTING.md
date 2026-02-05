# Contributing to ARK

Contributions are welcome. To keep the project consistent and safe for rocketry use:

1. **Code style** — Match existing style: no comments in code, same naming and layout as in `ARK/` and `User/`.
2. **No comments** — Do not add comments in source files unless strictly necessary for safety.
3. **Testing** — Prefer SIL build and run before submitting; Pico/ESP32 testing when you change HAL or arch-specific code.
4. **Safety** — Changes to FDIR, state machine, or recovery logic should be conservative and documented in commit messages or PRs.
5. **Pull requests** — Use a short branch, one logical change per PR; reference any issue if applicable.

By contributing you agree that your contributions are licensed under the project’s MIT License.
