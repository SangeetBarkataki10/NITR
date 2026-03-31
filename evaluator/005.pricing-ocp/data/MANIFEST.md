# discount-ocp public cases
Each case has `<name>.in.json` and `<name>.out.json` under `data/`.
For m4 cases, the corresponding rules file is under `data/rules/` and should be passed via `--rules`.

## Cases
- **m1_basic** (m1)
  - run: `tools/pricing --in cases/discount-ocp/data/m1_basic.in.json --out /tmp/m1_basic.out.json --milestone m1`
- **m1_none** (m1)
  - run: `tools/pricing --in cases/discount-ocp/data/m1_none.in.json --out /tmp/m1_none.out.json --milestone m1`
- **m2_both_coupons** (m2)
  - run: `tools/pricing --in cases/discount-ocp/data/m2_both_coupons.in.json --out /tmp/m2_both_coupons.out.json --milestone m2`
- **m2_duplicates** (m2)
  - run: `tools/pricing --in cases/discount-ocp/data/m2_duplicates.in.json --out /tmp/m2_duplicates.out.json --milestone m2`
- **m3_coupon_exclusive** (m3)
  - run: `tools/pricing --in cases/discount-ocp/data/m3_coupon_exclusive.in.json --out /tmp/m3_coupon_exclusive.out.json --milestone m3`
- **m4_disable_member** (m4)
  - run: `tools/pricing --in cases/discount-ocp/data/m4_disable_member.in.json --out /tmp/m4_disable_member.out.json --milestone m4 --rules cases/discount-ocp/data/rules/m4_disable_member.rules.json`
- **m4_group_tie_break** (m4)
  - run: `tools/pricing --in cases/discount-ocp/data/m4_group_tie_break.in.json --out /tmp/m4_group_tie_break.out.json --milestone m4 --rules cases/discount-ocp/data/rules/m4_group_tie_break.rules.json`
- **m4_multi_group** (m4)
  - run: `tools/pricing --in cases/discount-ocp/data/m4_multi_group.in.json --out /tmp/m4_multi_group.out.json --milestone m4 --rules cases/discount-ocp/data/rules/m4_multi_group.rules.json`
