#!/usr/bin/env bash
GRDIR=$(julia -e 'using Plots; println(ENV["GRDIR"])' | awk -F'/src' '{print $1}')
cat <<EOF > julia-fix-gksqt.nix
with import <nixpkgs> {};
let
  libPath = lib.makeLibraryPath [
    stdenv.cc.cc.lib qt5.qtbase qt5Full libGL ];
in
  pkgs.stdenv.mkDerivation {
    name = "julia-fix-gksqt";
    shellHook = ''
      export QT_QPA_PLATFORM_PLUGIN_PATH="\${qt5.qtbase.bin}/lib/qt-\${qt5.qtbase.version}/plugins"
      chmod +wx $GRDIR/bin/gksqt
      \${patchelf}/bin/patchelf \\
        --set-interpreter \${glibc}/lib/ld-linux-x86-64.so.2 \\
        --set-rpath "\${libPath}" \\
        $GRDIR/bin/gksqt
      ldd $GRDIR/bin/gksqt \\
        | grep -q "not found" || \\
        echo '../gksqt is patched'
    '';
  }
EOF
