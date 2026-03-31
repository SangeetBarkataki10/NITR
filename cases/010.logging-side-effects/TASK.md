Implement the loan review workflow in `src/`.

Requirements:
- `EvaluateApplicant` should determine whether an applicant is approved and list denial reasons.
- `ReviewApplicants` should process a batch of applicants, return approved applicant ids in input order, and emit one audit log line per applicant.
- Approval rules:
    - credit score must be at least `700`
    - annual income must be at least `50000`
    - debt ratio must be at most `0.40`
- Use the exact denial reason tokens and ordering described as:
    1. `low_credit`
    2. `low_income`
    3. `high_debt`
- Use the exact audit message format:
    - approved applicant: `"<id> approved"`
    - denied applicant: `"<id> denied: <reason1>,<reason2>,..."`
- Keep all public headers and function names unchanged.
- The project should build with CMake and pass the provided tests.
