---
case_id: 018-seeded-selection-testability
title: Seeded Selection for Reproducible Testing
primary_dimension: testability
secondary_dimensions:
  - change_locality
  - responsibility_separation
language: C++
difficulty: medium
loc: ~220
---

## Problem Context
A recommendation service selects a small list of suggested item IDs from pre-scored candidates.
Production behavior should stay random enough for variety, but incident replay and tests require deterministic outputs from the same input and seed.
The codebase currently mixes policy rules and randomization in one place, making exact validation hard.

## Given Code
Starter code provides:
- candidate model (`id`, `score`, `eligible`, `is_fallback`)
- default selector entrypoint (`SelectRecommendations`)
- replay entrypoint (`SelectRecommendationsReplay`) with incomplete behavior
- sampler seam (`IndexSampler`) and a fixed deterministic sampler (`SamplerV1`)

Initial implementation compiles but does not fully satisfy replay contract and policy consistency requirements.

## Agent-Facing Contract (This Text Must Match TASK.md)

### Task

The recommendation selector currently returns random results but is hard to replay in tests and incident debugging.
You need to add deterministic replay support while keeping the existing default production entrypoint intact.

The selector must follow these product rules:
- Use primary candidates (`eligible == true && is_fallback == false`) when available.
- Use fallback candidates (`eligible == true && is_fallback == true`) only when no primary candidate is eligible.
- If no eligible candidate exists at all, return an empty result.
- Non-random ordering priority is `score DESC`, then `id ASC`.
- Selection is without replacement, and output order is draw order.

### Requirements
- Keep `SelectRecommendations(candidates, k)` available for default production usage.
- Add/complete deterministic replay behavior in `SelectRecommendationsReplay(candidates, k, seed)`.
- Ensure replay behavior follows the fixed `SamplerV1` randomization contract (documented in code comments and SPEC).
- Make multi-selection deterministic under replay seed, including tie handling.
- Ensure `k > pool_size` returns all available items without duplicates.
- Ensure tie/fallback/empty behavior is directly testable without probabilistic retries.
- Keep policy behavior consistent across default and replay code paths.

### Constraints
- Do not add time/sleep/timeout-based logic.
- Do not add test-only branches or debug-only force-pick hooks.
- Do not thread seed/control parameters through unrelated public APIs.
- Keep implementation in C++ and preserve a small, maintainable selector API.

## Expected Design Direction (Human-Facing)
A good solution should keep one policy pipeline and inject randomness through a narrow seam.
The recommended shape is:
- shared selection policy (`pool selection`, `ordering key`, `tie handling`, `fallback rules`)
- sampler seam for index draws (`IndexSampler`)
- default path using non-fixed random sampler
- replay path using `SamplerV1` with explicit seed

The case is not intended to enforce a single class layout.

## Fixed Randomization Contract (SamplerV1)
Exact seeded replay outputs are intentionally oracle-checked.
To keep this fair, deterministic randomization is fully specified:

- State type: `uint64_t`
- Seed init: `state = seed ^ 0x9E3779B97F4A7C15ULL`
- Step: `state = state * 6364136223846793005ULL + 1442695040888963407ULL`
- Draw: for `n > 0`, `NextIndex(n)` returns `((state >> 32) % n)` after one step
- Tie-group shuffle uses Fisher-Yates driven only by `NextIndex`
- Replay behavior must not rely on `std::shuffle` or `uniform_int_distribution`

## Hidden Evaluator Intent
Primary maintainability probe:
- D7 Testability and Determinism under randomness-driven nondeterminism

The evaluator rewards:
- deterministic replay correctness under fixed contract
- direct branch testing (tie/fallback/empty) without retries
- localized randomness seam
- policy consistency between default and replay behavior

The evaluator penalizes:
- duplicated policy implementations that drift
- global mutable RNG patterns
- test-only branches or forced hooks
- seed pollution across unrelated APIs
- probabilistic/flaky testing strategies

## Evaluation Criteria
### Functional
- Correct primary/fallback/empty behavior
- Correct multi-select without replacement
- Correct draw-order outputs
- Replay exactness for fixed seeds and fixtures

### Structural
- `SelectRecommendations(candidates, k)` remains stable
- non-selector public API remains seed/control-free
- replay path aligns with `SamplerV1` contract

### Maintainability
- one policy path for default and replay modes
- randomness control isolated at selector boundary
- deterministic tests are low-friction and exact

## Oracle Signals
- evaluator unit tests for exact replay vectors
- policy invariant tests on default path
- policy-equivalence probe via controlled sampler seam
- grep/script checks for obvious anti-patterns

## Common Failure Modes (Non-Scoring)
- separate seeded-only algorithm with different policy
- hidden global RNG state
- `if (test_mode)`-style branches
- fallback used even when primary pool exists
- output sorted post draw (breaking draw order)

## Distinctness and Mapping
Primary Dimension:
- D7 Testability and Determinism

Measured Capability:
- deterministic replay from controlled randomness
- branch-focused deterministic testing under fixed RNG contract

Secondary Dimensions:
- D1 Change Locality (non-scoring)
- D3 Responsibility Decomposition (non-scoring)

Distinct from case 009:
- no clock/sleep/timeout/expiry behavior
- nondeterminism source is RNG only

Distinct from D9:
- no side-effect isolation objective

## Allowed & Disallowed Summary
| Action | Allowed |
|---|---|
| Add new files | Yes |
| Modify existing core logic | Yes |
| Modify existing tests | No (evaluator-owned) |
| Add new dependencies | No |
| Modify public headers | Selector boundary only |
| Use global mutable state | No |
| Introduce new external IO | No |
