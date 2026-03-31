# 013. stable-public-api

## Summary

This case evaluates whether a small semantic requirement change can be implemented without expanding or perturbing an already-established public API.

The repository contains a tiny library catalog module with a public header consumed by both the application and the evaluator. The new requirement is straightforward: archived books should no longer appear in title lookup results or in the catalog digest. The maintainable solution is to update internal behavior while keeping the public API stable.

## Maintainability Dimension

- **Primary:** Change Locality
- **Secondary:** API Stability, Responsibility Boundaries

## Why this case exists

AI coding agents often respond to even small behavior changes by widening public interfaces: adding booleans, mode flags, extra overloads, or new parameters that leak implementation decisions into external boundaries. This case tests whether the agent can recognize that the requirement is a semantic refinement, not a justification for API churn.

## Repository shape

```text
- cases/013.stable-public-api/
  - app/
    - main.cc
  - src/
  - TASK.md
  - CMakeLists.txt
- evaluator/013.stable-public-api/
  - checks/
  - data/
  - tests/
- docs/013.stable-public-api/
  - SPEC.md
```

## Existing code summary

The repository provides:

- a `Book` value type
- a `CatalogService` with two public methods
- a tiny demo application under `cases/013.stable-public-api/app/main.cc`
- evaluator tests and a structural check under `evaluator/013.stable-public-api/`

The current implementation still includes archived books in both search and digest output. The public API is intentionally small and already sufficient for the requested behavior change.

## Task for humans

Update the catalog behavior so that archived books are excluded from:

1. prefix-based title lookup
2. the catalog digest summary

The external interface should remain stable. The change should be implemented internally rather than by widening the public API with new control flags.

## Agent-facing task

The exact text in `TASK.md` is reproduced below.

---

Implement the requested catalog behavior change.

Requirements:
- archived books must not appear in title lookup results
- archived books must not appear in the catalog digest
- keep the existing behavior for non-archived books

Do not modify the evaluator.

---

## Good solution characteristics

A good solution typically:

- updates filtering logic inside the existing implementation
- preserves current public method names and signatures
- avoids introducing mode flags such as `include_archived`
- keeps the change local to catalog behavior

## Common bad solutions

Bad solutions include:

- adding extra boolean or mode parameters to public methods
- adding replacement public APIs when the old one is already sufficient
- pushing requirement-specific branching to external callsites
- modifying the app and tests indirectly by widening the boundary

## Oracle design

### Functional oracle

The evaluator checks that:

- archived titles are excluded from lookup results
- lookup still returns matching non-archived titles in sorted order
- digest output excludes archived books
- digest formatting remains correct for visible books

### Structural oracle

The evaluator checks that:

- `src/library_catalog.h` does not gain public control flags such as `include_archived`
- public method signatures remain stable
- the implementation does not solve the task by shifting policy into the app layer

## Failure diagnosis

Typical failures are:

- **API churn:** requirement solved by adding a public boolean flag
- **change spread:** multiple external callsites changed for an internal semantic update
- **boundary leakage:** archive policy moved outward instead of being handled inside the service

## Notes

This is a maintainability probe, not just a correctness task. The point is not only to make the output right, but to do so without unnecessary public-interface growth.
