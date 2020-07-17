#include <stdio.h>
#include <string.h>

#include <H5public.h>

#ifndef H5_VERS_MAJOR
#error H5_VERS_MAJOR not defined
#endif

#ifndef H5_VERS_MINOR
#error H5_VERS_MINOR not defined
#endif

#ifndef H5_VERS_RELEASE
#error H5_VERS_RELEASE not defined
#endif

#ifndef H5_VERS_SUBRELEASE
#error H5_VERS_SUBRELEASE not defined
#endif

/**
 * The sole purporse of this program is to have an easy way of getting the version number
 * of the HDF5 library for use in preprocessing of e.g. Fortran source code.
 * This is because HDF5 does not provide files containing the HDF5 version number _as preprocessor macros_
 * which can be directly included in the Fortran source code.
 * When executed, this program prints a preprocessor macro, which then can be included
 * in the calls to e.g. gfortran inside the Makefile.
 *
 * The corresponding macros returned, if no parameters are given, are:
 * H5_VERS_1_8  for HDF5 1.8
 * H5_VERS_1_10 for HDF5 1.10
 * H5_VERS_1_12 for HDF5 1.12
 *
 * If you only require the major or only the minor version number,
 * specify --major or --minor on the command line:
 * `argv[0] --major` gives e.g.  1 for HDF5 1.12
 * `argv[0] --minor` gives e.g. 12 for HDF5 1.12
 */

void print_help(char* argv0) {
	if (!strcmp(H5_VERS_SUBRELEASE, "")) {
		printf("Get the version number of the HDF5 library this tool was compiled against (%d.%d.%d).\n",
		       H5_VERS_MAJOR, H5_VERS_MINOR, H5_VERS_RELEASE);
	} else {
		printf("Get the version number of the HDF5 library this tool was compiled against (%d.%d.%d-%s).\n",
		       H5_VERS_MAJOR, H5_VERS_MINOR, H5_VERS_RELEASE, H5_VERS_SUBRELEASE);
	}
	printf("\
useage: %s [--minor | --major | --release | --subrelease | --macro]\n\
  --major      : return the major      version (%d) of the installed HDF5 version\n\
  --minor      : return the minor      version (%d) of the installed HDF5 version\n\
  --release    : return the release    version (%d) of the installed HDF5 version\n\
  --subrelease : return the subrelease version (%s) of the installed HDF5 version\n\
  --macro instructs the program to return a macro describing the version of HDF5, e.g.\n\
          H5_VERS_1_8  for HDF5 1.8\n\
          H5_VERS_1_10 for HDF5 1.10\n\
          H5_VERS_1_12 for HDF5 1.12 etc. (you probably got the idea by now...).\n\
    Only the major and minor version numbers are returned, since there should be no\n\
    incompatible API changes in between different version of release or subrelease.\n\
", argv0, H5_VERS_MAJOR, H5_VERS_MINOR, H5_VERS_RELEASE, H5_VERS_SUBRELEASE);
}

int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "--major")) {
		printf("%d", H5_VERS_MAJOR);
	} else if (argc == 2 && !strcmp(argv[1], "--minor")) {
		printf("%d", H5_VERS_MINOR);
	} else if (argc == 2 && !strcmp(argv[1], "--release")) {
		printf("%d", H5_VERS_RELEASE);
	} else if (argc == 2 && !strcmp(argv[1], "--subrelease")) {
		printf(H5_VERS_SUBRELEASE);
	}  else if (argc == 2 && !strcmp(argv[1], "--macro")) {
		printf("H5_VERS_%d_%d", H5_VERS_MAJOR, H5_VERS_MINOR);
	} else {
		if (argc == 1) {
			print_help(argv[0]);
		} else {
			print_help("get_hdf5_version");
		}
	}
	return 0;
}

