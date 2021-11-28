workspace "AYK"
	architecture "x64"
	startproject "AYK-Editor"
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
IncludeDir["glm"] = "AYK/vendor/glm"
IncludeDir["stb_image"] = "AYK/vendor/stb_image"
IncludeDir["entt"] = "AYK/vendor/entt"

group "Dependencies"
	include "AYK/vendor/GLFW"
	include "AYK/vendor/Glad"
	include "AYK/vendor/imgui"

project "AYK"
	location "AYK"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "aykpch.h"
	pchsource "AYK/src/aykpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include;",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"AYK_PLATFORM_WINDOWS",
			"AYK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AYK_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "AYK_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"AYK/vendor/spdlog/include",
		"AYK/src",
		"AYK/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links{
		"AYK"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"AYK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AYK_RELEASE" 
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AYK_DIST"
		runtime "Release"
		optimize "on"


project "AYKEditor"
	location "AYKEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"AYK/vendor/spdlog/include",
		"AYK/src",
		"AYK/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links{
		"AYK"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"AYK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AYK_RELEASE" 
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AYK_DIST"
		runtime "Release"
		optimize "on"
