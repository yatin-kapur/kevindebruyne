load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "klib",
    srcs = glob(["*.cpp", "*.h"]),
    linkopts = [
        "-lpthread"
    ],
    deps = [
        "//lib/logger:logger",
        "//lib/k:k"
    ],
    defines = [
        "KXVER=3"
    ],
    linkstatic=1,
    visibility = ["//visibility:public"]
)