# Null Pointer Checks

## Issue

Currently all functions do proper argument checking which might degrade
performance.

## Constraints

## Assumptions

## Considered Alternatives

- Removing all null pointer checks and do assert on debug code
- Removing some null pointer checks
- adding functional high-level methods that avoid most null pointer checks

## Decision

Delayed to 1.0.0

## Argument

- should have consistent, defined behavior

## Implications

- ABI, API

## Related decisions

## Notes

- Benchmarks needed
