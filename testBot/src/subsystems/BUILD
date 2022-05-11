cc_library(
    name = "subsystems", 
    srcs = glob(["*/*.cpp"]),
    hdrs = glob(["*/*.hpp"]),
    visibility = ["//visibility:public"],
    deps = [
        "@bazelrio//libraries/cpp/wpilib/wpilibc",
        "@bazelrio//libraries/cpp/ctre/phoenix",
        "@bazelrio//libraries/cpp/rev/revlib",
        "@firelib",
    ],
)