rem Run this from your vcpkg root
rem We use a renamed version of this file
vcpkg install mpir:x86-windows-static mpir:x64-windows-static
vcpkg export mpir:x86-windows-static mpir:x64-windows-static --zip
