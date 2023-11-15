import qbs.FileInfo

QtApplication {
    Depends { name: "Qt"; submodules: ['widgets', 'gui'] }
    files: [
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
    ]

    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
