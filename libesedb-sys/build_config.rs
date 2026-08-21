use std::env;

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub(crate) enum TargetConfig {
    WindowsMsvc,
    Unix { macos: bool },
}

impl TargetConfig {
    pub(crate) fn from_cargo_env() -> Result<Self, String> {
        Self::from_values(
            &env::var("CARGO_CFG_TARGET_OS")
                .map_err(|error| format!("CARGO_CFG_TARGET_OS is unavailable: {error}"))?,
            &env::var("CARGO_CFG_TARGET_FAMILY")
                .map_err(|error| format!("CARGO_CFG_TARGET_FAMILY is unavailable: {error}"))?,
            &env::var("CARGO_CFG_TARGET_ENV").unwrap_or_default(),
        )
    }

    pub(crate) fn from_values(
        target_os: &str,
        target_families: &str,
        target_env: &str,
    ) -> Result<Self, String> {
        if target_os == "windows" {
            return if target_env == "msvc" {
                Ok(Self::WindowsMsvc)
            } else {
                Err(format!(
                    "unsupported Windows target environment {target_env:?}; the bundled \
                     libesedb C configuration currently supports only MSVC"
                ))
            };
        }

        if target_families.split(',').any(|family| family == "unix") {
            return Ok(Self::Unix {
                macos: target_os == "macos",
            });
        }

        Err(format!(
            "unsupported target OS {target_os:?} in target family {target_families:?}"
        ))
    }
}
