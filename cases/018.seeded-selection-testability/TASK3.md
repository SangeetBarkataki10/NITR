## Task

Finish deterministic replay so multi-selection behavior is stable and testable.

### Requirements
- Keep the selection policy and replay determinism working.
- Make multi-selection deterministic under replay seed, including tie handling.
- Selection is without replacement, and output order is draw order.
- Ensure `k > pool_size` returns all available items without duplicates.
- Keep policy behavior consistent across default and replay code paths.

### Constraints
- Do not add time/sleep/timeout-based logic.
- Do not add test-only branches or debug-only force-pick hooks.
- Do not thread seed/control parameters through unrelated public APIs.
- Keep implementation in C++ and preserve a small, maintainable selector API.
