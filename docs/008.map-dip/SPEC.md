# Solidbench Case 003 — MAP-DIP-SNAPSHOT

```yaml
case_id: MAP-DIP-SNAPSHOT
domain: map
principle: DIP
difficulty: easy
language: C++
loc: ~250
```

## 2. Problem Context
A mapping system builds a **MapSnapshot** by fetching multiple *layers* (e.g., geometry, semantics) and assembling them into one output.
Teams frequently add new layer types as the system evolves, often from separate modules/plugins.

## 3. Given Code
The provided code builds snapshots correctly for the built-in layers, but it violates DIP:
- The snapshot builder **directly constructs concrete layer providers** using `if/else` on the layer `"type"`.
- Adding a new layer requires editing existing core logic.

The code compiles and all provided tests pass.

## 4. Task Description
Refactor the implementation to satisfy DIP **without changing the observable behavior** for existing layers.

### Behavioral requirements
- `map_snapshot` reads a JSON config from a file path argument.
- It reads all stdin as the input payload string.
- It outputs a stable text snapshot format (see tests).

### Constraints
You **must not** modify:
- `cases/008.map-dip/app/main.cc`
- evaluator files under `evaluator/008.map-dip/`
- The public signature of `MapSnapshotService::BuildSnapshot(...)`

You **may**:
- Add new files/classes
- Modify files under `cases/008.map-dip/src/`
- Introduce a registry/factory mechanism

### Plugin requirement (killer DIP test)
The evaluator will compile an extra translation unit that registers a new layer type:
- `reverse_payload` — reverses the stdin payload string and returns it as a layer.

Your solution must pass this test **without modifying** the snapshot core logic.

## 5. Expected Design Direction (Non-prescriptive)
Acceptable directions include:
- A registry of layer creators keyed by `"type"`
- An injected factory/registry into the snapshot service
- Separation between “pipeline policy” (config) and “construction mechanism” (providers)

## 6. Evaluation Criteria

### 6.1 Functional
- Existing tests pass (built-in layers: `geometry`, `semantics`)
- New plugin test passes (`reverse_payload`)

### 6.2 Structural
- No branching on concrete `"type"` strings inside the snapshot service implementation.
- No mention of concrete provider class names inside the snapshot service implementation.

### 6.3 Design
- Adding a new layer type is achievable by registering a creator function, without editing core service code.

## 7. Failure Modes (Non-scoring)
- Implementing `reverse_payload` by adding another `if (type == "reverse_payload")` branch.
- Using RTTI/dynamic_cast with a monolithic base class.
- Hardcoding a list of supported layer types in the service.

## 8. Principle Mapping
Violated Principle: Dependency Inversion Principle (DIP)
Measured Capability:
  - Ability to extend behavior by adding new implementations that depend on stable abstractions
  - Core policy depending only on interfaces/registries, not concrete providers

## 9. Allowed & Disallowed Summary

| Action                         | Allowed |
|--------------------------------|---------|
| Add new files                  | Yes     |
| Modify existing core logic     | src only|
| Modify existing tests          | No      |
| Add new dependencies           | No      |
| Use reflection / RTTI          | No      |
