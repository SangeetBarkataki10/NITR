## Task

Start wiring the SRP-style estimation pipeline so the `cv_srp` executable can read the input pair and run through the new pipeline instead of relying on the legacy monolith.

### Requirements
- Implement the parser and normalization flow through the SRP pipeline.
- Keep the CLI contract as `cv_srp --input <pair.json> --output <result.json>`.

### Constraints
- Do not modify `src/legacy_monolith.cc`.
- Do not call the legacy monolith from the normal SRP execution path.
- Keep JSON parsing out of estimator and scoring code.
- Do not modify evaluator files.
