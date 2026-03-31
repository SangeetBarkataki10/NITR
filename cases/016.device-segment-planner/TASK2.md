## Task

Extend the pipeline execution tool so device placement also supports the newer per-step device style.

### Requirements
- Keep the legacy config behavior working.
- Support the updated case where step-level device requirements produce `GPU: 1-4`, `CPU: 5`, `GPU: 6`, `CPU: 7-8`.
- Keep backward compatibility for the existing config loader and command-line entrypoint.

### Constraints
- Do not modify files under `evaluator/`.
- You may add new files under `src/`.
- Do not add third-party dependencies.
- Keep existing behavior unchanged unless required above.
