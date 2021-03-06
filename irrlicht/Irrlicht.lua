-- A project defines one build target
project "Irrlicht"
--kind "WindowedApp"
--kind "ConsoleApp"
kind "SharedLib"
--kind "StaticLib"
language "C++"
files {
    "include/*.h",
    "src/*.cpp", 
    "src/*.h",
}
defines {
    "IRRLICHT_EXPORTS",
}
linkoptions {
}
links {
    "aesGladman",
    "freetype",
    "winmm", "gdi32", "shlwapi", "vfw32", "imm32",
    "png", "jpeg", "bzip2", "lzma", "z",
    "opengl32",
}

