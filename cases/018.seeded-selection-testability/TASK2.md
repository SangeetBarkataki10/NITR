## Task

Make replay behavior deterministic under the fixed `SamplerV1` contract.

### Requirements
- Keep the selection policy behavior working.
- Ensure replay behavior follows the fixed `SamplerV1` randomization contract documented in code comments and SPEC.
- Ensure tie and fallback behavior are directly testable without probabilistic retries.
- Keep policy behavior consistent across default and replay code paths.

### Constraints
- Do not add time/sleep/timeout-based logic.
- Do not add test-only branches or debug-only force-pick hooks.
- Do not thread seed/control parameters through unrelated public APIs.
- Keep implementation in C++ and preserve a small, maintainable selector API.
