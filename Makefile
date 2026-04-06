PYTHON ?= python3
CMAKE ?= cmake
CTEST ?= ctest
BUILD_DIR ?= build

.PHONY: generate verify verify-host python-test cpp-test configure

generate:
	$(PYTHON) generator/dli_gen.py
	$(PYTHON) generator/dli_gen_python.py
	$(PYTHON) generator/dissector_gen.py
	$(PYTHON) generator/ics_gen.py
	$(PYTHON) generator/profile_gen.py

configure:
	$(CMAKE) -S . -B $(BUILD_DIR)

python-test:
	PYTHONPATH=idl/python $(PYTHON) -m pytest -q

cpp-test: configure
	$(CTEST) --test-dir $(BUILD_DIR) --output-on-failure

verify:
	$(PYTHON) tools/full_verify.py

verify-host:
	$(PYTHON) tools/full_verify.py --host
