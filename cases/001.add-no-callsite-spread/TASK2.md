## Task

Extend `nitr::case001::add` so the same API also works for floating-point callers.

### Requirements
- Keep existing `int` behavior working.
- Support `float` and `double` addition so calls such as `add(3.5, 4.5)` and `add(100000000.0, 1.0)` work correctly.

### Constraints
- Do not modify `app/main.cc`.
- You may modify files under `src/` and add new files under `src/` if needed.
- Do not modify evaluator files.
