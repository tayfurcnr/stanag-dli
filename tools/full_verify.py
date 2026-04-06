#!/usr/bin/env python3
import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT / ".verify-build"
INSTALL_DIR = ROOT / ".verify-install"
CONSUMER_BUILD_DIR = ROOT / ".verify-consumer-build"
DIST_DIR = ROOT / ".verify-dist"


def run(cmd, *, env=None, cwd=ROOT):
    print(f"[verify] {' '.join(cmd)}")
    subprocess.run(cmd, cwd=cwd, env=env, check=True)


def assert_no_installed_sources():
    include_root = INSTALL_DIR / "include" / "dli"
    unexpected = sorted(str(path.relative_to(include_root)) for path in include_root.rglob("*.cpp"))
    if unexpected:
        raise RuntimeError(f"installed include tree contains source files: {', '.join(unexpected)}")


def reset_dir(path: Path):
    if path.exists():
        shutil.rmtree(path)


def main():
    parser = argparse.ArgumentParser(description="Generate artifacts and verify the DLI SDK.")
    parser.add_argument("--skip-generate", action="store_true", help="Skip generator steps.")
    parser.add_argument("--skip-cpp", action="store_true", help="Skip C++ configure/build/test.")
    parser.add_argument("--skip-package-smoke", action="store_true", help="Skip install and find_package smoke test.")
    parser.add_argument("--skip-python-package-smoke", action="store_true", help="Skip Python wheel build smoke test.")
    parser.add_argument("--skip-python", action="store_true", help="Skip Python pytest suite.")
    parser.add_argument("--host", action="store_true", help="Run host-only integration tests as well.")
    args = parser.parse_args()

    env = os.environ.copy()
    python_path = str(ROOT / "idl" / "python")
    env["PYTHONPATH"] = python_path + os.pathsep + env.get("PYTHONPATH", "")
    env.setdefault("CCACHE_DISABLE", "1")
    env.setdefault("CXX", "/usr/bin/g++")

    if not args.skip_generate:
        run([sys.executable, "generator/dli_gen.py"], env=env)
        run([sys.executable, "generator/dli_gen_python.py"], env=env)
        run([sys.executable, "generator/dissector_gen.py"], env=env)
        run([sys.executable, "generator/ics_gen.py"], env=env)
        run([sys.executable, "generator/profile_gen.py"], env=env)

    if not args.skip_cpp:
        reset_dir(BUILD_DIR)
        reset_dir(INSTALL_DIR)
        reset_dir(CONSUMER_BUILD_DIR)
        reset_dir(DIST_DIR)
        run(
            [
                "cmake",
                "-S",
                str(ROOT),
                "-B",
                str(BUILD_DIR),
                f"-DCMAKE_CXX_COMPILER={env['CXX']}",
            ]
        )
        run(["cmake", "--build", str(BUILD_DIR)])
        if not args.skip_package_smoke:
            run(["cmake", "--install", str(BUILD_DIR), "--prefix", str(INSTALL_DIR)])
            assert_no_installed_sources()
            run(
                [
                    "cmake",
                    "-S",
                    str(ROOT / "tools" / "find_package_smoke"),
                    "-B",
                    str(CONSUMER_BUILD_DIR),
                    f"-DCMAKE_PREFIX_PATH={INSTALL_DIR}",
                    f"-DCMAKE_CXX_COMPILER={env['CXX']}",
                ]
            )
            run(["cmake", "--build", str(CONSUMER_BUILD_DIR)])
        ctest_cmd = ["ctest", "--output-on-failure"]
        if not args.host:
            ctest_cmd.extend(["-LE", "host_only"])
        run(ctest_cmd, env=env, cwd=BUILD_DIR)

    if not args.skip_python:
        run([sys.executable, "-m", "pytest", "-q"], env=env)

    if not args.skip_python_package_smoke:
        DIST_DIR.mkdir(parents=True, exist_ok=True)
        run(
            [
                sys.executable,
                "-m",
                "pip",
                "wheel",
                ".",
                "--no-deps",
                "--no-build-isolation",
                "-w",
                str(DIST_DIR),
            ],
            env=env,
        )

    if args.host:
        run([sys.executable, "idl/python/tests/verify_python_dli.py"], env=env)


if __name__ == "__main__":
    main()
