# Task

Add summary caching to `InventoryReportService`.

Requirements:
- Repeated `GetSummary()` calls should reuse the last computed summary when the product collection has not changed.
- `ReplaceProducts(...)` should make the old cached summary invalid.
- `UpsertProduct(...)` should make the old cached summary invalid.
- `ClearCache()` should force the next `GetSummary()` call to recompute the summary.
- Keep the current behavior of summary values correct after product replacement and updates.
