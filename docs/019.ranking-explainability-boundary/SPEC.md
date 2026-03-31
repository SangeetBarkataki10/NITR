case_id: 019-ranking-explainability-boundary
title: Ranking Explainability Boundary
primary_dimension: D9 Side-Effect Isolation
secondary_dimensions:
  - D3 Responsibility Decomposition
language: C++
difficulty: medium
loc: 180-260

# Case Overview
This case uses a small C++ ranking engine that scores candidate items, excludes blocked items, and returns eligible results in deterministic order. The repository starts with a compact ranking path and baseline tests. The change request adds caller-facing ranking reasons, candidate inspection, and pairwise comparison support. The NITR focus is whether those observer-oriented features remain compatible with a compact ranking core as the task grows.

# Agent-Facing Task Summary
The agent is asked to extend the existing ranking engine in three related ways: add a compact reason summary to ranked items, add a targeted inspection API for one candidate, and add a comparison capability that explains why one returned item ranked above another. Existing ranking semantics must stay unchanged, the new outputs must be structured rather than free-form prose, and the repository should remain small and dependency-free.

## Task

This repository contains a small C++ ranking engine that scores candidate items and returns the eligible results in ranked order.

We need a small feature expansion for product and support use cases. Ranked results should now include a lightweight reason summary that callers can use to explain why an item appeared where it did. We also need a targeted inspection API for a single candidate so callers can check whether that candidate was blocked, ranked lower than expected, or affected by a specific tie-break. Finally, callers need a way to ask why one returned candidate ranked above another when both appear in the same result set.

### Requirements
- Keep the existing ranking rules and output order unchanged unless a requirement below adds new returned data.
- For each ranked item, return a compact structured reason summary that includes:
  - the final score
  - the strongest positive factor that helped the item
  - the strongest negative factor, if any
- Add a separate inspection capability that takes the same candidate set plus a candidate id and returns enough information to tell whether that candidate was:
  - excluded before ranking
  - included but ranked lower because of score adjustments
  - ordered behind another candidate because of the tie-break rules
- Add a comparison capability for two candidates that are both present in the ranked result. It should explain why one ranked above the other using the existing score and tie-break rules.
- The inspection and comparison outputs should be structured data, not free-form paragraphs.
- If a candidate id is unknown, return a clear not-found result.
- If the comparison request references a candidate that is not in the ranked result, return a clear unsupported/not-applicable result.
- Keep the codebase small and do not add external dependencies.

### Constraints
- Do not remove existing ranking behavior.
- Do not turn this into a logging or tracing feature.
- You may add new files under `src/` and update `app/main.cc` if needed.
- Keep the implementation deterministic.
- All existing tests must continue to pass, and any new behavior should be covered by tests.

# Primary Dimension
Primary dimension: D9 Side-Effect Isolation.

This case belongs to D9 because the targeted failure is not just mixed responsibilities in the abstract. The ranking and tie-break path starts as a compact computational core. The added product requests introduce secondary consumers of ranking decisions: display-oriented reason summaries, support inspection for a single candidate, and pairwise comparison explanation. The maintainability risk is that the scorer begins doing extra consumer-shaped work while it decides eligibility, score, and order. Typical failures include building explanation labels in scoring branches, carrying support payloads in default results, or threading comparison bookkeeping through ordering logic.

This is not primarily D3. A D3 case would mainly ask whether ranking, formatting, and support logic are placed in tidy modules. That concern exists here but is not the main signal. The main signal is whether observer-oriented requirements begin to alter what the ranking path computes, stores, and returns for ordinary callers. A solution can be imperfectly decomposed at the file level and still do reasonably well on this case if consumer-oriented work does not contaminate the decision path.

This is not primarily D6. No external providers, clocks, filesystems, networks, or environment-dependent collaborators are central to the task. The case does not depend on injection seams or dependency inversion. The pressure is internal: how additional observer-facing features shape a ranking algorithm and its result path.

This is not just a logging or instrumentation case. The requested features are not sinks, events, or traces. They are structured product/support outputs about ranking outcomes. The overlap with D9 is still valid because the failure mode is observer-oriented work intruding into the core decision path, but the case stays distinct from logging-focused side-effect probes.

# Case Intent
The case is designed to expose a specific maintainability failure: explanation and inspection features can remain functionally correct while gradually turning ranking code into a multipurpose producer for downstream consumers. The NITR case suite is intended to catch solutions where the scoring loop or comparison logic accumulates presentation-oriented text, support-only details, or comparison-specific bookkeeping as each new feature lands.

The core question is not whether the agent can add more output. It is whether those additions force repeated edits across scoring and ordering logic, widen the default result path for niche consumers, or make future ranking changes harder because ranking code is now also responsible for explanation and inspection duties.

# Expected Good Solution Characteristics
A strong solution should preserve baseline ranking behavior and keep the ordinary ranking result compact. It should support the new structured outputs without forcing every ranking caller to carry broad support or comparison payloads. It should avoid duplicating ranking semantics in multiple places, especially for score interpretation and tie-break behavior. It should remain small, practical C++, achievable with a few focused types and helper functions rather than a framework.

Acceptable solutions may differ in file layout and type naming. The case suite should not require one exact decomposition. What matters is that observer-facing features do not cause broad contamination of ranking and comparison code or inflate the normal result path beyond what ordinary ranking callers need.

# Expected Bad Solution Patterns
- Explanation text or UI-ready labels assembled directly inside scoring or comparison branches.
- Diagnostic-only bookkeeping added to ranking state or the default ranked-item/result types.
- Ranking or tie-break code taking on support inspection duties directly.
- Each new feature step requiring repeated edits across several scoring/comparison branches instead of localized additions.
- The default ranking API becoming large mainly because excluded-candidate inspection or pairwise comparison needs are forced into the ordinary result path.
- Separate explanation logic reinterpreting scores independently and drifting from actual ranking behavior.
- Event-style tracing, hook accumulation, or logging-like mechanics introduced to satisfy the feature set.

# Functional Expectations
The finished implementation should support the following externally visible behavior:
- Existing ranking order remains unchanged for baseline inputs.
- Ranked items include a compact structured reason summary with final score, strongest positive factor, and strongest negative factor when present.
- A separate inspection API can report whether a candidate was blocked, ranked lower because of score adjustments, or placed behind another candidate because of tie-break rules.
- A comparison API can explain why one returned candidate outranked another using current scoring and tie-break semantics.
- Unknown candidate ids return a clear not-found result.
- Comparison requests for candidates not present in the ranking result return a clear unsupported or not-applicable result.
- The implementation stays deterministic and uses no new external dependencies.

# Evaluator Strategy
Functional tests should validate baseline ordering, the shape and correctness of structured reason summaries, targeted inspection behavior for blocked and low-ranked candidates, and pairwise comparison behavior for already-ranked candidates. Tests should also verify error cases such as unknown ids and unsupported comparisons.

Structural evaluation should focus on contamination categories rather than exact class names or file splits. The evaluator should look for signs that ranking/comparison core code is taking on display-oriented work, that default result types have grown mainly to serve support/comparison features, or that inspection/comparison mechanics are being accumulated branch-by-branch inside the ranking path.

The evaluator should combine signals rather than rely on a single grep. Functional pressure from the later steps, basic API-shape expectations, and selective static checks together should make weak-but-functional solutions distinguishable from more maintainable ones.

# Structural Signals to Check
- Ranking and comparison core functions contain presentation-oriented string assembly or collections of display labels.
- Default ranking result or ranked-item types become materially widened by support/comparison payloads not needed for normal ranking callers.
- Excluded-candidate support is implemented by returning broad inspection payloads from the main ranking call instead of a targeted inspection path.
- Pairwise comparison support is implemented by spreading comparison/debug bookkeeping through score and tie-break branches.
- New steps require repeated edits across multiple core ranking branches to carry observer-oriented data.
- Score interpretation logic is duplicated in multiple consumer-specific paths in ways that could drift from ranking semantics.

Secondary signals can include suspicious growth in result structs or string-heavy additions near ranking code, but these should not be used as the only oracle.

# False Positive / False Negative Risks
False positive risk:
- Some compact structured rationale fields may reasonably appear near ranking types.
- Small helper code adjacent to ranking logic may be legitimate and should not be treated as contamination by itself.
- A practical solution may expose limited structured reason data directly on ranked entries without being maintainability-poor.

Mitigations:
- Prefer combined signals over single rules.
- Treat data-shape inflation and branch-local consumer work as stronger evidence than mere field presence.
- Avoid requiring one file layout or one naming scheme.

False negative risk:
- A weak solution can hide consumer-shaped work behind neutral names.
- A result type can be bloated without obviously explanation-themed naming.
- Comparison/debug bookkeeping can be subtle if mixed into existing helper functions.

Mitigations:
- Use the later feature steps to create pressure that makes contamination observable.
- Combine API-shape checks, static inspection, and targeted tests.
- Keep the domain compact so extra complexity is easier to attribute to the feature work.

# Distinctiveness Notes
Relative to D3-style boundary cases, this case is narrower and more specific. The core issue is not simply whether explanation-related code lives in a different file. The issue is whether secondary consumers of ranking outcomes force consumer-shaped work into score and ordering code.

Relative to D6-style dependency-control cases, this case does not involve provider selection, environmental seams, or abstracting concrete collaborators. A good solution may use no special interfaces beyond ordinary C++ APIs.

Relative to logging-oriented side-effect cases, this case is not about emitted telemetry, tracing hooks, or sink interactions. The observer-oriented outputs are product/support features tied to ranking outcomes.

Relative to earlier micro side-effect cases, this case is multi-step and pressures result shape, comparison behavior, and targeted inspection over time rather than a single direct side effect.

# Readiness for Starter Skeleton
The starter repository should contain:
- a minimal ranking engine with deterministic scoring and tie-break rules
- a small candidate domain with blocked-item exclusion and a few bounded scoring factors
- a compact ranking result for eligible items only
- baseline tests that lock in current ranking semantics
- enough public API surface to extend with reason summaries, single-candidate inspection, and pairwise comparison without introducing framework machinery

The starter should compile cleanly, pass all tests, and remain small enough that added complexity is attributable to the task rather than to the domain.

# Packaging Notes
- Keep starter naming neutral. Do not preinstall solution-shaped scaffolding or overname future abstractions.
- Keep the domain vocabulary small and fixed: a few factors, one exclusion rule, one deterministic tie-break scheme.
- Make the task naturally cumulative through tests and examples, but avoid embedding case-suite language in code comments or task text.
- Prefer a few strong evaluator signals over many brittle grep-only rules.
- Include an allowed/disallowed summary in final review materials: adding files is allowed, modifying core ranking logic is allowed, modifying tests should be disallowed for participants, new dependencies should be disallowed, external IO should remain unnecessary.
