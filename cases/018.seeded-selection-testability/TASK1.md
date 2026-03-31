## Task

Add deterministic replay support for recommendation selection while keeping the existing default production entrypoint intact.

### Requirements
- Keep `SelectRecommendations(candidates, k)` available for default production usage.
- Add or complete `SelectRecommendationsReplay(candidates, k, seed)`.
- Use primary candidates (`eligible == true && is_fallback == false`) when available.
- Use fallback candidates (`eligible == true && is_fallback == true`) only when no primary candidate is eligible.
- If no eligible candidate exists at all, return an empty result.
- Non-random ordering priority is `score DESC`, then `id ASC`.

### Constraints
- Do not add time/sleep/timeout-based logic.
- Do not add test-only branches or debug-only force-pick hooks.
- Do not thread seed/control parameters through unrelated public APIs.
- Keep implementation in C++ and preserve a small, maintainable selector API.
