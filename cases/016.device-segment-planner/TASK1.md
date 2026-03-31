## Task

Update the pipeline execution tool so device placement supports the legacy config style instead of assuming the whole pipeline runs on GPU.

### Requirements
- Support the legacy case where `legacy_gpu_through_step: 4` means steps 1-4 run on GPU and steps 5-8 run on CPU.
- Keep backward compatibility for the existing config loader and command-line entrypoint.

### Constraints
- Do not modify files under `evaluator/`.
- You may add new files under `src/`.
- Do not add third-party dependencies.
- Keep existing behavior unchanged unless required above.
