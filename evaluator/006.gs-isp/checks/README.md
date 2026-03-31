These checks are intended for the post-task evaluation phase.

- `check_data_isp.py` validates that sorting, shading, and compositing no longer
  depend directly on the legacy `HitBuffer` type and that stage-specific views
  are introduced instead.
