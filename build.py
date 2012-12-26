import sys
import os

from os.path import basename, exists, getmtime, isfile, join
from subprocess import call

be_verbose = False #-v, --verbose

bin_dir = "bin"

#Relative to build-directory, NOT recursive.
include_dirs = ["inc"]
source_dirs = ["src"]

COMPILER = "gcc"
CFLAGS = "-O2 -Wall -Wextra"
INCFLAGS = "-I" + " -I".join(include_dirs)

def build_cprimes_header():
	"""Combines header files into one, distributable header."""
	build_log("\nBuilding primes.h")
	try:
		primes_header = open("primes.h.tmp", mode = "w")
	except e as IOError:
		build_log("Error creating primes.h.\n\tStopping.", always_print = True)
		return False
	headers = set()
	primes_header.write("#pragma once\n")
	for include_dir in include_dirs:
		for header in os.listdir(include_dir):
			headers.update(get_header_deps(join(include_dir, header)))
			with open(join(include_dir, header)) as f:
				primes_header.write("\n//{}\n".format(header))
				for line in f:
					if any([line.startswith(phrase) for phrase in ["#include", "#pragma once", "START_EXTERN_C", "END_EXTERN_C", "//", "\n"]]):
						continue
					primes_header.write(line)
			primes_header.write("\n")
	primes_header.close()
	if exists("primes.h"):
		os.remove("primes.h")
	os.rename("primes.h.tmp", "primes.h")
	return True


def compiler_cmd(source):
	target = get_target(source)
	return "gcc -o {} {} {} {} ".format(target, CFLAGS, INCFLAGS, source)

def main():
	global be_verbose
	if "-v" in sys.argv:
		be_verbose = True
	dependancies = build_dep_tree()
	for source in dependancies:
		deps = dependancies[source]
		target = get_target(source)
		#build_log("{} -> {}.\n\tDepends on: {}\n\tRebuild? {}\n".format(source, target, deps, needs_rebuild(target, deps)))
		if needs_rebuild(target, deps):
			pass #rebuild it!
	build_cprimes_header()

#Could I do a "verbosity level" sort of deal?
def build_log(*args, always_print = False):
	if always_print or be_verbose:
		print(*args)

def get_header_deps(filename, check_sys_headers = True):
	"""
	Finds the header file dependancies of a C source or header file by analyzing the #includes
	Returns a list of header files which filename depends on. Does not find the file in the filesystem, so the relative directory needs to be passed to the compiler. (e.g. -I../inc)
	Anything in <> is ignored as a system include if check_sys_headers is False
	"""
	build_log("Checking {} for header dependancies.".format(filename))
	if filename[-2:] not in [".c", ".h"]:
		raise ValueError("{} is not a C source or header file.")
	header_deps = []
	try:
		with open(filename, "r") as file:
			for line in file:
				line = line.strip()
				if line.startswith("#include"):
					header = line.replace("#include", "").strip()
					if not check_sys_headers and (header[0], header[-1]) == ('<', '>'):
						build_log("\tIgnoring system include {}".format(header))
					else:
						for dir_name in include_dirs:
							full_header = join(dir_name, header[1:-1])
							if exists(full_header):
								build_log("\tFound header file dependancy {} in {}".format(full_header, filename))
								header_deps.append(full_header)
	except IOError as e:
		pass
	count = len(header_deps)
	if count != 1:
		build_log("Found {} dependancies in {}\n".format(count, filename))
	else:
		build_log("Found {} dependancy in {}\n".format(count, filename))
	return header_deps

def get_target(source):
	target = basename(source).replace(".c", ".o")
	return join(bin_dir, target)

def source_exists(source):
	for dir_name in source_dirs:
		if source in os.listdir(dir_name) and isfile(join(dir_name, source)):
			return True
	return False

def get_source_deps(source):
	header_deps = get_header_deps(source, check_sys_headers = False)
	source_deps = []
	for header in header_deps:
		header_source = basename(header).replace(".c", ".h")
		if source_exists(header_source) and header_source != source:
			source_deps.append(get_target(header_source))
	return source_deps + header_deps

def build_dep_tree():
	dependancies = {}
	for dir_name in source_dirs:
		for filename in os.listdir(dir_name):
			deps = get_source_deps(join(dir_name, filename))
			target = get_target(filename)
			source = join(dir_name, filename)
			dependancies[source] = deps
	return dependancies

def needs_rebuild(target, dependancies = []):
	build_log("Checking to see if {} needs to be rebuilt.".format(target))
	if not exists(target):
		build_log("\t{} does not exist and needs to be rebuilt.".format(target))
		return True
	for dep in dependancies:
		if not exists(dep):
			build_log("\t{}'s dependancy {} does not exist.".format(target, dep))
			continue
		if getmtime(dep) > getmtime(target):
			build_log("\t{} has been updated; {} needs to be rebuilt.".format(dep, target))
			return True
	build_log("\tUp to date.\n")
	return False

if __name__ == "__main__":
	main()
