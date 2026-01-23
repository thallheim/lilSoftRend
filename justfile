set windows-shell := ["C:\\Program Files\\Git\\bin\\sh.exe","-c"]

_default:
    # @just _fuzzy-list
    @just --list --unsorted
    
# This list, but with fzf \o/
@_fuzzy-list:
    if ! which fzf > /dev/null 2>&1; then \
    echo "FATAL: fzf not installed." && exit 1; fi
    just --unsorted --choose \
    --chooser "fzf --no-multi --min-height=10 --height=~25 --border=sharp"

# Run CMake project config/dep. installs
alias conf := configure
alias c := configure
[group("configure build"), doc("Configure for Ninja")]
@configure *ARGS:
    cmake -B build -S . -G "Ninja Multi-Config" {{ARGS}}

alias b := build
[group("build"), doc("Build - debug config")]
@build *ARGS:
    cmake --build build --config "Debug" {{ARGS}}

alias br := build-release
[group("build"), doc("Build - release config")]
@build-release *ARGS:
    cmake --build build --config "Release" {{ARGS}}

alias purge := purge-build-artefacts
[group("Clean-up"), doc("Delete build artefacts")]
@purge-build-artefacts:
    echo "Purge build artefacts..."
    rm -rf ./build

alias purge-all := purge-all-artefacts
[group("Clean-up"), doc("Delete CMake cache & all artefacts")]
@purge-all-artefacts:
    echo "Purge cache & all artefacts..."
    rm -rf ./.cache ./build ./vendor
