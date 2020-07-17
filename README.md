# get_hdf5_version
A small C program which prints the version of HDF5 for use in preprocessing non-C source code.

The sole purporse of this program is to have an easy way of getting the version number
of the HDF5 library for use in preprocessing of e.g. Fortran source code.
This is because HDF5 does not provide files containing the HDF5 version number _as preprocessor macros_
which can be directly included in the Fortran source code.
When executed, this program prints a preprocessor macro, which then can be included
in the calls to e.g. `gfortran` inside the Makefile.

The corresponding macros returned, if no parameters are given, are:
* `H5_VERS_1_8`  for HDF5 1.8,
* `H5_VERS_1_10` for HDF5 1.10,
* `H5_VERS_1_12` for HDF5 1.12 etc. (you probably got the idea by now...).

If you only require the major or only the minor version number,
specify `--major`, `--minor`, `--release` or `--subrelease` on the command line:
* `get_hdf5_version --major` gives e.g.  1 for HDF5 1.12.0-1479016456
* `get_hdf5_version --minor` gives e.g. 12 for HDF5 1.12.0-1479016456
* `get_hdf5_version --release` gives e.g. 0 for HDF5 1.12.0-1479016456
* `get_hdf5_version --subrelease` gives e.g. 1479016456 for HDF5 1.12.0-1479016456

## Useage in a Makefile
Suppose you would like to use this utility in a `Makefile` for a Fortran program.

First you have to use `get_hdf5_version` to declare the HDF5 version macros:

```make
H5_VERS_MAJOR=$(shell get_hdf5_version --major)
H5_VERS_MINOR=$(shell get_hdf5_version --minor)
```

Hand over the macros to your compiler:

```make
myprog: myprog.f90
  gfortran -DH5_VERS_MINOR=$(H5_VERS_MINOR) -o myprog myprog.f90
```


Then, in your sources, you can use them just as in C:

```fortran
#if H5_VERS_MINOR<11
!> dummy argument for outputs of h5lget_info_f for HDF5 1.10
  integer(haddr_t)               :: dummy_addr_token
#else
!> dummy argument for outputs of h5lget_info_f for HDF5 1.12
  type(h5o_token_t_f)            :: dummy_addr_token
#endif

... some more code ...

  call h5lget_info_f(myGrp, "aDataset", dummy_cset, dummy_corder, dummy_f_corder_valid, dummy_link_type, & 
&                            dummy_addr_token, dummy_val_size, hdfier)
```

