-- Auto-download desktop ANGLE binaries from mmozeiko/build-angle GitHub releases
local angleDir = "FizzGen/vendor/ANGLE"
if not os.isfile(angleDir .. "/ARM64/bin/libEGL.dll") then
    local repo = "mmozeiko/build-angle"
    local archs = { "arm64", "x64" }

    -- Query latest release tag
    print("Querying latest ANGLE release from " .. repo .. "...")
    local tagFile = os.tmpname()
    os.execute('powershell -Command "(Invoke-RestMethod -Uri \'https://api.github.com/repos/' .. repo .. '/releases/latest\').tag_name | Out-File -Encoding ascii \'' .. tagFile .. '\'"')
    local f = io.open(tagFile, "r")
    local tag = f:read("*l"):match("^%s*(.-)%s*$")
    f:close()
    os.remove(tagFile)
    print("Latest ANGLE release: " .. tag)

    for _, arch in ipairs(archs) do
        local destDir = angleDir .. "/" .. string.upper(arch)
        local zipName = "angle-" .. arch .. "-" .. tag .. ".zip"
        local url = "https://github.com/" .. repo .. "/releases/download/" .. tag .. "/" .. zipName
        local tmp = os.tmpname() .. ".zip"
        local extractDir = os.tmpname() .. "_angle_" .. arch

        print("Downloading ANGLE " .. arch .. " from " .. url .. "...")
        os.execute('powershell -Command "Invoke-WebRequest -Uri \'' .. url .. '\' -OutFile \'' .. tmp .. '\'"')

        os.execute('powershell -Command "Expand-Archive -Path \'' .. tmp .. '\' -DestinationPath \'' .. extractDir .. '\' -Force"')

        -- The zip contains angle-{arch}/ with bin/, lib/, include/ subdirs
        local innerDir = extractDir .. "/angle-" .. arch
        os.execute('powershell -Command "New-Item -ItemType Directory -Force -Path \'' .. destDir .. '\'"')
        os.execute('powershell -Command "Copy-Item -Recurse -Force \'' .. innerDir .. '/bin\' \'' .. destDir .. '/\'"')
        os.execute('powershell -Command "Copy-Item -Recurse -Force \'' .. innerDir .. '/lib\' \'' .. destDir .. '/\'"')
        os.execute('powershell -Command "Copy-Item -Recurse -Force \'' .. innerDir .. '/include\' \'' .. destDir .. '/\'"')

        -- Cleanup
        os.remove(tmp)
        os.execute('powershell -Command "Remove-Item -Recurse -Force \'' .. extractDir .. '\'"')
        print("ANGLE " .. arch .. " binaries installed to " .. destDir)
    end
end

workspace "FizzGen"
	platforms { "x64", "ARM64" }
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	filter "platforms:x64"
		architecture "x64"

	filter "platforms:ARM64"
		architecture "ARM64"

	filter {}

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "FizzGen/vendor/GLFW/include"
	IncludeDir["Glad"] = "FizzGen/vendor/Glad/include"
	IncludeDir["ImGui"] = "FizzGen/vendor/ImGui"
	IncludeDir["ANGLE"] = "FizzGen/vendor/ANGLE/ARM64/include"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "FizzGen/vendor/GLFW"
	include "FizzGen/vendor/Glad"
	include "FizzGen/vendor/ImGui"
	
	

	-- Solution Items appear under the Solution Items node in Visual Studio.
	-- Add any files you want visible in the .sln but not part of a specific project.
		if _G.solutionitems then
		solutionitems {
			"todo.md",
			"persinalNotes.md",
			"premake5.lua",
			".gitignore"
		}
	end


	outDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "FizzGen"
		location "FizzGen"
		kind "sharedlib"
		language "C++"

		targetdir ("bin/" .. outDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outDir .. "/%{prj.name}")
		buildoptions "/utf-8"

		pchheader "fgpch.h"
		pchsource "FizzGen/src/fgpch.cpp"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}"
		}

		links {
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "platforms:x64"
			links { "opengl32.lib" }

		filter "platforms:ARM64"
			defines { "FG_USE_ANGLE", "IMGUI_IMPL_OPENGL_ES3" }
			includedirs { "%{IncludeDir.ANGLE}" }
			links { "libEGL.dll", "libGLESv2.dll" }
			libdirs { "%{prj.name}/vendor/ANGLE/ARM64/lib" }

		filter {}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "Off"
			systemversion "latest"

			defines {
				"FG_PLATFORM_WINDOWS",
				"FG_BUILD_DLL"
			}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outDir .. "/Sandbox")
		}

		filter { "platforms:ARM64", "system:windows" }
			postbuildcommands {
				("{COPY} %{wks.location}/FizzGen/vendor/ANGLE/ARM64/bin/*.dll ../bin/" .. outDir .. "/Sandbox"),
				("{COPY} %{wks.location}/FizzGen/vendor/ANGLE/ARM64/bin/*.dll ../bin/" .. outDir .. "/FizzGen")
			}

		filter {}

		filter "configurations:Debug"
			defines "FG_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "FG_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "FG_DIST"
			runtime "Release"
			optimize "On"






project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outDir .. "/%{prj.name}")
	buildoptions "/utf-8"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"FizzGen/vendor/spdlog/include",
		"FizzGen/src"
	}
	
	links {
		"FizzGen"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"
		defines {
			"FG_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "FG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FG_DIST"
		runtime "Release"
		optimize "On"
