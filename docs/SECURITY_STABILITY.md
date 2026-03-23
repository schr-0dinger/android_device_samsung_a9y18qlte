# Security / Stability Notes

## Live Findings So Far

### Lockscreen / credential issue
- `lock_settings` service is present on the device.
- Legacy gatekeeper and keystore binder services are present.
- `locksettings.db` exists under `/data/system`.
- Live testing was partially blocked by flaky ADB while probing credential paths.
- On the current device state, `cmd lock_settings sp` reports `SP Enabled = false`.
- Framework source shows synthetic password is enabled by default in `LockSettingsService`, so this specific `SP=false` state is likely per-device database state, not a tree default.
- The strongest remaining hypothesis is a combination of bad current-device SP state plus gatekeeper/keymaster runtime mismatch rather than a completely missing locksettings stack.

### Encryption
- Current live ROM reports `ro.crypto.state=unsupported`.
- Current normal-boot `fstab.qcom` has `/data` mounted with no encryption flags.
- Recovery still expects `/data` as `encryptable=footer`.
- Stock extracted vendor `fstab.qcom` is also effectively unencrypted.

Interpretation:
- enabling encryption should be treated as a separate deliberate bring-up item, not an accidental side effect of other fixes
- changing this blindly is risky because it can require a userdata wipe and can easily create an unbootable build if the chosen mode is wrong

### Fingerprint
- Fingerprint HALs and init RCs are packaged in the vendor tree.
- The device manifest advertises the fingerprint HAL.
- The device tree was missing the framework feature XML copy for fingerprint.
- That omission can hide Settings options even when lower layers exist.

### SELinux enforcing readiness
- `BoardConfig.mk` still forces `androidboot.selinux=permissive`.
- Device-specific `file_contexts` was missing labels for:
  - `android.hardware.gatekeeper@1.0-service`
  - `android.hardware.keymaster@3.0-service`
- Those labels are now added in the source tree.

## Changes Landed In Source Tree

1. Added fingerprint feature XML to the device build:
- `frameworks/native/data/etc/android.hardware.fingerprint.xml -> system/etc/permissions`

2. Added SELinux exec labels for:
- `/vendor/bin/hw/android.hardware.gatekeeper@1.0-service`
- `/vendor/bin/hw/android.hardware.keymaster@3.0-service`

## Recommended Next Validation

### On the next build
1. Check `pm list features | grep fingerprint`
2. Check whether fingerprint screen-lock option appears on a tester device with a working sensor
3. Test temporary PIN/password persistence across reboot
4. Capture targeted logcat while setting a PIN:
   - `LockSettings`
   - `SyntheticPassword`
   - `gatekeeper`
   - `keymaster`
   - `keystore2`
5. Capture permissive AVC denials before attempting enforcing

### Do not do yet
- Do not flip encryption on in `fstab.qcom` until we validate the intended mode and wipe implications.
- Do not remove `androidboot.selinux=permissive` until we have a denial-driven policy pass.
