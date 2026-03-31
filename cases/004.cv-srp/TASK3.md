## Task

Finish the SRP-style estimation pipeline so the default executable behavior matches the existing legacy behavior on the provided scenarios.

### Requirements
- Keep the parser, normalization, estimation, scoring, and policy flow working through the SRP pipeline.
- Implement the serialization/output flow through the SRP pipeline.
- Make the default executable behavior match the legacy reference output on the provided scenarios.
- Preserve the required exit codes and stderr error strings for invalid input, estimation failure, and reject cases.

### Constraints
- Do not modify `src/legacy_monolith.cc`.
- Do not call the legacy monolith from the normal SRP execution path.
- Keep JSON parsing/serialization out of estimator, scoring, and policy code.
- Keep decision logic out of estimator code, and keep policy logic based on metrics rather than recomputing residuals.
- Do not modify evaluator files.
