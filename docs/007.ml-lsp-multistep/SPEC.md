# Case 007 Task

## 1. Case Metadata

```yaml
case_id: 007-ml-lsp-feature-transform
project: Needle in the Repo
primary_dimension: interface_and_substitutability_discipline
secondary_dimensions:
  - contract_preservation
  - caller_independence
  - composition_safety
probe_granularity: multi-step
domain: ml
language: C++
difficulty: medium
loc: ~260
```

## 2. Problem Context

This repository contains a tiny feature-transform pipeline.
A `FeatureTransform` is an abstract component that maps one feature vector to another.
Callers are supposed to depend only on the shared abstraction rather than on transform-specific behavior.

The current codebase includes:
- `IdentityTransform`,
- `L2NormalizeTransform`, and
- a small `FeaturePipeline` that applies one transform.

The current family is not fully substitutable:
`L2NormalizeTransform` is unsafe on all-zero input and the system does not yet exercise the abstraction through multiple callers or composition.
This case upgrades the repository from a single-call-site transform example into a small transform subsystem that must preserve one shared behavioral contract across multiple usage paths.

## 3. Task Structure

This is a **three-step** maintenance task.
The steps are intentionally related: a shallow fix in Step 1 should be exposed by Steps 2 and 3.

### Step 1 — Add `ClampTransform` and repair the shared contract
Add a new transform named `ClampTransform` whose behavior is elementwise clamping to the closed interval `[-1.0, 1.0]`.
At the same time, make the transform family satisfy a common contract.

Shared contract for **all** `FeatureTransform` implementations:
- output length equals input length,
- input values are not modified,
- empty input returns empty output,
- valid inputs do not throw,
- output contains no `NaN` or `Inf`.

Additional contract for `L2NormalizeTransform`:
- for non-zero input, the output must have unit L2 norm,
- for all-zero input, the output must be an all-zero vector.

### Step 2 — Add a second caller through batch execution
Add a batch execution path that applies **any** `FeatureTransform` to a batch of feature vectors.
The batch path must depend only on the shared abstraction and must not branch on concrete transform types.

### Step 3 — Add transform chaining
Add a compositional path that allows multiple transforms to be applied sequentially through the same abstraction.
The chain itself should behave like a `FeatureTransform` so that callers can continue to depend on the shared contract.
The chain must work correctly with `ClampTransform` and the existing transforms.

## 4. Agent-Facing Task (embedded TASK.md)

The following section is the exact content of `TASK.md`.

---

## Task Description

Extend the feature-transform subsystem in three steps:

1. Add `ClampTransform`, which clamps each value to `[-1.0, 1.0]`, and make the transform family safe on edge cases.
2. Add a batch execution path that applies any `FeatureTransform` to a batch of feature vectors.
3. Add transform chaining so multiple transforms can be applied sequentially through the same abstraction.

Requirements:
- `FeatureTransform` remains the shared abstraction.
- Output length must equal input length.
- Input values must not be modified.
- Empty input must return empty output.
- Valid inputs must not throw.
- Outputs must not contain `NaN` or `Inf`.
- `L2NormalizeTransform` must return a unit-norm vector for non-zero input and an all-zero vector for all-zero input.

The following files must not be modified:
- `src/feature_transform.h`
- `src/feature_pipeline.h`
- `src/feature_pipeline.cc`

You may:
- add new files,
- modify existing transform implementations,
- update factory logic,
- implement the new batch and chaining paths.

You must not:
- modify evaluator files,
- change the abstract interface signature,
- bypass the abstraction by specializing callers on concrete transform types.

---

## 5. Expected Design Direction (Non-prescriptive)

Reasonable solutions should keep transform-specific behavior inside transform implementations and keep higher-level callers generic.
The new batch path and chain path should operate on `FeatureTransform` rather than on concrete subclasses.
Good solutions preserve one behavioral contract across:
- single execution,
- batch execution, and
- transform composition.

## 6. Evaluation Criteria

### 6.1 Functional
- `ClampTransform` clamps elementwise to `[-1.0, 1.0]`.
- `L2NormalizeTransform` safely handles zero input.
- The batch path works for existing and new transforms.
- The chain path applies transforms in order.
- All public and hidden tests pass.

### 6.2 Structural
- `src/feature_transform.h` remains unchanged.
- `src/feature_pipeline.h` remains unchanged.
- `src/feature_pipeline.cc` remains unchanged.
- The batch path and chain path continue to use `FeatureTransform` as the shared abstraction.
- No caller may branch on concrete transform types.

### 6.3 Maintainability
- Substitutability holds across multiple callers, not just one pipeline path.
- Composition should not introduce concrete-type coupling.
- Edge-case handling should stay inside component implementations rather than being pushed onto callers.

## 7. Common Failure Modes (Non-scoring)

Common incorrect solutions include:
- fixing zero-vector behavior by adding special logic in callers,
- implementing batch execution with concrete-type branching,
- making the chain depend on concrete subclass checks,
- letting `ClampTransform` violate the shared size or finiteness contract,
- introducing transform-specific special cases into generic utilities.

## 8. Maintainability Mapping

Primary dimension:
- Interface and Substitutability Discipline

Measured capabilities:
- preserving one behavioral contract across multiple implementations,
- keeping callers generic under extension,
- supporting composition without leaking concrete-type knowledge.
