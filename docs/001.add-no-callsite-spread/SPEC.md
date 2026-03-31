```yaml
case_id:        core-maint-add-multi_type
domain:         core_utils
focus:          maintainability
difficulty:     easy
language:       C++
```
```

---

## 2. Problem Context

A small utility function `add` is widely used across a codebase.  
As requirements evolve (supporting new numeric types), maintainable code should allow extension without forcing edits to existing call sites.  
This case targets “change amplification”: a small requirement change should not cascade into widespread edits.

---

## 3. Given Code

Initial code state provided:

- `app/main.cc` calls `solid::add` with several numeric inputs and prints results.
- `src/add.h` / `src/add.cc` are provided but initially incomplete.
- The project initially may fail to link until required functions are implemented.

---

## 4. Task Description

Implement `add` to satisfy milestone requirements while respecting file-level constraints.

### Functional requirements
- **Milestone 1:** Implement `add` for int `type` so the program outputs `7` for `add(3,4)`.
- **Milestone 2:** Add `float` support for `add` so unit tests such as `add(3.5, 4.5) == 8.0` pass.
- **Milestone 3:** Add `double` support for `add` so unit tests such as `add(100000000.0, 1.0) == 100000001.0` pass.
- **Milestone 4:** Add `long long` support for `add` so unit tests such as `add(100000000, 100000000) == 200000000` pass.

### Maintainability constraint (structural)

- `app/main.cc` must NOT be modified.
- The implementation should avoid duplicated per-type logic and keep the core addition behavior centralized (the evaluator performs a structural check for this).

### Allowed actions

- Modify `src/` files (including changing public APIs in `src/add.h`), add new `.h/.cc` files under `src/`.
- Refactor library internals freely as long as `app/main.cc` remains unchanged and all tests pass.

### Disallowed actions

- Modifying `app/main.cc`.
- Modifying evaluator code or tests.

---

## 5. Evaluation

The evaluator checks:

1) Functional correctness for the current milestone (unit tests).
2) Structural constraints:
   - `app/main.cc` unchanged.
   - No macro-based rewriting of `add`.
   - The library implementation follows a maintainable structure that scales across the required numeric types.

A solution that passes functional tests but violates structural constraints fails.