workspace "FizzGen"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	outDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "FizzGen"
		location "FizzGen"
		kind "sharedlib"
		language "C++"

		targetdir ("bin/" .. outDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outDir .. "/%{prj.name}")
		buildoptions "/utf-8"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include"
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
