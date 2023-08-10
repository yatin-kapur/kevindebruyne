load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "quarto",
    srcs = glob(["*.cpp", "*.h"]),
    deps = [
        "//lib/logger:logger",
        "//lib/boost:boost",
    ],
    copts = [
        "-std=c++20"
    ]
)