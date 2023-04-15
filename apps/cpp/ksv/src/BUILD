load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "ksv",
    srcs = glob(["*.cpp", "*.h"]),
    deps = [
        "//lib/logger:logger",
        "//lib/rapidcsv:rapidcsv",
        "//lib/xmlparse:xmlparse",
        "//lib/boost:boost",
        "//lib/k:klib",
    ],
    defines = [
        "KXVER=3"
    ]
)