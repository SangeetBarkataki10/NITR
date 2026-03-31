# Evaluator Verdict Convention

This file defines the minimal runner convention for case `015-pipeline-provider-decoupling`.

## Entry points

### Visible evaluator

```bash
./evaluator/015.pipeline-provider-decoupling/run_visible.sh
```

Default behavior:
- configure with `CASE015_ENABLE_VISIBLE_CHECKS=ON`
- configure with `CASE015_ENABLE_HIDDEN_EVALUATOR=OFF`
- build the case
- run all visible CTest tests
- optionally validate modified-file scope through `check_allowed_file_touches.py`

Optional environment variables:
- `BUILD_DIR=/path/to/build-dir`
- `CMAKE_BIN=cmake`
- `CTEST_BIN=ctest`
- `PYTHON_BIN=python3`
- `MODIFIED_FILES="src/pipeline_runner.cc src/build_pipeline.cc app/main.cc"`

### Extended evaluator

```bash
./evaluator/015.pipeline-provider-decoupling/run_hidden.sh
```

Default behavior:
- configure with `CASE015_ENABLE_VISIBLE_CHECKS=ON`
- configure with `CASE015_ENABLE_HIDDEN_EVALUATOR=ON`
- build the case
- run all visible and extended CTest tests/checks
- optionally validate modified-file scope through `check_allowed_file_touches.py`

Optional environment variables are the same as for `run_visible.sh`.

## Exit code convention

### `run_visible.sh`
- `0`: visible evaluator passed
- `10`: CMake configure failed
- `11`: build failed
- `12`: visible tests or visible structural checks failed
- `13`: modified-file scope check failed

### `run_hidden.sh`
- `0`: extended evaluator passed
- `20`: CMake configure failed
- `21`: build failed
- `22`: visible or extended tests or structural checks failed
- `23`: modified-file scope check failed

## Suggested verdict categories

These categories are for the outer evaluation harness.

- `pass`
  - visible evaluator passed
  - extended evaluator passed
  - modified-file scope respected
- `visible_only_pass`
  - visible evaluator passed
  - extended evaluator failed
- `functional_pass_structural_fail`
  - build succeeded
  - functional tests passed
  - one or more structural checks failed
- `forbidden_file_touch`
  - modified-file scope check failed
- `build_fail`
  - configure or build failed
- `test_fail`
  - one or more visible or extended behavior tests failed

## Optional JSON result schema

An outer harness may normalize results into a JSON object such as:

```json
{
  "case_id": "015-pipeline-provider-decoupling",
  "mode": "visible",
  "configure_pass": true,
  "build_pass": true,
  "ctest_pass": true,
  "file_touch_scope_pass": true,
  "verdict": "pass",
  "modified_files": [
    "src/pipeline_runner.cc",
    "src/build_pipeline.cc"
  ]
}
```

## Notes

- `TASK.md` remains the agent-facing contract.
- `SPEC.md` may remain private for repository authors.
- This case uses the standard `app/`, `evaluator/`, `src/`, `TASK.md`, and `CMakeLists.txt` structure so evaluation logic stays outside the task statement.
- Extended evaluator coverage should continue to prioritize dependency-boundary violations even when visible functionality passes.
