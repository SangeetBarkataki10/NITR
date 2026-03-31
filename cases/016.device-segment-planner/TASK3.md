## Task

Finish the device-placement update so the planner and runner handle arbitrary valid configs deterministically.

### Requirements
- Keep the legacy and updated config behavior working.
- Generalize to arbitrary valid configs by coalescing consecutive same-device-required steps into one segment.
- Ensure execution follows the computed segmentation result instead of assuming all steps run on GPU.
- Keep backward compatibility for the existing config loader and command-line entrypoint.

### Constraints
- Do not modify files under `evaluator/`.
- You may add new files under `src/`.
- Do not add third-party dependencies.
- Keep existing behavior unchanged unless required above.
