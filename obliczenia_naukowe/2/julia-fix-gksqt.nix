with import <nixpkgs> {};
let
  libPath = lib.makeLibraryPath [
    stdenv.cc.cc.lib qt5.qtbase qt5Full libGL ];
in
  pkgs.stdenv.mkDerivation {
    name = "julia-fix-gksqt";
    shellHook = ''
      export QT_QPA_PLATFORM_PLUGIN_PATH="${qt5.qtbase.bin}/lib/qt-${qt5.qtbase.version}/plugins"
      chmod +wx /home/felix/.julia/artifacts/231c36cbc48a78caf7818ee7f4cd260eb3d642e3/bin/gksqt
      ${patchelf}/bin/patchelf \
        --set-interpreter ${glibc}/lib/ld-linux-x86-64.so.2 \
        --set-rpath "${libPath}" \
        /home/felix/.julia/artifacts/231c36cbc48a78caf7818ee7f4cd260eb3d642e3/bin/gksqt
      ldd /home/felix/.julia/artifacts/231c36cbc48a78caf7818ee7f4cd260eb3d642e3/bin/gksqt \
        | grep -q "not found" || \
        echo '../gksqt is patched'
    '';
  }
