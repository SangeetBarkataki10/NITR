---
case_id: 020-handover-packet-ownership-boundary
title: Handover Packet Ownership Boundary
primary_dimension: responsibility_separation
secondary_dimensions:
  - side_effect_containment
  - state_lifecycle
language: C++
difficulty: medium
loc: 180-260
---

## Case Summary

This is a micro C++ maintainability case about a warehouse handover tool that must both preview and save the same handover packet. The core design pressure is whether packet assembly remains domain-owned or is absorbed into preview/save-side code.

The case is intentionally narrow. It is not about exporter extensibility, generic formatting architecture, or broad lifecycle management. It is about one boundary: building a stable handover packet from tracker state versus using that already-built packet in consumer flows.

## Problem Context

The system tracks totes scanned during a warehouse shift.
At handover time, supervisors need to inspect the handover packet in the terminal before saving it for the next shift.
The saved packet and the preview must describe the same handover state.
One tote may still be in progress when the packet is requested.

## Given Code

The starter repo should compile and pass its initial tests.

The initial code should include:
- a mutable `ShiftTracker`-like domain object under `cases/020.handover-packet-ownership-boundary/src/`
- a packet/result data shape under `cases/020.handover-packet-ownership-boundary/src/`
- an existing save path that currently reads tracker state directly and assembles packet content inline
- a preview path that is missing or stubbed
- a small CLI entrypoint under `cases/020.handover-packet-ownership-boundary/app/main.cc`

The initial design should make the wrong move attractive: extending the existing save path or sharing its logic with preview in output-adjacent code.

## Task

The warehouse handover tool can currently save a handover packet at the end of a shift, but the save path builds the packet directly from the live tracker state. We now need a terminal preview so supervisors can inspect the packet before saving it.

Update the handover flow so preview and save use the same packet content. If the shift still has one in-progress tote, that tote must appear in the packet. Packet row numbers and the packet summary must also match between preview and save. Previewing the packet must not change what later gets saved, and repeated preview/save calls should stay stable.

### Requirements
- Add support for previewing the handover packet before saving it.
- Keep preview and save consistent for the same tracker state.
- Include the current in-progress tote in the packet when present.
- Preserve correct packet row numbers and packet summary in both preview and save.
- Previewing must not change what a later save produces.
- Keep existing behavior unchanged unless required above.

### Constraints
- Do not modify evaluator files.
- Do not add external dependencies.
- Keep the change small and local to this case.

## Primary and Secondary Dimensions

Primary Dimension:
- D3 Responsibility Decomposition

Measured Capability:
- keep packet assembly on the domain side
- keep preview/save code limited to consuming assembled packet data

Secondary Dimensions:
- D9 Side-Effect Isolation
- D8 State Ownership and Lifecycle

## Why This Case Is Primarily D3

This case measures a narrow but real D3 boundary:
- domain-side logic assembles a stable handover packet from mutable tracker state
- consumer-side logic previews, renders, or saves that packet

The scored question is whether preview/save-side code owns packet assembly. That is responsibility decomposition: business completion logic must stay in the domain-side assembly boundary rather than leak into consumer code.

This is not primarily D4 because the task is not about adding exporters or extension points. Two consumers exist only to expose whether shared logic is owned by the wrong layer.

This is not primarily D8 because the in-progress tote is only a small source of assembly pressure. The case should not revolve around broader state transitions, resets, or ownership transfer.

This is not primarily D9 because thin IO wrappers are not enough. Preview/save code can be read-only and still be structurally wrong if it assembles packet content from tracker state.

## Distinctness From Nearby Cases

### Distinct From Case 014

Case `014 report-export-ocp` is a D4 extension-structure case about adding another output representation cleanly.

Case 020 is different in both task shape and scoring:
- the visible story is one handover packet used in two contexts, not exporter growth
- there is no format registry, output dispatch, or pluggable exporter pressure
- the main failure is not patching a central switch
- the main failure is letting preview/save-side code own packet assembly

A solution can look extension-friendly and still fail case 020 if it centralizes packet assembly in writer-side or preview-side helpers.

### Distinct From D8 Cases

This is not a lifecycle-control probe. “Include the in-progress tote” exists only to ensure packet assembly performs real work. The case suite should not reward or punish broader state-machine design.

### Distinct From D9 Cases

This is not a logging/IO isolation case. Preview and save are present because they reveal ownership mistakes, not because side effects themselves are the main stressor.

## Exact Task Intent Behind TASK.md

`TASK.md` should feel like a small product request:
- supervisors need preview before save
- preview and save must agree
- preview must not perturb the later save result

The hidden intent is that this pressure should make it tempting to:
- copy packet assembly into preview
- share a helper in the writer/output layer
- keep missing packet-field computation near rendering or save code

The case should reward moving packet assembly behind a domain-side boundary instead.

## Hidden Evaluator Intent

The evaluator should distinguish between:

- acceptable ownership:
  - tracker state is turned into packet/result data on the domain side
  - preview/save consume packet/result data

- unacceptable ownership:
  - preview/save code computes packet rows, row numbers, or summary from tracker state
  - an output-layer helper assembles packet data once and both consumers call it
  - rendering/writing code fills in missing packet fields from raw tracker state

The key hidden oracle question is:

**Does any consumer-side code turn tracker state into packet content?**

If yes, the solution should score poorly even when behavior is functionally correct.

## Expected Good Solution Shape

Acceptable solutions may vary, but they should share these properties:
- packet assembly happens before preview/save formatting or writing
- preview/save operate on packet/result data, not raw tracker state
- assembly logic for the in-progress tote, row numbering, and summary lives behind a domain-side API or module
- rendering and writing helpers may be shared, provided they only consume packet/result data

Examples of acceptable shapes:
- `ShiftTracker` exposes a method that returns an assembled packet/result object
- a new domain-side assembler under `cases/020.handover-packet-ownership-boundary/src/` takes tracker state and returns packet/result data
- a tracker-adjacent snapshot/materializer API produces a packet view used by preview/save

No exact class name or file split is required.

## Expected Bad Solution Shapes

The following are structurally wrong for this case:
- preview reads tracker state and assembles packet rows
- save reads tracker state and assembles packet rows
- preview or save computes row numbers or summary from tracker data
- formatting code derives missing packet fields from live tracker state
- preview and save duplicate their own assembly logic
- a shared helper under preview/writer/app code accepts tracker state and assembles the packet for both consumers

The known false positive to guard against is:
- an agent creates a shared helper in the output layer
- both preview and save call it
- behavior is correct
- ownership is still wrong because packet assembly remains consumer-side

## Oracle Strategy

The oracle should combine behavioral checks with static/structural checks. Behavioral checks alone are insufficient because the known false-positive shared-helper solution can still behave correctly.

### Core Scoring Rule

Consumer-side code may:
- consume packet data
- format packet data
- write packet data

Consumer-side code may not:
- turn tracker state into packet data

### Behavioral Signals

Tests should verify:
- preview includes the in-progress tote when present
- save includes the same rows and summary for the same tracker state
- preview-then-save and save-then-preview are equivalent
- repeated preview/save calls are stable

These tests catch mutation and order-dependence bugs.

### Dependency-Direction Signals

The starter repo should expose:
- tracker-side state ownership
- packet/result-side consumption

Checks should verify:
- preview/save modules may depend on packet/result headers
- preview/save modules may not depend on tracker-internal headers beyond a narrow allowed surface
- preview/save modules may not call tracker accessors meant for packet assembly

The point is dependency direction, not exact symbol names.

### Symbol-Ownership Signals

The evaluator should identify the assembly-owned behaviors:
- folding in the in-progress tote
- assigning final packet row numbers
- computing the packet summary

Checks should verify those behaviors are not implemented in preview/save/render/write-side files over raw tracker state.

### Structural Signals

Checks should verify:
- packet assembly logic is reachable through a domain-side API or domain-side module
- consumer-layer shared helpers, if any, accept packet/result data rather than raw tracker state
- newly added helper code under preview/save/writer/app files does not become the sole owner of packet assembly logic

This is how the evaluator should catch the shared output-side helper false positive without demanding one exact architecture.

## Functional Checks

- Preview returns or prints the same packet content that save persists for the same tracker state.
- If the tracker contains one in-progress tote, that tote appears in both preview and save output.
- Packet row numbers are correct in both preview and save.
- Packet summary is correct in both preview and save.
- Calling preview before save does not alter the saved packet.
- Calling save before preview does not alter the previewed packet.
- Repeated preview/save calls remain stable.
- Existing non-handover behavior remains unchanged.

## Structural / Static Checks

- Forbid evaluator changes.
- Add checks that preview/save-side files do not implement packet assembly directly from tracker state.
- Add checks that preview/save-side shared helpers do not accept raw tracker state as packet assembly input.
- Add checks that packet/result-side APIs or domain-side assembly logic are actually used by both consumers.
- Add dependency/include checks to keep tracker-internal assembly details out of consumer modules.
- Add symbol-usage or grep-based checks around the assembly-owned behaviors if the final starter code exposes stable names for them.

These checks should target ownership, not style. Avoid forcing exact filenames beyond what is needed for layer identification.

## False-Positive and False-Negative Risks

### False Positives

- A behaviorally correct shared helper under writer/preview/app code assembles the packet once and feeds both consumers.
  - Mitigation: dependency-direction checks, helper input checks, and symbol-ownership checks must classify this as consumer-side assembly.

- A formatter helper appears pure but computes missing packet fields from tracker state.
  - Mitigation: ensure formatter/render helpers are only allowed to accept packet/result data.

### False Negatives

- A good solution uses a different domain-side object or API name than expected.
  - Mitigation: do not check for exact class names; check for boundary properties and data flow.

- A good solution introduces a new domain-side assembly module rather than extending the tracker directly.
  - Mitigation: allow either tracker-owned or domain-adjacent assembly as long as consumer-side ownership is avoided.

## Leakage Risks and Mitigation Notes

### Leakage Risks

- `TASK.md` could expose the case intent if it mentions stable result assembly or separation ideas directly.
- Starter comments could reveal that the writer path is intentionally “wrong.”
- Test names or check names could expose the ownership rule.

### Mitigations

- Keep `TASK.md` purely product-facing.
- Keep structural language only in `docs/020.handover-packet-ownership-boundary/SPEC.md` and evaluator files.
- Use neutral behavioral test names.
- Make the initial save-path design feel plausibly legacy, not pedagogical.

## Notes for Later Starter-Code Authoring

- Keep the code small: one tracker, one packet/result type, one preview path, one save path.
- Ensure the save path currently assembles packet rows inline from tracker state.
- Ensure the repo already has a packet/result concept so consumers can legitimately depend on it.
- Keep packet assembly rules minimal:
  - include one in-progress tote
  - assign row numbers
  - compute one small summary
- Avoid multiple formats, exporter registries, lifecycle workflows, or extra infrastructure.
- Keep filesystem behavior simple and deterministic.

## Notes for Later Evaluator Authoring

- Favor a mixed oracle:
  - deterministic behavior tests
  - include/dependency checks
  - targeted grep/symbol checks
- Build structural checks around data flow:
  - tracker state -> packet/result is domain-side
  - packet/result -> preview/save is consumer-side
- Explicitly test the known false positive:
  - a shared output-side helper that accepts tracker state and assembles packet content should fail
- Keep checks tolerant of alternative good decompositions.
- Avoid brittle checks that require one exact class name such as `PacketBuilder`.
- Avoid location-only policing unless paired with dependency and symbol ownership evidence.

## Maintainability Mapping

Primary Dimension:
- D3 Responsibility Decomposition

Measured Capability:
- preserve ownership of domain-result assembly
- prevent consumer-side code from taking over business completion logic

Secondary Dimensions:
- D9 Side-Effect Isolation
- D8 State Ownership and Lifecycle

## Allowed & Disallowed Summary

| Action                         | Allowed |
|--------------------------------|---------|
| Add new files                  | Yes     |
| Modify existing core logic     | Yes     |
| Modify existing tests          | No      |
| Add new dependencies           | No      |
| Modify public headers          | Yes     |
| Use global mutable state       | No      |
| Introduce new external IO      | No      |
