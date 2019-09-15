workspace "AYK"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AYK"
	location "AYK"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include;"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"AYK_PLATFORM_WINDOWS",
			"AYK_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AYK_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "AYK_DIST"
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
		staticruntime "On"
		systemversion "latest"

		defines {
			"AYK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AYK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AYK_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "AYK_DIST"
		symbols "On"