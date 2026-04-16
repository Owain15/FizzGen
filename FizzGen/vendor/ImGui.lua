project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "ImGui/imconfig.h",
        "ImGui/imgui.h",
        "ImGui/imgui.cpp",
        "ImGui/imgui_draw.cpp",
        "ImGui/imgui_internal.h",
        "ImGui/imgui_tables.cpp",
        "ImGui/imgui_widgets.cpp",
        "ImGui/imstb_rectpack.h",
        "ImGui/imstb_textedit.h",
        "ImGui/imstb_truetype.h",
        "ImGui/imgui_demo.cpp",
        "ImGui/backends/imgui_impl_opengl3.cpp",
        "ImGui/backends/imgui_impl_opengl3.h",
        "ImGui/backends/imgui_impl_opengl3_loader.h",
        "ImGui/backends/imgui_impl_win32.cpp",
        "ImGui/backends/imgui_impl_win32.h",
    }

    includedirs {
        "ImGui",
        "ImGui/backends"
    }

    filter "platforms:ARM64"
        defines { "IMGUI_IMPL_OPENGL_ES3" }
        includedirs { "%{wks.location}/FizzGen/vendor/ANGLE/ARM64/include" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        runtime "Release"
        optimize "on"
