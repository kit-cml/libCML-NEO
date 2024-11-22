#!/usr/bin/python
if __name__ == '__main__':
  import sys
  import os
  sys.path.insert(0, os.path.abspath('config'))
  import configure
  configure_options = [
    'PETSC_ARCH=linux-gnu-cxx-debug',
    '--with-shared=1',
    '--download-parmetis=1',
    '--download-f-blas-lapack=1',
    '--prefix=/opt/prog/petsc/petsc-3.1-p8',
    '--download-superlu_dist=1',
    '--with-clanguage=C++',
    '--download-sundials=1',
  ]
  configure.petsc_configure(configure_options)
