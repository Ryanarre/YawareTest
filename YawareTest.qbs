import qbs.FileInfo

QtApplication {
    Depends { name: "Qt"; submodules: ['widgets', 'gui', 'sql'] }
    files: [
        "dbmanager.cpp",
        "dbmanager.h",
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
        "screenrow.h",
    ]

    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
