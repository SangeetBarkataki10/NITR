# 014. report-export-ocp

## Summary
Add support for exporting reports in **Markdown** format without hard-coding the new format into the central export service.

## Primary maintainability dimension
- **D4. Extension Structure**

## Secondary dimensions
- Responsibility decomposition
- Change locality
- Reuse of existing abstraction

## Motivation
This case probes whether a coding agent extends an existing export architecture or patches the central dispatcher when a new format is requested.

The repository already contains:
- a `ReportExporter` interface,
- concrete exporters for existing formats,
- a `ReportExportService` that delegates export requests to registered exporters.

The requested feature is small: add Markdown export. The maintainable solution is to implement a new exporter and register it through the existing extension seam. The unmaintainable solution is to modify the central service with format-specific branching.

## Task for humans
The system currently exports reports in text and CSV formats. Extend it to also support Markdown export.

A report contains:
- a title,
- a list of column names,
- a list of rows.

Add Markdown export with the following output format:

For a report with title `Quarterly Metrics`, columns `Name, Value`, and rows `(Latency, 120ms)`, `(Errors, 3)`, the Markdown output must be:

```text
# Quarterly Metrics

| Name | Value |
| --- | --- |
| Latency | 120ms |
| Errors | 3 |
```

Requirements:
- Preserve existing text and CSV behavior.
- Add Markdown export for format key `markdown`.
- Reuse the existing exporter abstraction.
- Do not add format-specific branching to the central export service.

## Agent-facing TASK.md section
See `TASK.md`.

## Expected good solution shape
A good solution typically:
- adds a new `MarkdownReportExporter`,
- keeps format-specific rendering inside that exporter,
- registers the exporter through the existing factory/composition layer,
- leaves `ReportExportService` generic.

## Common bad solutions
Bad solutions include:
- adding `if (format == "markdown")` or similar branching inside `ReportExportService`,
- modifying the central service to construct Markdown output directly,
- bypassing the `ReportExporter` interface,
- scattering Markdown-specific logic across unrelated files.

## Functional oracle
The evaluator checks that:
- text export still works,
- CSV export still works,
- Markdown export works for the provided format key,
- Markdown formatting matches the required output exactly.

## Structural oracle
The evaluator checks that:
- `ReportExportService` remains format-agnostic,
- `report_export_service.cc` does not contain `markdown`-specific branching,
- the new format is added by extension through the exporter abstraction.

## Why this case exists
Many agents can add a new output format functionally. Fewer preserve the original extension structure. This case isolates whether the agent recognizes and uses the existing plugin-style seam instead of collapsing back to a central dispatcher patch.
