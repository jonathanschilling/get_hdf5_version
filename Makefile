
CC=gcc
INC=-I/usr/include

get_hdf5_version: get_hdf5_version.c
	$(CC) $(INC) -o get_hdf5_version get_hdf5_version.c

clean:
	rm get_hdf5_version
