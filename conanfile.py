from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration
from conan.tools.build import cross_building
from conan.tools.files import copy
import os

required_conan_version = ">=1.43.0"


class LibgodConan(ConanFile):
    name = "libgod"
    version = "1.1.0"
    description = "Global Optimization Data Library"
    license = "BSD-3-Clause"
    url = "https://github.com/bmstu-rk6/libgod"
    homepage = "https://github.com/bmstu-rk6/libgod"
    topics = ("math", "optimization")

    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_docs": [True, False],
        "with_testing": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_docs": False,
        "with_testing": True,
    }

    exports_sources = "*"

    generators = "cmake", "cmake_find_package", "cmake_find_package_multi"

    @property
    def _build_subfolder(self):
        return "build_subfolder"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            del self.options.fPIC

    def requirements(self):
        self.requires("boost/1.79.0")
        if self.options.with_testing:
            self.requires("gtest/1.12.1")

    def build_requirements(self):
        self.build_requires("asn1c/0.9.28")
        if self.options.with_docs:
            self.build_requires("doxygen/1.9.4")

    def _configure_cmake(self, parallel):
        cmake = CMake(self, parallel=parallel)
        cmake.definitions["BUILD_DOCUMENTATION"] = self.options.with_docs
        cmake.definitions["BUILD_TESTING"] = self.options.with_testing

        cmake.definitions["ASN1C_EXECUTABLE"] = "asn1c"
        cmake.definitions["ASN1C_SUPPORT_PATH"] = self.deps_env_info["asn1c"].SUPPORT_PATH

        cmake.configure(source_folder=self.source_folder, build_folder=self._build_subfolder)
        return cmake

    def build(self):
        cmake = self._configure_cmake(parallel=True)
        cmake.build()
        if self.options.with_testing:
            if self.settings.os == 'Macos':
                copy(self,
                     "*.dylib",
                     src=os.path.join(self.build_folder, self._build_subfolder, "lib"),
                     dst=os.path.join(self.build_folder, self._build_subfolder, "test"),
                     keep_path=False)
            else:
                copy(self,
                     "*.so*",
                     src=os.path.join(self.build_folder, self._build_subfolder, "lib"),
                     dst=os.path.join(self.build_folder, self._build_subfolder, "test"),
                     keep_path=False)

        if self.options.with_testing:
            # test require non-parallel execution
            cmake = self._configure_cmake(parallel=False)
            cmake.test()

    def package(self):
        cmake = self._configure_cmake(parallel=True)
        cmake.install()

        self.copy("LICENSE.txt", src='.', dst="licenses")
        tools.rmdir(os.path.join(self.package_folder, "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "cmake"))
        tools.rmdir(os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "libgod")
        self.cpp_info.set_property("cmake_target_name", "libgod")
        self.cpp_info.set_property("pkg_config_name", "god")
        self.cpp_info.libs = tools.collect_libs(self)
        if self.settings.os in ["Linux", "FreeBSD"]:
            self.cpp_info.system_libs = ["m"]
        self.cpp_info.includedirs.append(os.path.join("include", "libgod"))

