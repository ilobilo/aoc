add_rules("plugin.compile_commands.autoupdate", { outputdir = ".vscode" })

set_policy("run.autobuild", true)
set_warnings("all", "error")
set_languages("c++23")

target("1a")
    set_kind("binary")
    add_files("1a/main.cpp")
    set_rundir("1a")

target("1b")
    set_kind("binary")
    add_files("1b/main.cpp")
    set_rundir("1b")

target("2a")
    set_kind("binary")
    add_files("2a/main.cpp")
    set_rundir("2a")

target("2b")
    set_kind("binary")
    add_files("2b/main.cpp")
    set_rundir("2b")

target("3a")
    set_kind("binary")
    add_files("3a/main.cpp")
    set_rundir("3a")

target("3b")
    set_kind("binary")
    add_files("3b/main.cpp")
    set_rundir("3b")

target("4")
    set_kind("binary")
    add_files("4/main.cpp")
    set_rundir("4")

target("5")
    set_kind("binary")
    add_files("5/main.cpp")
    set_rundir("5")