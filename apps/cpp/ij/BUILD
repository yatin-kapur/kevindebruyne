load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "ij",
    srcs = glob(["*.cpp", "*.h"]),
    deps = [
        "//lib/logger:logger",
        "//lib/kdb:klib",
    ],
    defines = [
        "KXVER=3"
    ],
    copts = [
        "-std=c++20"
    ]
)