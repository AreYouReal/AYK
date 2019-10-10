workspace "AYK"
	architecture "x64"
	startproject "Sandbox"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "AYK/vendor/GLFW/include"
IncludeDir["Glad"] = "AYK/vendor/Glad/include"
IncludeDir["ImGui"] = "AYK/vendor/imgui"

group "Dependencies"
	include "AYK/vendor/GLFW"
	include "AYK/vendor/Glad"
	include "AYK/vendor/imgui"

group ""

project "AYK"
	location "AYK"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "aykpch.h"
	pchsource "AYK/src/aykpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include;",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"AYK_PLATFORM_WINDOWS",
			"AYK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AYK_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "AYK_DIST"
		runtime "Release"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"AYK/vendor/spdlog/include",
		"AYK/src"
	}

	links{
		"AYK"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"

		defines {
			"AYK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AYK_RELEASE" 
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "AYK_DIST"
		runtime "Release"
		optimize "On"