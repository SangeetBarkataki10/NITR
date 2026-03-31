# SPEC

## Metadata
```yaml
case_id: 015-pipeline-provider-decoupling
title: Policy Enrichment in Event Pipeline
primary_dimension: dependency_control
secondary_dimensions:
  - extension_structure
language: C++
difficulty: medium
loc: ~220
```

## Problem Context
A service runs a compact event pipeline to normalize and score incoming events before emitting report lines. Product now needs each emitted record enriched with policy metadata derived from event source.

Policy lookup must support multiple backends because local runs and production runs use different policy data.

## Agent-Facing Contract (from TASK.md)
## Task

TASK.md is the normative source for the agent-facing contract text.

Add policy enrichment to the existing event pipeline outputs.

Requirements:
- Add `policy_tier` and `retention_days` to enriched output records.
- Policy lookup must support both `static` and `file` policy sources selected by configuration.
- Mode selection must be configuration-driven without changing baseline (non-policy) pipeline behavior.
- For unknown sources, apply fallback policy:
  - `policy_tier=standard`
  - `retention_days=30`
- Keep existing build and tests passing, and add/update code needed for this feature.

Constraints:
- Do not add external libraries beyond what is already used in this repository.
- Keep changes small and focused; avoid unrelated refactors.

## Hidden Evaluator Intent (author-only, never copy into TASK.md)
### Evaluation Criteria

#### Functional
- Existing behavior tests continue to pass.
- Enrichment values are correct for known and unknown sources.
- Static/file modes are both tested and produce distinguishable results based on non-equivalent fixtures.

Fixture roles:
- `expected_output_baseline.txt`: baseline regression for non-policy behavior.
- `expected_output_static.txt`: expected output for static mode.
- `expected_output_file.txt`: expected output for file mode.

#### Structural
- No concrete policy provider dependency edge from `src/pipeline/*`.
- `PipelineRunner` depends on `PolicyProvider` contract surface only.
- `src/pipeline/*` must not create/select providers directly or indirectly (including factory/helper/builder APIs).
- Concrete provider mode branching appears in exactly one allowed composition boundary.
- Execution-path proof: mode-switching tests must execute that same boundary call path (`build_pipeline(...)` directly or via `app/main.cc` harness), not bypass it via direct `PipelineRunner` construction.

#### Maintainability Scoring Precedence
- D6 dependency-boundary checks are primary.
- Any D6 structural violation fails maintainability regardless of functional pass status.

### Oracle Notes
Checks are intentionally split by concern (dependency edge, contract surface, no-core-creation, single wiring boundary) to reduce overlap and improve diagnosis precision.
