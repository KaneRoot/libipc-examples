const std = @import("std");

fn link_and_install(exe : *std.Build.CompileStep) void {
    const source_file = std.Build.FileSource.relative("./lib/ipc/src/main.zig");
    // var empty : []const std.Build.ModuleDependency = &.{};
    exe.addAnonymousModule("ipc", .{ .source_file = source_file, .dependencies = &.{} });
    exe.linkLibC();

    // This declares intent for the executable to be installed into the
    // standard location when the user invokes the "install" step (the default
    // step when running `zig build`).
    exe.install();
}

// Although this function looks imperative, note that its job is to
// declaratively construct a build graph that will be executed by an external
// runner.
pub fn build(b: *std.Build) void {
    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target = b.standardTargetOptions(.{});

    // Standard optimization options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall. Here we do not
    // set a preferred release mode, allowing the user to decide how to optimize.
    const optimize = b.standardOptimizeOption(.{});

    const ipcd_exe = b.addExecutable(.{
        .name = "ipcd",
        .root_source_file = .{ .path = "src/ipcd.zig" },
        .target = target,
        .optimize = optimize,
    });
    link_and_install(ipcd_exe);

    const tcpd_exe = b.addExecutable(.{
        .name = "tcpd",
        .root_source_file = .{ .path = "src/tcpd.zig" },
        .target = target,
        .optimize = optimize,
    });
    link_and_install(tcpd_exe);

    const pong_exe = b.addExecutable(.{
        .name = "pong",
        .root_source_file = .{ .path = "src/pong.zig" },
        .target = target,
        .optimize = optimize,
    });
    link_and_install(pong_exe);

    const pongd_exe = b.addExecutable(.{
        .name = "pongd",
        .root_source_file = .{ .path = "src/pongd.zig" },
        .target = target,
        .optimize = optimize,
    });
    link_and_install(pongd_exe);
}
