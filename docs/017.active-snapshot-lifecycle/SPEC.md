# SPEC: 017-active-snapshot-lifecycle

```yaml
case_id: 017-active-snapshot-lifecycle
title: Active Snapshot Lifecycle
primary_dimension: state_lifecycle
secondary_dimensions:
  - change_locality
  - testability
language: C++
difficulty: medium
loc: 200-300
```

## Problem Context
A small in-memory service answers key lookups from a currently active snapshot. Product requirements now need explicit lifecycle control over which snapshot is active at runtime. The system must support registering snapshots, switching active snapshot, and clearing active state. Query behavior must remain deterministic across lifecycle transitions. The case is intentionally compact and excludes infra concerns.

## Given Code
Starter code provides:
- snapshot domain data (`version` + key-value payload)
- a registry/store that can hold snapshots and expose one active snapshot for querying
- a query service used by `app/main.cc`
- compiling baseline with a manual bind-to-active query flow

The baseline has an active-snapshot concept but lifecycle operations are incomplete or under-specified, creating room for inconsistent replacement/reset behavior if extended poorly.

## Task

Extend the snapshot query subsystem so it supports explicit snapshot lifecycle operations while keeping existing query behavior intact where not changed below.

### Requirements
- Add an in-memory snapshot registration API that accepts:
  - snapshot version id
  - key-value payload
- Duplicate snapshot registration for an existing version must be rejected.
- Add an activation API that sets a registered snapshot as the current active snapshot.
- Activating an unknown snapshot version must fail and keep the previously active snapshot unchanged.
- Support replacing the current active snapshot by activating a different registered snapshot.
- Add a reset API that clears the current active snapshot.
- Reset when already empty must be a no-op.
- Query behavior must follow this contract exactly:
  - active snapshot exists and key exists: return `kFound` with value
  - active snapshot exists and key missing: return `kNotFound` with no value
  - no active snapshot: return `kNoActiveSnapshot` with no value
- After replacement, queries must read only from the newly active snapshot.
- After reset, queries must not return stale data from any previously active snapshot.
- Repeated lifecycle transitions must work correctly, including:
  - replace-after-replace sequence (`v1 -> v2 -> v3`)
  - reset-then-reactivate sequence (`vX -> reset -> vY`)

### Constraints
- Keep the system in-memory and deterministic.
- Do not introduce concurrency, threads, persistence, networking, or filesystem-based loading.
- Keep `app/main.cc` as a small demo entry point.
- You may add files under `src/`.
- Do not remove existing behavior unless required by the lifecycle contract above.

## Expected Design Direction (Human-Facing)
Acceptable solution directions:
- Keep lifecycle mutation responsibility concentrated in one core owner component.
- Keep query path read-focused and dependent on current active snapshot resolution.
- Keep public API additions narrow and directly tied to lifecycle requirements.

Undesirable directions:
- proliferating active-state mutation across unrelated modules
- storing parallel writable active-version trackers in multiple classes
- shifting lifecycle logic into demo wiring code

## Evaluation Criteria
### Functional
- Existing tests pass.
- New lifecycle tests pass for activate/replace/reset/no-active semantics.
- Replacement and reset correctness hold across repeated transitions.

### Structural
- No global mutable active snapshot state.
- No duplicate writable active-state trackers across multiple modules.
- Query layer does not own mutable snapshot payload cache.
- Lifecycle mutation semantics remain in core `src` ownership path, not in `app/main.cc`.

### Maintainability
- Mutable state ownership remains clear and localized.
- Lifecycle transitions are explicit and consistent.
- API surface expansion remains limited to necessary lifecycle operations.
- Behavior remains deterministic and testable.

## Oracle Signals
Planned evaluator signals:
1. Functional sequence tests for:
   - baseline active query
   - `v1 -> v2 -> v3` replacement sequence
   - reset behavior (`kNoActiveSnapshot`)
   - `reset -> reactivate` sequence
   - inactive snapshot isolation after replacement
2. Structural check: reject namespace/file-scope mutable active-state variables in `src/*.cc` (except local static const/constexpr).
3. Structural check: detect multiple writable active-tracker fields across core classes.
4. Structural check: reject mutable snapshot-cache ownership in query service.
5. Structural check: reject lifecycle state-mutation implementation inside `app/main.cc`.

Signals are designed for objective grading with low false positives.

## Failure Modes (Non-scoring)
Common weak outcomes:
- duplicated active-version/source-of-truth fields
- stale snapshot aliases surviving replacement
- reset implemented as partial flags without clearing authoritative active state
- lifecycle mutation logic spread across query and demo layers

## Maintainability Mapping
Primary Dimension:
- D8 state ownership and lifecycle

Measured Capability:
- localizing mutable active-state ownership
- keeping replace/reset invalidation semantics coherent over time

Secondary Dimensions:
- D1 change locality (supporting)
- D7 testability and determinism (supporting)

## Allowed & Disallowed Summary
| Action | Allowed |
|---|---|
| Add new files under `src/` | Yes |
| Modify existing core logic | Yes |
| Modify existing tests | Yes, only to add lifecycle coverage |
| Add new dependencies | No (unless trivial stdlib-only use) |
| Modify public headers | Yes, if required by lifecycle API |
| Use global mutable state | No |
| Introduce new external IO | No |
