{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # Define environment variables (if necessary)
  shellHook = ''
    export MANPATH=${pkgs.man-pages}/share/man:${pkgs.man-pages-posix}/share/man:${pkgs.gcc.man}/share/man:${pkgs.valgrind.man}/share/man:${pkgs.xorg.libX11.man}/share/man:${pkgs.xorg.libXext.man}/share/man:${pkgs.minilibx.man}/share/man:$MANPATH
  '';

  # Packages
  buildInputs = with pkgs; [
    ###### Compilers / Headers #####
    clang
    clang-tools
    gcc
    glibc.dev
    libcxx
    libcxx.dev
    ################################
    ## Project-Specific Packages ###
    minilibx
    xorg.libX11.dev
    xorg.libXext.dev
    ################################
    ############ Other #############
    man-pages
    man-pages-posix
    valgrind.dev
    norminette
    ################################
    ########### Man Pages ##########
    gcc.man
    minilibx.man
    valgrind.man
    xorg.libX11.man
    xorg.libXext.man
    ################################
    ######## Neovim Packages #######
    bottom
    gdu
    neovim
    nodejs
    python3
    ripgrep
    tree-sitter
    unzip
    wl-clipboard
    ################################
  ];
}
