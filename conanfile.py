from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class BiliQtConan(ConanFile):
    name = "biliqt"
    version = "0.1.0"

    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("qt/6.8.3")

        self.requires("oatpp/1.3.0")
        self.requires("oatpp-openssl/1.3.0")

        self.requires("protobuf/6.32.1")

    def configure(self):
        if "qt" in self.dependencies:
            self.options["qt/*"].compiler.cppstd = "gnu20"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_CXX_EXTENSIONS"] = True
        tc.generate()
