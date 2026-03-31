# Task

Implement support for a compact rendering mode in the inventory report.

## Requirements

Add a new field to `ReportOptions`:

- `compact_mode` with default value `false`

Keep the existing full mode behavior unchanged.

When `compact_mode` is `true`:

- the header must be exactly:
  `Inventory Report (compact)`
- each row must be rendered as:
  `<id>:<name>:<quantity>`
- if `include_summary` is `true`, the summary must be exactly:
  `Total quantity: <sum>`
- if `include_summary` is `false`, omit the summary
