## Task

Extend the SRP-style estimation pipeline so it completes estimation, scoring, and policy decisions through the new execution path.

### Requirements
- Keep the parser and normalization flow working.
- Implement the estimation, scoring, and policy flow through the SRP pipeline.
- Preserve the required exit codes and stderr error strings for invalid input, estimation failure, and reject cases.

### Constraints
- Do not modify `src/legacy_monolith.cc`.
- Do not call the legacy monolith from the normal SRP execution path.
- Keep JSON parsing/serialization out of estimator, scoring, and policy code.
- Keep decision logic out of estimator code, and keep policy logic based on metrics rather than recomputing residuals.
- Do not modify evaluator files.
