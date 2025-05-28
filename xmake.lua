-- set xmake version
set_xmakever("2.9.4")

-- include local folders
includes("lib/commonlibsf")

-- set project
set_project("BakaHoldToSprint")
set_version("6.0.0")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- enable lto
set_policy("build.optimization.lto", true)
set_policy("package.requires_lock", true)

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
