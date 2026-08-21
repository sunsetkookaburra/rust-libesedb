#[allow(dead_code)]
#[path = "../libesedb-sys/build_config.rs"]
mod build_config;

use build_config::TargetConfig;

#[test]
fn windows_msvc_uses_the_windows_configuration() {
    assert_eq!(
        TargetConfig::from_values("windows", "windows", "msvc"),
        Ok(TargetConfig::WindowsMsvc)
    );
}

#[test]
fn windows_gnu_fails_with_an_actionable_diagnostic() {
    let error = TargetConfig::from_values("windows", "windows", "gnu")
        .expect_err("the bundled C configuration does not support MinGW");

    assert!(error.contains("Windows target environment \"gnu\""));
    assert!(error.contains("supports only MSVC"));
}

#[test]
fn macos_retains_its_unix_adjustments() {
    assert_eq!(
        TargetConfig::from_values("macos", "unix", ""),
        Ok(TargetConfig::Unix { macos: true })
    );
}

#[test]
fn linux_uses_the_general_unix_configuration() {
    assert_eq!(
        TargetConfig::from_values("linux", "unix", "gnu"),
        Ok(TargetConfig::Unix { macos: false })
    );
}

#[test]
fn comma_separated_target_families_are_supported() {
    assert_eq!(
        TargetConfig::from_values("example", "wasm,unix", ""),
        Ok(TargetConfig::Unix { macos: false })
    );
}

#[test]
fn unsupported_target_fails_before_compiling_bundled_c() {
    let error = TargetConfig::from_values("none", "wasm", "")
        .expect_err("a target without a bundled configuration must fail early");

    assert!(error.contains("unsupported target OS \"none\""));
}
