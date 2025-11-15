from conan import ConanFile

class BiliQtConan(ConanFile):
    name = "biliqt"
    version = "0.1.0"

    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps", "CMakeToolchain", "CMakeConfigDeps"

    def requirements(self):
        self.requires("qt/6.8.3")

        self.requires("oatpp/1.3.0")
        self.requires("oatpp-openssl/1.3.0")

        self.requires("protobuf/6.32.1")

    def configure(self):
        if "qt" in self.dependencies:
            self.options["qt/*"].compiler.cppstd = "gnu20"
