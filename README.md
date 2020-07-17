# get_hdf5_version
A small C program which prints the version of HDF5 for use in preprocessing non-C source code.

The sole purporse of this program is to have an easy way of getting the version number
of the HDF5 library for use in preprocessing of e.g. Fortran source code.
This is because HDF5 does not provide files containing the HDF5 version number _as preprocessor macros_
which can be directly included in the Fortran source code.
When executed, this program prints a preprocessor macro, which then can be included
in the calls to e.g. gfortran inside the Makefile.

The corresponding macros returned, if no parameters are given, are:
* `H5_VERS_1_8`  for HDF5 1.8,
* `H5_VERS_1_10` for HDF5 1.10,
* `H5_VERS_1_12` for HDF5 1.12 etc. (you probably got the idea by now...).

If you only require the major or only the minor version number,
specify `--major`, `--minor`, `--release` or `--subrelease` on the command line:
* `argv[0] --major` gives e.g.  1 for HDF5 1.12.0-1479016456
* `argv[0] --minor` gives e.g. 12 for HDF5 1.12.0-1479016456
* `argv[0] --release` gives e.g. 0 for HDF5 1.12.0-1479016456
* `argv[0] --subrelease` gives e.g. 1479016456 for HDF5 1.12.0-1479016456
