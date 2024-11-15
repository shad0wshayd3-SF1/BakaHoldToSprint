-- set xmake version
set_xmakever("2.9.4")

-- include local folders
includes("extern/commonlibsf")

-- set project
set_project("BakaHoldToSprint")
set_version("4.1.0")
set_license("GPL-3.0")

-- set defaults
set_arch("x64")
set_languages("c++23")
set_optimize("faster")
set_warnings("allextra", "error")
set_defaultmode("releasedbg")

-- enable lto
set_policy("build.optimization.lto", true)

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- setup targets
target("BakaHoldToSprint")
    -- bind local dependencies
    add_deps("commonlibsf")

    -- add commonlibsf plugin
    add_rules("commonlibsf.plugin", {
        name = "BakaHoldToSprint",
        author = "shad0wshayd3"
    })

    -- add source files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/PCH.h")

    -- add extra files
    add_extrafiles(".clang-format")
