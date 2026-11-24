#!/usr/bin/env bash
set -Eeuo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="$ROOT/dist"
VERSION="${RT4SVPP_VERSION:-1.48}"

usage() {
  cat <<'HELP'
Usage:
  ./packaging/build.sh ubuntu 22.04
  ./packaging/build.sh ubuntu 24.04
  ./packaging/build.sh ubuntu 26.04
  ./packaging/build.sh fedora 44
  ./packaging/build.sh fedora 45
  ./packaging/build.sh all

Optional: RT4SVPP_VERSION=1.48 ./packaging/build.sh ubuntu 24.04
Outputs: dist/*.deb and dist/*.rpm
HELP
}

if [[ $# -eq 1 && "$1" == all ]]; then
  for target in 'ubuntu 22.04' 'ubuntu 24.04' 'ubuntu 26.04' 'fedora 44' 'fedora 45'; do
    read -r distro release <<< "$target"
    "$0" "$distro" "$release"
  done
  exit 0
fi

if [[ $# -ne 2 ]]; then usage; exit 2; fi
DISTRO="$1"
RELEASE="$2"
case "$DISTRO:$RELEASE" in
  ubuntu:22.04|ubuntu:24.04|ubuntu:26.04|fedora:44|fedora:45) ;;
  *) echo "Unsupported build target: $DISTRO $RELEASE" >&2; usage; exit 2 ;;
esac

if [[ "$(uname -m)" != x86_64 ]]; then
  echo 'This initial packaging setup targets x86_64 hosts only.' >&2
  exit 1
fi
command -v podman >/dev/null || { echo 'Install Podman first: sudo dnf install podman' >&2; exit 1; }
[[ -f "$ROOT/ui_class.pro" ]] || { echo "Missing $ROOT/ui_class.pro" >&2; exit 1; }
[[ -f "$ROOT/packaging/container-build.sh" ]] || { echo 'Missing packaging/container-build.sh' >&2; exit 1; }

mkdir -p "$OUT"
IMAGE="$DISTRO:$RELEASE"
echo "==> Building RT4SV++ $VERSION on $IMAGE"

# The source mount is read-only. We disable SELinux container labeling instead
# of relabeling the developer's working tree with :Z.
podman run --rm \
  --security-opt label=disable \
  --mount "type=bind,src=$ROOT,dst=/project,ro=true" \
  --mount "type=bind,src=$OUT,dst=/out" \
  --env "RT4SVPP_VERSION=$VERSION" \
  --env "RT4SVPP_DISTRO=$DISTRO" \
  --env "RT4SVPP_RELEASE=$RELEASE" \
  "$IMAGE" \
  bash /project/packaging/container-build.sh

echo "==> Finished. Packages: $OUT"
