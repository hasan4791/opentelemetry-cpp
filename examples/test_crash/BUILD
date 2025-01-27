cc_binary(
    name = "test",
    srcs = [
        "main.cc",
    ],
    tags = ["test_crash"],
    deps = [
        "//api",
        "//examples/common/foo_library:common_foo_library",
        "//exporters/jaeger:opentelemetry_exporter_jaeger_trace",
        "//sdk/src/trace",
    ],
)
