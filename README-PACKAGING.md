# Native RT4SV++ packages with Podman

Place `packaging/` at the root of your RT4SV++ repository, alongside `ui_class.pro`.

## Prerequisites (on Fedora)

```bash
sudo dnf install podman
```

No local Qt, CCfits, CFITSIO or compiler installation is needed for these builds.

## Build

```bash
chmod +x packaging/*.sh
./packaging/build.sh ubuntu 22.04
./packaging/build.sh ubuntu 24.04
./packaging/build.sh ubuntu 26.04
./packaging/build.sh fedora 44
./packaging/build.sh fedora 45
```

To build all targets sequentially:

```bash
./packaging/build.sh all
```

To set the application version:

```bash
RT4SVPP_VERSION=1.48 ./packaging/build.sh ubuntu 24.04
```

Builds take a snapshot of the current working tree (including uncommitted changes) into the container; they never edit the host source tree. Finished files are in `dist/`.

## Install and test

Ubuntu, matching .deb:

```bash
sudo apt install ./dist/rt4svpp_1.48-1_ubuntu24.04_amd64.deb
rt4sv++ --version
```

Fedora, matching .rpm (actual filename includes `.fc44` or `.fc45`):

```bash
sudo dnf install ./dist/rt4svpp-1.48-1.fc44.x86_64.rpm
rt4sv++ --version
```

For both, also run an actual FITS processing smoke test and verify GUI on the target OS:

```bash
rt4sv++ --input sample_data/*.fits --aot all
```

## What the packages contain

- `/usr/bin/rt4sv++`
- `/usr/share/applications/rt4svpp.desktop`

The `.deb` declares dependencies calculated by `dpkg-shlibdeps`; the `.rpm` relies on automatic ELF dependency extraction. System Qt6, CCfits and CFITSIO are installed by APT/DNF. These are **not** static/self-contained binaries.

The `--version` and `--help` smoke checks are run in the build container. Package installation and GUI tests on a clean VM are **still required** before release.

## Important caveats

- First version targets `x86_64` only.
- `RT4SVPP_VERSION` must use an RPM-compatible numeric version (e.g. `1.48`, `1.48.1`).
- Separate packages should be installed on their corresponding distribution release. The packaging scripts do not publish to GitHub.
- RPM `License` is GPL-3.0-or-later, reflecting the binary distribution terms in `LICENSE.md` (the QCustomPlot components are GPL).
- `Exec=rt4sv++ %F` GUI desktop entry supports passing paths; replace generic icon with the actual project icon later.
- Ubuntu 22.04 uses Qt 6.2; building against it is a useful compatibility test, not a guarantee the current code supports it.

Add `/dist/` to `.gitignore`.
