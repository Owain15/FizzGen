-- Auto-download desktop ANGLE binaries from mmozeiko/build-angle GitHub releases
local angleDir = "FizzGen/vendor/ANGLE"
if not os.isfile(angleDir .. "/ARM64/bin/libEGL.dll") then
    local repo = "mmozeiko/build-angle"
    local archs = { "arm64" }

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
	IncludeDir["glm"] = "FizzGen/vendor/glm"
	IncludeDir["stb_image"] = "FizzGen/vendor/stb_image"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "FizzGen/vendor/GLFW"
	include "FizzGen/vendor/Glad"
	include "FizzGen/vendor/ImGui/ImGui.lua"
	
	

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
		kind "staticlib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outDir .. "/%{prj.name}")
		buildoptions "/utf-8"

		pchheader "fgpch.h"
		pchsource "FizzGen/src/fgpch.cpp"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb_image/**.h",
			"%{prj.name}/vendor/stb_image/**.cpp",
			"%{prj.name}/vendor/glm/glm.hpp",
			"%{prj.name}/vendor/glm/glm.inl"
		}

		includedirs{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"
		}

		links {
			"GLFW",
			--"Glad",
			"ImGui",
			--"opengl32.lib"
		}

		filter "platforms:x64"
			links {
				"Glad",
				"opengl32.lib"
			}
			removefiles { "%{prj.name}/src/FizzGen/Platform/ANGLE/**" }

		filter "platforms:ARM64"
			removefiles { "%{prj.name}/src/FizzGen/Platform/OpenGL/**" }

	

		filter "platforms:ARM64"
			defines { "FG_USE_ANGLE", "IMGUI_IMPL_OPENGL_ES3" }
			includedirs { "%{IncludeDir.ANGLE}" }
			--links { "libEGL.dll", "libGLESv2.dll" }
			libdirs { "%{prj.name}/vendor/ANGLE/ARM64/lib", "%{prj.name}/vendor/ANGLE/ARM64/bin" }

	       -- Link import libs so linker can resolve symbols for ARM64
	       links { "Glad" }
	       linkoptions { "libEGL.dll.lib", "libGLESv2.dll.lib" }

		
		filter "system:windows"

			systemversion "latest"

			defines {
				"FG_PLATFORM_WINDOWS"
			}


		filter { "platforms:ARM64", "system:windows" }
	


		filter "configurations:Debug"
			defines "FG_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FG_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "FG_DIST"
			runtime "Release"
			optimize "on"






project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outDir .. "/%{prj.name}")
	buildoptions "/utf-8"
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs {
		"FizzGen/vendor/spdlog/include",
		"FizzGen/src",
		"FizzGen/vendor",
		"%{IncludeDir.glm}"
	}
	
	links {
		"FizzGen"
	}

	filter "platforms:ARM64"
		defines { "FG_USE_ANGLE", "IMGUI_IMPL_OPENGL_ES3" }
		libdirs {
			"FizzGen/vendor/ANGLE/ARM64/lib",
			"FizzGen/vendor/ANGLE/ARM64/bin"
		}
		links { "Glad" }
		linkoptions { "libEGL.dll.lib", "libGLESv2.dll.lib" }
		postbuildcommands {
			'{COPY} "%{wks.location}FizzGen/vendor/ANGLE/ARM64/bin/libEGL.dll" "%{cfg.targetdir}"',
			'{COPY} "%{wks.location}FizzGen/vendor/ANGLE/ARM64/bin/libGLESv2.dll" "%{cfg.targetdir}"',
			'{COPY} "%{wks.location}FizzGen/vendor/ANGLE/ARM64/bin/d3dcompiler_47.dll" "%{cfg.targetdir}"'
		}

	filter "system:windows"

		systemversion "latest"
		defines {
			"FG_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "FG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FG_DIST"
		runtime "Release"
		optimize "on"
