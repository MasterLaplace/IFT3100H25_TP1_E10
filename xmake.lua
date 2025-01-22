add_rules("mode.debug", "mode.release")

add_repositories("package_repo_singleton https://github.com/MasterLaplace/Singleton.git", "package_repo_fixed https://github.com/MasterLaplace/xmake-repo.git")

add_requires("nlohmann_json", "singleton", "libcurl", "libgit2")

set_project("Flakkari")
set_languages("cxx20")

target("flakkari")
    set_kind("binary")
    set_policy("build.warning", true)

    add_packages("nlohmann_json", "singleton", "libcurl", "libgit2")

    add_files("Flakkari/**.cpp")

    add_includedirs("Flakkari/", { public = true })
    add_includedirs("Flakkari/Engine", { public = true })
    add_includedirs("Flakkari/Engine/EntityComponentSystem", { public = true })
    add_includedirs("Flakkari/Engine/EntityComponentSystem/Components", { public = true })
    add_includedirs("Flakkari/Engine/EntityComponentSystem/Systems", { public = true })
    add_includedirs("Flakkari/Engine/Math", { public = true })
    add_includedirs("Flakkari/Logger", { public = true })
    add_includedirs("Flakkari/Network", { public = true })
    add_includedirs("Flakkari/Protocol", { public = true })
    add_includedirs("Flakkari/Server", { public = true })
    add_includedirs("Flakkari/Server/Client", { public = true })
    add_includedirs("Flakkari/Server/Game", { public = true })
    add_includedirs("Flakkari/Server/Internals", { public = true })

    if is_plat("windows") then
        add_syslinks("Iphlpapi")
        -- add_ldflags("/LTCG", {force = true})
    end

    if is_mode("debug") then
        add_defines("DEBUG")
        set_symbols("debug")
        set_optimize("none")
    else
        add_defines("NDEBUG")
        set_optimize("fastest")
    end
