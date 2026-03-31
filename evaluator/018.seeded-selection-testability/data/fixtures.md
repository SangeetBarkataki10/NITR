# Case 018 Fixture Notes

Evaluator tests use fixed fixture families:
- single replay pick
- multi replay pick
- k larger than pool
- tie-heavy score groups
- fallback-only eligible pool
- fully ineligible pool

Replay expectations are computed against the SamplerV1 reference contract in test code.
Default-path evaluation is invariant-based and does not require exact IDs.
