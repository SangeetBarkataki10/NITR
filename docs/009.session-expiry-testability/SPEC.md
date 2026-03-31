# 009. session-expiry-testability

## Summary
This case evaluates whether an agent can implement time-based expiration logic in a way that remains easy to test, extend, and maintain. The task is intentionally small: implement a `SessionManager` that creates sessions, validates them against a TTL, and refreshes them. The maintainability challenge is that time-dependent logic often becomes coupled to real wall-clock time, which makes tests slow, flaky, and hard to reason about.

The key question is not merely whether the expiration behavior works, but whether the implementation makes time-driven behavior deterministic and cheap to test.

---

## Maintainability Mapping
- **Primary dimension:** testability
- **Secondary dimensions:** dependency control, change locality, API stability
- **Typical failure mode:** expiration logic directly reads the system clock inside business logic, forcing tests to depend on real time or `sleep`
- **Target capability:** introduce an appropriate seam for controlling time without leaking evaluation intent into the public API

---

## Case Intent
Human reviewers should use this case to distinguish between:

- **Functionally correct but brittle solutions**, which compute expiration by directly reading wall-clock time in core logic and require real-time waiting in tests
- **Maintainable solutions**, which make time behavior deterministic and fast to test by separating time access from session rules

This is a maintainability probe, not just a dependency-injection probe. A solution only passes the structural goal if it enables boundary-condition tests without sleeping or waiting for real time to pass.

---

## User-Facing Task
Implement a small session-management component.

A session has:
- a string session id
- a creation time
- a last-refresh time
- a TTL in seconds

The component should support:
- creating a session
- checking whether a session is currently valid
- refreshing an existing session so its validity window restarts from the refresh time
- removing a session

Behavior rules:
1. A session is valid immediately after creation.
2. A session becomes invalid once the elapsed time since its most recent start point reaches the TTL.
   - The most recent start point is the creation time if the session has never been refreshed.
   - Otherwise it is the most recent refresh time.
3. Refreshing a valid session makes it valid again for a full TTL window starting at refresh time.
4. Refreshing a missing or already expired session should fail.
5. Removing a session should make later validity checks fail.

The implementation should remain small, readable, and easy to test.

---

## Required Repository Structure
Each case uses the following layout:

```text
- cases/009.session-expiry-testability/
  - app/
    - main.cc
  - src/
  - TASK.md
  - CMakeLists.txt
- evaluator/009.session-expiry-testability/
  - checks/
  - data/
  - tests/
- docs/009.session-expiry-testability/
  - SPEC.md
```

All code must be in English.

---

## Expected Starter Setup
The starter repository should provide:
- a minimal `SessionManager` declaration or skeleton in `cases/009.session-expiry-testability/src/`
- a tiny demo program in `cases/009.session-expiry-testability/app/main.cc`
- evaluator tests that check functional behavior
- evaluator structural checks that inspect whether the final implementation couples business logic directly to system time

The starter should not mention evaluation strategy to the agent.

---

## Evaluation

### Functional checks
The evaluator should verify at least:
- creating a session makes it valid
- a session expires exactly at the TTL boundary according to the specified rule
- refreshing a valid session restarts its validity window
- refreshing an expired session fails
- removing a session invalidates it

### Maintainability checks
The evaluator should additionally verify that the solution supports deterministic time-based testing.

Signals of a strong solution:
- session logic can be tested without `sleep`
- time progression can be controlled in tests
- boundary conditions are easy to encode precisely
- public APIs are not polluted with evaluation-specific hooks

Signals of a weak solution:
- business logic directly calls `std::chrono::system_clock::now()`, `std::time`, or similar wall-clock APIs
- tests must wait for real time to pass
- time logic is scattered across multiple call sites
- internal state is exposed only to compensate for poor testability

### Suggested oracle signals
Possible structural or semi-structural signals include:
- detect direct wall-clock reads from session-domain logic files
- reject tests that rely on long `sleep`-based timing
- reward designs that isolate time access behind a small seam or passed-in dependency
- ensure no evaluation-only backdoors were added to the public API

---

## Why This Case Matters
AI coding agents often produce code that is functionally correct for time-based features but hard to test and maintain. Real-time coupling is a common source of flaky tests and future change cost. This case isolates that failure mode in a small, explainable probe.

---

## TASK.md Section
The agent-facing task should contain only the concise implementation request below, without describing the evaluation purpose or maintainability rationale.

```md
Implement a small `SessionManager`.

A session has an id and a TTL in seconds.
Support:
- creating a session
- checking whether a session is currently valid
- refreshing a valid session so its validity window restarts
- removing a session

Rules:
1. A session is valid immediately after creation.
2. A session becomes invalid once the elapsed time since creation or the most recent refresh reaches the TTL.
3. Refreshing a missing or expired session should fail.
4. Removing a session makes later validity checks fail.

Keep the implementation small and readable.
```
