load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "klib",
    srcs = [
        "c.o",
        "k.h",
    ],
    linkopts = [
        "-lpthread"
    ],

    linkstatic=1,
    visibility = ["//visibility:public"]
)