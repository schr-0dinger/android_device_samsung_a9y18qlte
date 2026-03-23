# QASSA A9 Stabilization Plan (Next 48 Hours)

## Goal

Finish a stable QASSA AOSP build for `a9y18qlte` before the current workstation becomes unavailable.
VoLTE iteration then continues from that stable ROM baseline instead of from live ad-hoc overlays.

## Day 1

1. Verify source tree integrity
- confirm device/vendor trees contain the intended text changes
- confirm current vendor prebuilts match expected hashes
- confirm audio HAL init RC packaging fix is still present

2. Produce a clean build artifact
- sync from `Samsung` into `qassa`
- perform a clean build
- verify the output image contains the expected files before flashing

3. Boot verification
- confirm boot completes
- confirm audio services start
- confirm `com.sec.imsservice` installs and runs
- confirm SIM, LTE, and data remain stable

## Day 2

1. Core telephony verification
- outgoing normal call
- SMS send/receive
- mobile data
- hotspot if relevant

2. IMS verification
- confirm Samsung IMS package loads
- confirm VoLTE capability shows up in telephony logs
- test outgoing IMS call
- only then resume targeted incoming-call work

## Guardrails

- do not reintroduce the rejected `telephony-common.jar` patch
- do not use the slot-0-only MMTEL suppression patch as baseline
- keep live experiments separate from source-of-truth tree changes
- record every flashed build with its output zip name and `imsservice.apk` hash
