# Tester Checklist: Security / Lockscreen / Fingerprint / SELinux

Use this on a build that includes the latest device-tree fixes.

## 1. Basic Security UI

Check whether these options are visible:
- Pattern
- PIN
- Password
- Fingerprint

Record:
- whether each option is shown
- whether selecting it crashes Settings

## 2. Temporary Credential Test

1. Set a temporary PIN
2. Lock the screen
3. Unlock with the PIN
4. Reboot the phone
5. Unlock again with the same PIN
6. Remove the PIN

Record:
- whether the PIN setup succeeds
- whether the PIN survives reboot
- whether the credential disappears after reboot
- whether the phone bootloops or asks for an unexpected password

## 3. Fingerprint Test

Only for devices with a working fingerprint sensor.

1. Open fingerprint enrollment
2. Check whether enrollment starts
3. Try adding one finger
4. Lock the phone
5. Test fingerprint unlock

Record:
- whether the fingerprint menu appears
- whether enrollment starts or fails immediately
- exact error text if shown

## 4. Encryption State

From adb:
```sh
adb shell getprop ro.crypto.state
adb shell getprop ro.crypto.type
adb shell getprop vold.decrypt
```

Record the output.

## 5. SELinux / Security Logs

After reproducing lockscreen or fingerprint issues, capture:
```sh
adb logcat -d -b all | grep -i -E 'LockSettings|SyntheticPassword|gatekeeper|keymaster|keystore2|fingerprint|biometric|avc: denied'
```

Also capture kernel denials if available:
```sh
adb shell dmesg | grep -i 'avc: '
```

## 6. Useful Runtime State

```sh
adb shell cmd lock_settings sp
adb shell pm list features | grep -i -E 'fingerprint|biometric|secure_lock_screen'
adb shell service list | grep -i -E 'finger|gate|key|weaver|biometric|lock'
```

## 7. Report Format

Please include:
- build date / zip filename
- whether device was clean-flashed or dirty-flashed
- whether userdata was wiped
- whether a lock credential existed before the test
- the exact outputs of the commands above
