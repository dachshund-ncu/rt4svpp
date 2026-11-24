#!/usr/bin/env bash
set -Eeuo pipefail

: "${RT4SVPP_VERSION:?}"
: "${RT4SVPP_DISTRO:?}"
: "${RT4SVPP_RELEASE:?}"

if [[ "$RT4SVPP_DISTRO" == ubuntu ]]; then
  export DEBIAN_FRONTEND=noninteractive
  apt-get update
  apt-get install -y --no-install-recommends \
    build-essential gfortran make tar file \
    qt6-base-dev qt6-base-dev-tools qmake6 libqt6svg6-dev \
    libccfits-dev libcfitsio-dev dpkg-dev libgl-dev
elif [[ "$RT4SVPP_DISTRO" == fedora ]]; then
  dnf install -y \
    gcc-c++ gcc-gfortran make tar gzip file findutils \
    qt6-qtbase-devel qt6-qtsvg-devel \
    CCfits-devel cfitsio-devel rpm-build
else
  echo "Unknown distribution: $RT4SVPP_DISTRO" >&2
  exit 1
fi

# Snapshot of the entire current working tree, including uncommitted changes.
# Avoid importing previous builds or git metadata into the temporary source.
mkdir -p /tmp/rt4svpp-src
cd /project
tar --exclude='./.git' \
    --exclude='./dist' \
    --exclude='./flatpak-build' \
    --exclude='./build-flatpak' \
    --exclude='./flatpak-repo' \
    --exclude='./.flatpak-builder' \
    --exclude='./build' \
    --exclude='./*.o' \
    --exclude='./Makefile' \
    --exclude='./rt4sv++' \
    -cf - . | tar -xf - -C /tmp/rt4svpp-src
cd /tmp/rt4svpp-src

printf '\n==> Qt version: '
qmake6 -query QT_VERSION
qmake6 ui_class.pro 'CONFIG+=release'
make -j"$(nproc)"
./rt4sv++ --version
./rt4sv++ --help >/dev/null

STAGE=/tmp/rt4svpp-stage
mkdir -p "$STAGE"
make "INSTALL_ROOT=$STAGE" install
BIN="$STAGE/usr/bin/rt4sv++"
test -x "$BIN" || { echo "Not installed: $BIN" >&2; exit 1; }

# Optional desktop integration, no hard-coded icon resource needed.
mkdir -p "$STAGE/usr/share/applications"
cat > "$STAGE/usr/share/applications/rt4svpp.desktop" <<'DESKTOP'
[Desktop Entry]
Type=Application
Name=RT4SV++
Comment=NCU radio telescope spectra visualizer
Exec=rt4sv++ %F
Icon=applications-science
Terminal=false
Categories=Science;Education;
DESKTOP

if [[ "$RT4SVPP_DISTRO" == ubuntu ]]; then
  # dpkg-shlibdeps inspects the real ELF rather than guessing Qt/CCfits versions.
  mkdir -p debian
  cat > debian/control <<'CONTROL'
Source: rt4svpp
Section: science
Priority: optional
Maintainer: RT4SV++ maintainers <noreply@github.com>
Standards-Version: 4.6.0

Package: rt4svpp
Architecture: any
Description: Radio telescope spectra visualizer
CONTROL
  DEPS="$(dpkg-shlibdeps -O -e"$BIN" | sed -n 's/^shlibs:Depends=//p')"
  if [[ -z "$DEPS" ]]; then echo 'dpkg-shlibdeps returned no dependencies' >&2; exit 1; fi
  mkdir -p "$STAGE/DEBIAN"
  cat > "$STAGE/DEBIAN/control" <<CONTROL
Package: rt4svpp
Version: ${RT4SVPP_VERSION}-1
Section: science
Priority: optional
Architecture: amd64
Maintainer: RT4SV++ maintainers <noreply@github.com>
Depends: $DEPS, qt6-qpa-plugins
Recommends: qt6-wayland
Description: Radio telescope spectra visualizer
 RT4SV++ GUI and CLI for NCU 32-m telescope FITS observations.
CONTROL
  OUTFILE="/out/rt4svpp_${RT4SVPP_VERSION}-1_ubuntu${RT4SVPP_RELEASE}_amd64.deb"
  dpkg-deb --build --root-owner-group "$STAGE" "$OUTFILE"
  dpkg-deb -I "$OUTFILE" | head -35
elif [[ "$RT4SVPP_DISTRO" == fedora ]]; then
  TOP=/tmp/rt4svpp-rpmbuild
  mkdir -p "$TOP"/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
  cp "$BIN" "$TOP/SOURCES/rt4sv++"
  cp "$STAGE/usr/share/applications/rt4svpp.desktop" "$TOP/SOURCES/rt4svpp.desktop"
  cat > "$TOP/SPECS/rt4svpp.spec" <<'SPEC'
%global debug_package %{nil}
Name: rt4svpp
Version: %{_version}
Release: 1%{?dist}
Summary: Radio telescope spectra visualizer
License: GPL-3.0-or-later
URL: https://github.com/dachshund-ncu/rt4svpp
BuildArch: x86_64
Source0: rt4sv++
Source1: rt4svpp.desktop

%description
RT4SV++ GUI and CLI for NCU 32-m telescope FITS observations.

%prep

%build

%install
install -Dm755 %{SOURCE0} %{buildroot}%{_bindir}/rt4sv++
install -Dm644 %{SOURCE1} %{buildroot}%{_datadir}/applications/rt4svpp.desktop

%files
%{_bindir}/rt4sv++
%{_datadir}/applications/rt4svpp.desktop
SPEC
  # RPM permits only numeric, dot-separated Version fields in this workflow.
  rpmbuild -bb "$TOP/SPECS/rt4svpp.spec" \
    --define "_topdir $TOP" \
    --define "_version $RT4SVPP_VERSION"
  find "$TOP/RPMS" -type f -name '*.rpm' -exec cp -v '{}' /out/ \;
  rpm -qp --requires "$TOP"/RPMS/x86_64/*.rpm | head -30
fi
