# ARK Documentation

Documentation for the ARK (Avionics Reference Kernel) rocketry flight-computer framework.


## Contents

| Document | Description |
|----------|-------------|
| [01-overview](01-overview.md) | What ARK is and high-level picture |
| [02-architecture](02-architecture.md) | Main loop, kernels, state machine, HAL |
| [03-build-and-run](03-build-and-run.md) | How to build and run (SIL, Pico, ESP32) |
| [04-user-guide](04-user-guide.md) | User folder: UserCode, UserConfig, UserTransitions |
| [05-use-case-flight](05-use-case-flight.md) | Full use case: one flight from power-on to landed |
| [06-states-reference](06-states-reference.md) | All flight states and typical transitions |


## Quick start

1. Read [01-overview](01-overview.md) to understand what ARK does.
2. Read [03-build-and-run](03-build-and-run.md) to build and run SIL (no hardware).
3. Read [04-user-guide](04-user-guide.md) and [05-use-case-flight](05-use-case-flight.md) to define your flight logic and state transitions.
