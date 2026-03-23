workspace "FizzGen"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "FizzGen/vendor/GLFW/include"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "FizzGen/vendor/GLFW"
	
	

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
			"%{IncludeDir.GLFW}"
		}

		links {
			"GLFW",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"
			
			defines {
				"FG_PLATFORM_WINDOWS",
				"FG_BUILD_DLL"
			}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outDir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "FG_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "FG_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "FG_DIST"
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
		staticruntime "On"
		systemversion "latest"
		defines {
			"FG_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "FG_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "FG_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "FG_DIST"
		optimize "On"
